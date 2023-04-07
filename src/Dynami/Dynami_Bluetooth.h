#ifndef Dynami_Bluetooth_h
#define Dynami_Bluetooth_h

// See the following for generating UUIDs:
// https://www.uuidgenerator.net/
#define SERVICE_UUID "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"

#if DEBUG == false
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <BLE2902.h>
#include <Arduino.h>
#endif

#include "Dynami_Mediator.h"

class Dynami_Mediator;

#if DEBUG == false
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
#endif

#include "./abstractions/BaseComponent.h"
#include "./abstractions/Mediator.h"

class Dynami_Bluetooth : public BaseComponent
{
public:
    Dynami_Bluetooth();
    // Dynami_Mediator *dynamiMediator = NULL;
    // void set_mediator(Dynami_Mediator *mediator) { this->dynamiMediator = mediator; }
    #if DEBUG == false
    BLEServer *pServer = NULL;
    BLECharacteristic *pCharacteristic = NULL;
    BLEDescriptor *pDescr;
    BLE2902 *pBLE2902;

    MyServerCallbacks *SCB;
        #endif
    void BTSetup();
    void BTSendValue(char *);
    void BTLoop();
    void startAdvertising();
    unsigned long lastTimeSerialCheck = 0;
    unsigned int serialCheckTimeOut = 50;

private:
};

#endif