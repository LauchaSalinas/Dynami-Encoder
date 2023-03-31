#ifndef Dynami_Battery_h
#define Dynami_Battery_h

#include <Arduino.h>
#include <ArduinoSort.h>
#include "Dynami_MediatedComponent.h"

#define batteryPin 36 // Analog input pin
#define chargerPin 34 // Digital input pin


class MediatedComponent;

class Dynami_Battery : public MediatedComponent
{
public:
  Dynami_Battery();
  void batterySetup();
  void batteryLoop();
  bool isBatteryConnected();
  
  // Getters & Setters
  int   getCellsQty();
  bool  getBatteryConnectionStatus();
  bool  getChargerStatus();
  int   getBatteryValue();
  float getBatVoltageValue();
  int   getBatPercentage();

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

  //Private Methods
  void checkVoltage();
  bool isChargerConnected();
  void batPercentageToCells();

  //External Notifiers
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
