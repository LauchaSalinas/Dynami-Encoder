#ifndef Dynami_Battery_h
#define Dynami_Battery_h

#include <Arduino.h>
#include <ArduinoSort.h>

#include "./abstractions/BaseComponent.h"
#include "./abstractions/Mediator.h"

#define batteryPin 36 // Analog input pin
#define chargerPin 34 // Digital input pin

class Dynami_Battery : public BaseComponent
{
public:
  Dynami_Battery();
  void batterySetup();
  void batteryLoop();
  bool isBatteryConnected();

  // Getters & Setters
  int getCellsQty() { return this->cellsQty; };
  bool getBatteryConnectionStatus() { return this->batConnected; };
  bool getChargerStatus() { return this->chargerConnected; };
  int getBatteryValue() { return this->batteryValue; };
  float getBatVoltageValue() { return this->batVoltage; };
  int getBatPercentage() { return this->batPercentage; };

private:
  int batteryValue;
  float batVoltage;
  int batPercentage;
  int cellsQty = 0;
  bool chargerConnected = false;
  unsigned long voltageLastCheckTime = 0; // Battery voltage last check time
  int voltageFrecuencyCheck = 10000;
  bool chargerLastStatus = false;
  bool chargerPinReading = false;

  // Private Methods
  void checkVoltage();
  bool isChargerConnected();
  void batPercentageToCells();

  // External Notifiers
  void updateBatPercToCells();
  void chargerStatusChanged();
  void batteryConnectionStatusChanged();

  // battery connected checks
  bool batConnected = true;
  bool batConnectedLast = true;
  unsigned long batteryConnectedLastCheckTime = 0; // Battery voltage last check time
  int batteryConnectedFrecuencyCheck = 1000;
};

#endif