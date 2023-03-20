#include "Dynami_Battery.h"

Dynami_Battery::Dynami_Battery(){}

void Dynami_Battery::batterySetup() {
  pinMode(chargerPin, INPUT); // setup for charger pin
  batConnected = isBatteryConnected();
  chargerConnected = isChargerConnected();
  if (batConnected) {
    checkVoltage();
    batPercentageToCells();
  }
}

void Dynami_Battery::batteryLoop() {

  //Check Voltage routine
  if (millis() > voltageLastCheckTime + voltageFrecuencyCheck) {
    if (batConnected) {
      checkVoltage();
      updateBatPercToCells();
    }
    voltageLastCheckTime = millis();
  }

  if (millis() > batteryConnectedLastCheckTime + batteryConnectedFrecuencyCheck) { // debounce batery
    //battery check routine
    batConnected = isBatteryConnected();
    

    //Check charger routine
    chargerConnected = isChargerConnected();

    batteryConnectedLastCheckTime = millis(); //debounce counter store
  }

  chargerStatusChanged();
  batteryConnectionStatusChanged();
}
void Dynami_Battery::checkVoltage() {
  for (int i = 0 ; i < 10 ; i++ ) {
    batteryValueArr[i] = analogRead(batteryPin);
  }
  sortArray(batteryValueArr, 10);
  batteryValue = (batteryValueArr[4] + batteryValueArr[5] + batteryValueArr[6]) / 3;

  batVoltage = (float) (batteryValue * 3.3 / 4096) * 4.2 / 3.3;
  batPercentage = map(batteryValue, 2900, 4096, 0, 100); //3.3V as Battery Cut off Voltage & 4.1V as Maximum Voltage
  batPercentage = constrain(batPercentage, 0, 100);
}

bool Dynami_Battery::isBatteryConnected() {
  if (analogRead(batteryPin) >= 300) return true;
  return false;
}

void Dynami_Battery::batteryConnectionStatusChanged() {
  if (batConnected != batConnectedLast) {
    dynamiMediator->batteryConnectionStatusChanged();

    batConnectedLast = batConnected;
  }
}

bool Dynami_Battery::isChargerConnected() {
  chargerPinReading = digitalRead(chargerPin);
  if (chargerPinReading == HIGH) return true;
  return false;
}

void Dynami_Battery::chargerStatusChanged() {
  if (chargerPinReading != chargerLastStatus) {
    dynamiMediator->chargerStatusChanged();
    chargerLastStatus = chargerPinReading;
  }
}

void Dynami_Battery::updateBatPercToCells() {
  int upperTreshold = 5;
  int lowerTreshold = 5;

  if (batPercentage >= (cellsQty * 20) + upperTreshold) {
    cellsQty++;
    dynamiMediator->cellsQtyChanged();
  }
  else if (batPercentage <= ((cellsQty - 1) * 20) - lowerTreshold) {
    cellsQty--;
    dynamiMediator->cellsQtyChanged();
  }
}

void Dynami_Battery::batPercentageToCells() {
  cellsQty = map(batPercentage, 0, 100, 1, 5);
}

// Getters & Setters

int Dynami_Battery::getCellsQty() {
  return cellsQty;
}

bool Dynami_Battery::getBatteryConnectionStatus() {
  return batConnected;
}

bool Dynami_Battery::getChargerStatus() {
  return chargerConnected;
}
