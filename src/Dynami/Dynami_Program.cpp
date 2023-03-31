#include "Dynami_Program.h"

Dynami_Program::Dynami_Program() : velocityLowPassFilter(6.5, 1e2, true), velocityLowPassFilter2(1.5, 1e2, true), accelerationLowPassFilter(accelerationFilterFreq, 1e2, true), accelerationLowPassFilter2(0.75, 1e2, true)
{
}

void Dynami_Program::setPointers(Dynami_Encoder *enc)
{
  dynamiEncoder = enc;
}

void Dynami_Program::dynamiProgramSetup()
{
  startValue = millis();
}

void Dynami_Program::repControl()
{ ////// SI NO TIENE VUELTA DESCARTA
  if (millis() - startValue > 100)
  { // cada 100ms evalua
    if (dynamiEncoder->encoderValue > 200 || dynamiEncoder->encoderValue < -200)
    {
      if (dynamiEncoder->encoderValue >= 3000 && !up)
      { // si supera 3000 considera movimiento ascendente
        Serial.println("Up True");
        tiempoInicial = millis();
        up = true;
      }
      if (dynamiEncoder->encoderValue - dynamiEncoder->lastEncodedValue >= 200 || dynamiEncoder->encoderValue - dynamiEncoder->lastEncodedValue <= -200)
      { // bucle para revisar si se queda estatico el encoder
        dynamiEncoder->lastEncodedValue = dynamiEncoder->encoderValue;
        countReset = 0;
      }
      else
      {
        // quieto
        countReset++;
        // if (DEBUG_PROGRAM) Serial.println(countReset); NEEDS REFACTOR
        // si se queda 500ms (5*100ms) estatico, se reinicia la posición, si ya se activo la subida lleva 15resets
        if ((stages < 2 || countReset >= 15) && countReset >= 5)
        {
          dynamiMediator->programRepCancelled();
          up = false;
          // resetRepValues();
          countReset = 0;
        }
      }
    }
    startValue = millis(); // resetea los 100ms
  }
}

void Dynami_Program::resetDetector()
{
  // timeout check
  if (millis() - startValue > 200)
  {
    //
    if (dynamiEncoder->encoderValue > 200 || dynamiEncoder->encoderValue < -200)
    {
      // If theres movement, resets the reset counter
      if (abs(velocitydbFiltered) > 0.03)
      {
        countReset = 0;
      }
      // If theres no movement, increases the reset counter
      else
      {
        countReset++;
        // si se queda 500ms (5*100ms) estatico, se reinicia la posición, si ya se activo la subida lleva 15resets
        if ((!up || countReset >= 15) && countReset >= 5)
        {
          dynamiMediator->programRepCancelled();
          resetRepValues();
          countReset = 0;
        }
      }
      if (distance < 5 && countReset >= 5)
      {
        dynamiMediator->programRepCancelled();
        resetRepValues();
        countReset = 0;
      }
    }

    startValue = millis();
  }
}

void Dynami_Program::repControl2()
{

  if (distance < minDistance && stages <= -2)
  {
    // Serial.print("entro");
    minDistance = distance;
    initRepTime = millis();
    stages = -2;
  }
  // test could be either velocity or acceleration
  // added 10 millis to separate the events
  // added !up to not enter this stage in the post stages
  // min distance has to be at least
  if (velocitydbFiltered > 0 && millis() > initRepTime + 10 && !up && minDistance < -15 && stages == -2)
  {
    tiempoInicial = millis();
    up = true;
    stages = -1;
  }
  // if rep travel if above 50% of the return rep and /*acceleration is still*/ -> measure MPV
  if (distance >= (minDistance * 0.5) && up)
  {
    if (accelerationdbFiltered > accelerationdbFilteredMax && (stages == -1 || stages == 0))
    {
      accelerationdbFilteredMax = accelerationdbFiltered;
      accelerationdbFilteredMaxTime = millis();
      stages = 0;
    }
    // if time between last peak and millis is greater than 10 millis, considers that peak has been reached
    if (accelerationdbFilteredMaxTime + 20 < millis() && stages == 0)
    {
      velocidadMVP = velocitydbFiltered;
      tiempoPicoVMP = millis();
      stages = 1;
    }
  }

  // if rep travel if above 60% of the return rep and /*velocity is still*/ -> measure PV
  if (distance > minDistance * 0.40 && up)
  {
    if (velocitydbFiltered > velocitydbFilteredMax && (stages == 1 || stages == 2))
    {
      velocitydbFilteredMax = velocitydbFiltered;
      velocitydbFilteredMaxTime = millis();
      stages = 2;
    }
    // if time between last peak and millis is greater than 10 millis, considers that peak has been reached
    if (velocitydbFilteredMaxTime + 20 < millis() && stages == 2)
    {
      // tiempoPico = millis(); i think this should be replaced by velocitydbFilteredMaxTime
      peakReached = true;
      stages = 3;
    }
  }

  if (distance > minDistance * 0.1 && peakReached && velocitydbFiltered <= 0.1 && stages == 3)
  {
    stages = 4;
    newRep = true;
    repMeasurement2();
  }
}

void Dynami_Program::repControl3()
{
  // etapa 0 reset
  // etapa 1 idle -> d=0
  // etapa 2 descending -> d--
  // etapa 3 inicio concentrico -> detector v>=0 , almacena dmin, t, comienza a almacenar velocidad y contador
  // etapa 4a vpeak detector v>vpeak almacena v
  // etapa 4b mvp finish -> detector a<=0, almacena t, calcula mvp = acum velocidad / contador
  // etapa 5 mv finish -> detector v<=0, almacena t, calcula vm = acum velocidad / contador

  // etapa 1 idle -> d=0
  if (distance == 0 && stages == 0) //-1
  {
    // iddle
    stages = 1; //-0.5
  }
  // etapa 2 descending -> d--
  if (distance < 0 && stages <= 1) // fix stages >= 1
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
    if (minDistance > -20)
    {
      resetRepValues();
      return;
    }
    stages = 3; //0.5
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
  if (velocitydbFiltered <= 0.1 && stages == 3)
  {
    stages = 4; //1
    velocidadMV = velocityAcumulator / velocityCounter;
    finalRepTime = millis();
    ROM = distance + abs(minDistance);
    power = (weight * velocidadMV / 10 * 9.81);
    if ((ROM < 5 || velocitydbFilteredMax / 10 < 0.3) && (finalRepTime - initRepTime) > 200)
    { // delete /10 // this is a reset control not a rep control, move from function
      resetRepValues();
      return;
    }
    if (power > 10 && power < 1000)
      dynamiMediator->programNewRep();
  }
  // etapa 5 velocidad filtrada lenta llega a 0, resetea
  if (velocitydbFiltered2 <= 0 && stages == 4)
  {
    stages = 5;
    repMeasurement2();
  }
}
void Dynami_Program::repMeasurement()
{
  if (dynamiEncoder->maxEncodedValue <= dynamiEncoder->encoderValue)
  {
    dynamiEncoder->maxEncodedValue = dynamiEncoder->encoderValue;
    tiempoPico = millis();
  }
  // circuito de vuelta
  if (dynamiEncoder->encoderValue <= (dynamiEncoder->maxEncodedValue / 80) && up)
  {

    tiempoFinal = millis();
    up = false;
    addActualRep();
    tiempoTotal = (tiempoFinal - tiempoInicial);
    tiempoPicoTotal = (tiempoPico - tiempoInicial);

    dynamiMediator->programNewRep();
    resetRepValues();
  }
}
void Dynami_Program::repMeasurement2()
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

void Dynami_Program::setStartOfRep()
{ // records time & distance
}

void Dynami_Program::setEndOfRep()
{ // records time & distance
}

void Dynami_Program::calculateROM()
{ // Range of Motion (distance of rep)
}

void Dynami_Program::calculateMVP()
{ // Mean Propulsive Velocity
}

void Dynami_Program::calculateMV()
{ // MeanVelocity
}

void Dynami_Program::calculatePeakVelocity()
{ // (VMAX)
}

// Resets
void Dynami_Program::resetSetsReps()
{
  sets = 1;
  actualRep = 0;
}

void Dynami_Program::resetRepValues()
{
  // Reinicio de valores
  dynamiEncoder->resetEncoderValue();
  dynamiEncoder->maxEncodedValue = 0;
  dynamiEncoder->lastEncodedValue = 0;
  distance = 0;
  distanceLast = 0;
  velocitydbFiltered = 0;
  velocitydbFiltered2 = 0;
  accelerationdbFiltered = 0;
  minDistance = 0;
  initRepTime = 0;
  tiempoInicial = 0;
  up = false;
  accelerationdbFilteredMax = 0;
  tiempoPicoVMP = 0;
  velocitydbFilteredMax = 0;
  velocitydbFilteredMaxTime = 0;
  peakReached = false;
  newRep = false;
  velocidadMVP = 0;
  velocidadMV = 0;
  stages = 0;
  velocityCounter = 0;
  velocityAcumulator = 0;
  finalRepTime = 0;
}

// Arrow

void Dynami_Program::changeArrowDirection()
{
  if (arrowDirectionUp)
    arrowDirectionUp = false;
  else
    arrowDirectionUp = true;
}

// Getters & Setters

void Dynami_Program::addSet()
{
  sets++;
  actualRep = 0;
}

void Dynami_Program::addActualRep()
{
  actualRep++;
}

void Dynami_Program::addTargetRep()
{
  targetRep++;
}

int Dynami_Program::getSets()
{
  return sets;
}

int Dynami_Program::getActualRep()
{
  return actualRep;
}

int Dynami_Program::getTargetRep()
{
  return targetRep;
}

double Dynami_Program::getDistance()
{
  return distance;
}

char *Dynami_Program::getVelocity()
{
  double asd = velocitydb;
  if (asd > 10)
    asd = 9.99;
  dtostrf(asd, 4, 2, velocityStr); // dtostrf(float_value, min_width, num_digits_after_decimal, where_to_store_string)
  return velocityStr;
}

double Dynami_Program::getVelocitydb()
{
  return velocitydb;
}

double Dynami_Program::getVelocitydbFiltered()
{
  return velocitydbFiltered;
}

double Dynami_Program::getAcceleration()
{
  return accelerationdb;
}

double Dynami_Program::getAccelerationFiltered()
{
  return accelerationdbFiltered;
}

int Dynami_Program::getTiempoPicoTotal()
{
  return tiempoPicoTotal;
}

int Dynami_Program::getTiempoTotal()
{
  return tiempoTotal;
}

int Dynami_Program::getTiempoRetorno()
{
  return tiempoTotal - tiempoPicoTotal;
}

bool Dynami_Program::getArrowDirectionUp()
{
  return arrowDirectionUp;
}
