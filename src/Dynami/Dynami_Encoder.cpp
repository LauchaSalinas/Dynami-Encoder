#include "Dynami_Encoder.h"

Dynami_Encoder::Dynami_Encoder(){}

void Dynami_Encoder::encoderSetup()
{
    ESP32Encoder::isrServiceCpuCore = 0;
    encoder.attachFullQuad(DT, CLK);
    encoder.setCount(0);
}

void Dynami_Encoder::encoderLoop()
{
    encoderValue = encoder.getCount() / 4;
    
}

void Dynami_Encoder::resetEncoderValue()
{
    encoder.clearCount();
}

// Getters & Setters

long Dynami_Encoder::getEncoderValue()
{
    return encoderValue;
}

long Dynami_Encoder::getMaxEncodedValue()
{
    return maxEncodedValue;
}