#ifndef Dynami_Encoder_h
#define Dynami_Encoder_h

#include <ESP32Encoder.h>

#define CLK 15 // CLK ENCODER
#define DT 13  // DT ENCODER

#include "Dynami_Mediator.h"

class Dynami_Mediator;

class Dynami_Encoder // : public MediatedComponent
{
public:
    Dynami_Encoder();
    Dynami_Mediator *dynamiMediator = NULL;
    void set_mediator(Dynami_Mediator *mediator) { this->dynamiMediator = mediator; }

    void encoderSetup();
    void encoderLoop();
    void resetEncoderValue() { encoder.clearCount(); };

    // Getters & Setters
    long getEncoderValue(){ return encoderValue; };
    ESP32Encoder encoder;
    volatile long encoderValue = 0;
};

#endif