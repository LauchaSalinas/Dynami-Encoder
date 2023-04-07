#ifndef Dynami_Debug_h
#define Dynami_Debug_h

#include "Dynami_Mediator.h"
#include "./resources/Dynami_Timer.h"

#define ON true
#define OFF false
#define DEBUG OFF

#if DEBUG == true
#define SERIAL SerialBT
#include "BluetoothSerial.h"
#endif
#if DEBUG == false
#define SERIAL Serial
#endif

class Dynami_Debug
{
public:
    Dynami_Debug();
    Dynami_Mediator *dynamiMediator = NULL;
    void set_mediator(Dynami_Mediator *mediator) { this->dynamiMediator = mediator; }
    void DebugStart();
    void DebugLoop();
    String AskNewString();
    bool GetCharYN();
    void SerialRead();
    void SerialRead2();
    void DebugVelocity();
    void DebugBattery();
    void DebugEncoder();
    void DebugDistance();
    void DebugAcceleration();
    void DebugPlotter();
    void set_debug_service_status(bool debug) { this->debug_service_status_ = debug; }
    void set_debug_encoder_status(bool debug) { this->debug_encoder_status_ = debug; }
    void set_debug_velocity_status(bool debug) { this->debug_velocity_status_ = debug; }
    void set_debug_battery_status(bool debug) { this->debug_battery_status_ = debug; }
    void set_debug_distance_status(bool debug) { this->debug_distance_status_ = debug; }
    void set_debug_acceleration_status(bool debug) { this->debug_acceleration_status_ = debug; }

private:
    bool debug_service_status_ = true;
    bool debug_encoder_status_ = false;
    bool debug_velocity_status_ = false; //this
    bool debug_battery_status_ = false;
    bool debug_distance_status_ = false;
    bool debug_acceleration_status_ = false;
    Dynami_Timer encoder_timer_;
    Dynami_Timer velocity_timer_;
    Dynami_Timer battery_timer_;
    Dynami_Timer distance_timer_;
    Dynami_Timer acceleration_timer_;
#if DEBUG == true
    BluetoothSerial SerialBT;
#endif
};

#endif