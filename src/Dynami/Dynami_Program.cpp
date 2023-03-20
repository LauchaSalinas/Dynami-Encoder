#include "Dynami_Program.h"

Dynami_Program::Dynami_Program(){

}

void Dynami_Program::setPointers(Dynami_Encoder *enc){
    dynamiEncoder = enc;
}

void Dynami_Program::dynamiProgramSetup() {
  startValue = millis();
}

void Dynami_Program::repControl() { ////// SI NO TIENE VUELTA DESCARTA
  if (millis() - startValue > 100) { // cada 100ms evalua
    if (dynamiEncoder->encoderValue > 200 || dynamiEncoder->encoderValue < -200) {
      if (dynamiEncoder->encoderValue >= 3000 && !up) { // si supera 3000 considera movimiento ascendente
        //Serial.println("Up True");
        tiempoInicial = millis();
        up = true ;
      }
      if (dynamiEncoder->encoderValue - dynamiEncoder->lastEncodedValue >= 200 || dynamiEncoder->encoderValue - dynamiEncoder->lastEncodedValue <= -200) { //bucle para revisar si se queda estatico el encoder
        dynamiEncoder->lastEncodedValue = dynamiEncoder->encoderValue;
        countReset = 0;
      }
      else {
        //quieto
        countReset++;
        // if (DEBUG_PROGRAM) Serial.println(countReset); NEEDS REFACTOR
        // si se queda 500ms (5*100ms) estatico, se reinicia la posición, si ya se activo la subida lleva 15resets
        if ((!up || countReset >= 15) && countReset >= 5) {
          dynamiMediator->programRepCancelled();
          up = false;
          resetRepValues();
          countReset = 0;
        }
      }
    }
    startValue = millis(); // resetea los 100ms
  }
}

void Dynami_Program::repMeasurement() {
  if (dynamiEncoder->maxEncodedValue <= dynamiEncoder->encoderValue) {
    dynamiEncoder->maxEncodedValue = dynamiEncoder->encoderValue;
    tiempoPico = millis();
  }
  //circuito de vuelta
  if (dynamiEncoder->encoderValue <= (dynamiEncoder->maxEncodedValue / 80) && up) {
    
    tiempoFinal = millis();
    up = false;
    addActualRep();
    dynamiMediator->dynamiNotifyCenter->debugPrint("debug 4");
    tiempoTotal = (tiempoFinal - tiempoInicial);
    tiempoPicoTotal = (tiempoPico - tiempoInicial);
    //delete next line
    
    velocitydb = (((double)dynamiEncoder->maxEncodedValue  / (double)580) * (double)2.1 * (double)4 ) / tiempoPicoTotal;

    dynamiMediator->programNewRep();
    resetRepValues();
  }
}

void Dynami_Program::velocityMeasurament() {
  if (millis() > velocityMeasurementLastCheck + velocityMeasurementFrec) { // cada x evalua

    velocitydb = ((double)distance - (double)distanceLast) / (double)20  ; // 600 steps * 45.6 mm or 0.0456m * 50 (project to 1 sec) * 4 (calibration)
    // dynamiNotifyCenter->SerialNotifyVelocity(velocitydb); // NEEDS REFACTOR

    //    You are measuring encoder steps per second.
    //    Divide that by the number of encoder steps
    //    per revolution to get revolutions per second.
    //    If the encoder is on a wheel shaft, multiply
    //    that by the circumference of the wheel (in
    //    meters) to get meters per second.
    distanceLast = distance;
    velocityMeasurementLastCheck = millis(); // resetea los 100ms
  }
}

void Dynami_Program::distanceMeasurement() {
  distance = (abs(dynamiEncoder->encoderValue) / (double)580) * (double)2.1 * (double)4  ; //in cm
  //SerialNotifyDistance(distance);
}

void Dynami_Program::setStartOfRep() { // records time & distance

}

void Dynami_Program::setEndOfRep() { // records time & distance

}

void Dynami_Program::calculateROM() { // Range of Motion (distance of rep)

}

void Dynami_Program::calculateMVP() { // Mean Propulsive Velocity

}

void Dynami_Program::calculateMV() { // MeanVelocity

}

void Dynami_Program::calculatePeakVelocity() { // (VMAX)

}

// Resets
void Dynami_Program::resetSetsReps() {
  sets = 1;
  actualRep = 0;
}



void Dynami_Program::resetRepValues() {
  //Reinicio de valores
  dynamiEncoder->resetEncoderValue();
  dynamiEncoder->maxEncodedValue = 0;
  dynamiEncoder->lastEncodedValue = 0;
}

// Arrow

void Dynami_Program::changeArrowDirection() {
  if (arrowDirectionUp) arrowDirectionUp = false;
  else arrowDirectionUp = true;
}

// Getters & Setters

void Dynami_Program::addSet() {
  sets++;
  actualRep = 0;
}

void Dynami_Program::addActualRep() {
  actualRep++;
}

void Dynami_Program::addTargetRep() {
  targetRep++;
}

int Dynami_Program::getSets() {
  return sets;
}

int Dynami_Program::getActualRep() {
  return actualRep;
}

int Dynami_Program::getTargetRep() {
  return targetRep;
}

char* Dynami_Program::getVelocity() {
  double asd = velocitydb;
  if (asd > 10) asd = 9.99;
  dtostrf(asd, 4, 2, velocityStr); //dtostrf(float_value, min_width, num_digits_after_decimal, where_to_store_string)
  return velocityStr;
}

int Dynami_Program::getTiempoPicoTotal() {
  return tiempoPicoTotal;
}

int Dynami_Program::getTiempoTotal() {
  return tiempoTotal;
}

int Dynami_Program::getTiempoRetorno() {
  return tiempoTotal - tiempoPicoTotal;
}

bool Dynami_Program::getArrowDirectionUp() {
  return arrowDirectionUp;
}
