#include "Dynami_Encoder.h"

Dynami_Encoder::Dynami_Encoder(){}

void Dynami_Encoder::encoderSetup()
{
    ESP32Encoder::isrServiceCpuCore = 0;
    encoder.attachHalfQuad(DT, CLK);
    encoder.setCount(0);
}

void Dynami_Encoder::encoderLoop()
{
    encoderValue = encoder.getCount() / 2;
}
