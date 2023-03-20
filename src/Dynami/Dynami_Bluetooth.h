#ifndef Dynami_Bluetooth_h
#define Dynami_Bluetooth_h

// See the following for generating UUIDs:
// https://www.uuidgenerator.net/
#define SERVICE_UUID "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <BLE2902.h>
#include <Arduino.h>
#include "Dynami_Mediator.h"

class Dynami_Mediator;

class MyServerCallbacks : public BLEServerCallbacks
{
public:
    void onConnect(BLEServer *pServer)
    {
        deviceConnected = true;
    };

    void onDisconnect(BLEServer *pServer)
    {
        deviceConnected = false;
    }

    bool deviceConnected = false;
    bool oldDeviceConnected = false;
};

class Dynami_Bluetooth // : public MediatedComponent
{
public:
    Dynami_Bluetooth();
    Dynami_Mediator *dynamiMediator = NULL;
    void set_mediator(Dynami_Mediator *mediator) {this->dynamiMediator = mediator;}
    BLEServer *pServer = NULL;
    BLECharacteristic *pCharacteristic = NULL;
    BLEDescriptor *pDescr;
    BLE2902 *pBLE2902;
    MyServerCallbacks *SCB;
    void BTSetup();
    void BTSendValue(char *);
    void BTLoop();
    void startAdvertising();
private:
};

#endif