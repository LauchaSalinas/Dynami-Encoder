#ifndef Dynami_Battery_h
#define Dynami_Battery_h

#include <Arduino.h>
#include <ArduinoSort.h>
#include "Dynami_Mediator.h"

class Dynami_Mediator;

class Dynami_Battery // : public MediatedComponent // try to implement this later
{
  public:
    Dynami_Battery();
    Dynami_Mediator *dynamiMediator = NULL;
    void set_mediator(Dynami_Mediator *mediator) {this->dynamiMediator = mediator;}
    void batterySetup();
    void batteryLoop();
    void checkVoltage();
    bool isBatteryConnected(); //*
    void batteryConnectionStatusChanged();
    bool isChargerConnected();
    void chargerStatusChanged();
    void updateBatPercToCells();
    void batPercentageToCells();

    // Getters & Setters
    int getCellsQty(); //*
    bool getBatteryConnectionStatus(); //*
    bool getChargerStatus(); //*
    int batteryPin = 36; // Analog input pin
    int chargerPin = 34;
    int batteryValueArr[10]; // Analog Output of Sensor
    int batteryValue; //*
    float batVoltage;
    int batPercentage = 0;
    int cellsQty = 0;
    unsigned long voltageLastCheckTime = 0; // Battery voltage last check time
    int voltageFrecuencyCheck = 10000;

    // battery connected checks
    bool batConnected = true;
    bool batConnectedLast = true;
    unsigned long batteryConnectedLastCheckTime = 0; // Battery voltage last check time
    int batteryConnectedFrecuencyCheck = 1000;

    bool chargerConnected = false;

    byte chargerLastStatus = LOW; // fix this later; same as battery
    byte chargerPinReading = LOW;
    
  private:

};

#endif
