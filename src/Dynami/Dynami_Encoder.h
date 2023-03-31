#ifndef Dynami_Encoder_h
#define Dynami_Encoder_h

#include <ESP32Encoder.h>

#define CLK 13 // CLK ENCODER
#define DT 15  // DT ENCODER

#include "Dynami_Mediator.h"

class Dynami_Mediator;


class Dynami_Encoder // : public MediatedComponent
{
public:
    Dynami_Encoder();
    Dynami_Mediator *dynamiMediator = NULL;
    void set_mediator(Dynami_Mediator *mediator) {this->dynamiMediator = mediator;}
    ESP32Encoder encoder;
    volatile long encoderValue = 0;
    long lastencoderValue = 0;
    volatile long maxEncodedValue = 0;
    long lastEncodedValue = 0;
    void encoderSetup();
    void encoderLoop();
    void resetEncoderValue();

    // Getters & Setters

    long getEncoderValue();
    long getMaxEncodedValue();
};

#endif