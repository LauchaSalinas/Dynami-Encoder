#include "Dynami_Program.h"

Dynami_Program::Dynami_Program() : velocityLowPassFilter(6.5, 1e2, true), velocityLowPassFilter2(1.5, 1e2, true), accelerationLowPassFilter(accelerationFilterFreq, 1e2, true), accelerationLowPassFilter2(0.75, 1e2, true)
{
}

void Dynami_Program::resetDetector()
{
  // timeout check
  if (millis() > resetMeasurementLastCheck + 200)
  {
    // stage 1 -> direct reset
    if (distance > 1 && abs(velocitydbFiltered) < 0.5 && stages <= 1)
    {
      dynamiMediator->programRepCancelled();
      resetRepValues();
    }
    // stage 2 -> acummulative reset
    if (abs(distance) >= 2 && stages > 1)
    {
      // resetCounter reset is stills moves
      if (abs(velocitydbFiltered) > 0.5)
      {
        countReset = 0;
      }
      // If theres no movement, increases the reset counter
      else
      {
        countReset++;
      }
      if (countReset >= 5 && abs(velocitydbFiltered) < 0.5)
      {
        dynamiMediator->programRepCancelled();
        resetRepValues();
      }
    }
    resetMeasurementLastCheck = millis();
  }
}

void Dynami_Program::repControl3()
{
  // etapa 0 reset
  // etapa 1 idle -> d=0
  // etapa 2 descending -> d--
  // etapa 3 inicio concentrico -> detector v>=0 , almacena dmin, t, comienza a almacenar velocidad y contador
  // etapa 3a vpeak detector v>vpeak almacena v
  // etapa 3b mvp finish -> detector a<=0, almacena t, calcula mvp = acum velocidad / contador
  // etapa 4 mv finish -> detector v<=0, almacena t, calcula vm = acum velocidad / contador

  // etapa 1 idle -> d=0
  if (distance == 0 && stages == 0) //-1
  {
    // iddle
    stages = 1; //-0.5
  }
  // etapa 2 descending -> d--
  if (distance < -10 && stages <= 1) // fix stages >= 1
  {
    stages = 2; // 0
  }

  // etapa 3 inicio concentrico -> detector v>=0 , almacena dmin, t, comienza a almacenar velocidad y contador
  if (velocitydbFiltered >= 0 && stages == 2)
  {
    minDistance = distance;
    initRepTime = millis();
    velocityCounter = 0;
    velocityAcumulator = 0;

    // this is a reset control not a rep control, move from function
    // if (minDistance > -20)
    // {
    //   resetRepValues();
    //   return;
    // }
    stages = 3; // 0.5
  }

  // etapa 3a Medicion velocidad pico
  // etapa 3a vpeak detector v>vpeak almacena v
  if (velocitydbFiltered2 > velocitydbFilteredMax && stages == 3)
  {
    velocitydbFilteredMax = velocitydbFiltered2;
    velocitydbFilteredMaxTime = millis();
  }
  // etapa 3b medición velocidad maxima propulsiva
  // etapa 3b mvp finish -> detector a<=0, almacena t, calcula mvp = acum velocidad / contador
  if (accelerationdbFiltered <= 0 && velocidadMVP == 0 && stages == 3)
  {
    velocidadMVP = velocityAcumulator / velocityCounter;
  }
  // etapa 4 mv finish -> detector velocidadFiltradaLenta<=0, almacena t, calcula vm = acum velocidad / contador
  if (velocitydbFiltered <= 0.1 && stages == 3 && millis() > initRepTime+150)
  {
    stages = 4; // 1
    velocidadMV = velocityAcumulator / velocityCounter;
    finalRepTime = millis();
    ROM = distance + abs(minDistance);
    power = (weight * velocidadMV / 10 * 9.81);
    // if ((ROM < 5 || velocitydbFilteredMax / 10 < 0.3) && (finalRepTime - initRepTime) > 200)
    // { // delete /10 // this is a reset control not a rep control, move from function
    //   resetRepValues();
    //   return;
    // }
    if (power > 10 && power < 1000)
      dynamiMediator->programNewRep();
  }
  // etapa 5 velocidad filtrada lenta llega a 0, resetea
  if (velocitydbFiltered2 <= 0 && stages == 4)
  {
    stages = 5;
    repMeasurement();
  }
}

void Dynami_Program::repMeasurement()
{
  // inform new rep and reset all values
  if (millis() > repMeasurementLastCheck + repMeasurementFrec)
  {
    Serial.println("Rep and reset");

    resetRepValues();
    repMeasurementLastCheck = millis();
  }
}

void Dynami_Program::distanceMeasurement()
{
  //    You are measuring encoder steps.
  //    If the encoder is on a wheel shaft, multiply
  //    that by the circumference of the wheel (in
  //    meters) to get meters.

  // 600 steps * 45.6 mm or 0.0456m * 50 (project to 1 sec) * 4 (calibration)
  if (micros() > distanceMeasurementLastCheck + distanceMeasurementFrec)
  {
    distance = (dynamiEncoder->encoderValue / (double)580) * ((double)4.2 + calibration) * (double)4; // in cm

    distanceMeasurementLastCheck = micros();
  }
}

void Dynami_Program::velocityMeasurament()
{
  if (micros() > velocityMeasurementLastCheck + velocityMeasurementFrec)
  {
    velocitydb = (distance - distanceLast) * 100 / ((micros() - velocityMeasurementLastCheck) / 1000);
    distanceLast = distance;
    velocityCounter++;
    velocityAcumulator = velocityAcumulator + velocitydb;
    velocitydbFiltered = velocityLowPassFilter.filt(velocitydb);
    velocitydbFiltered2 = velocityLowPassFilter2.filt(velocitydb);
    velocityMeasurementLastCheck = micros();
  }
}

void Dynami_Program::accelerationMeasurament()
{
  if (micros() > accelerationMeasurementLastCheck + accelerationMeasurementFrec)
  {
    accelerationdb = ((double)velocitydbFiltered - (double)velocitydbLast) * 1000 / ((micros() - accelerationMeasurementLastCheck) / 1000);
    velocitydbLast = velocitydbFiltered;
    accelerationdbFiltered = accelerationLowPassFilter.filt(accelerationdb);
    accelerationdbFiltered2 = accelerationLowPassFilter2.filt(accelerationdb);
    accelerationMeasurementLastCheck = micros();
  }
}

void Dynami_Program::resetRepValues()
{
  // Reinicio de valores
  dynamiEncoder->resetEncoderValue();
  distance = 0;
  distanceLast = 0;
  velocitydbFiltered = 0;
  velocitydbFiltered2 = 0;
  accelerationdbFiltered = 0;
  minDistance = 0;
  initRepTime = 0;
  finalRepTime = 0;
  velocitydbFilteredMax = 0;
  velocitydbFilteredMaxTime = 0;
  velocidadMVP = 0;
  velocidadMV = 0;
  stages = 0;
  velocityCounter = 0;
  velocityAcumulator = 0;
  countReset = 0;
}
