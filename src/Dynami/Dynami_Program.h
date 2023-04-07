#ifndef Dynami_Program_h
#define Dynami_Program_h

#include "Dynami_Encoder.h"
#include "Dynami_Mediator.h"
#include "./resources/Dynami_Filter.h"

class Dynami_Mediator;
class Dynami_Encoder;

class Dynami_Program //: public MediatedComponent
{
public:
    Dynami_Program();
    Dynami_Mediator *dynamiMediator = NULL;
    void set_mediator(Dynami_Mediator *mediator) { this->dynamiMediator = mediator; }
    Dynami_Encoder *dynamiEncoder = NULL;
    void setPointers(Dynami_Encoder *enc) { dynamiEncoder = enc; };

    // Distance
    void distanceMeasurement();
    double distance = 0;
    double calibration = -0.79F;
    unsigned long distanceMeasurementLastCheck = 0;
    int distanceMeasurementFrec = 2500;

    // Velocity
    LowPass<1> velocityLowPassFilter;
    LowPass<1> velocityLowPassFilter2;
    void velocityMeasurament();
    double distanceLast = 0;
    double velocitydb = 0;
    double velocitydbFiltered = 0;
    double velocitydbFiltered2 = 0;
    double velocityFilterFreq = 1.5;
    double velocitySamplingFrecuency = 1e2;
    unsigned long velocityCounter = 0;
    double velocityAcumulator = 0;
    unsigned long velocityMeasurementLastCheck = 0;
    int velocityMeasurementFrec = 5000;

    // Acceleration
    void accelerationMeasurament();
    double accelerationdb = 0;
    double velocitydbLast = 0;
    double accelerationdbFiltered = 0;
    double accelerationFilterFreq = 1.5;
    LowPass<1> accelerationLowPassFilter;
    double accelerationdbFiltered2 = 0;
    LowPass<1> accelerationLowPassFilter2;
    unsigned long accelerationMeasurementLastCheck = 0;
    int accelerationMeasurementFrec = 10000;

    // Reset
    void resetDetector();
    int stages = 0;

    void repControl3();
    double minDistance = 0;
    double ROM = 0;
    unsigned long initRepTime = 0;
    unsigned long finalRepTime = 0;
    double velocitydbFilteredMax = 0;
    unsigned long velocitydbFilteredMaxTime = 0;
    double velocidadMVP = 0;
    double velocidadMV = 0;

    void repMeasurement();
    unsigned long repMeasurementLastCheck = 0;
    int repMeasurementFrec = 1000;

    // Resets
    void resetRepValues();

    // Getters & Setters

    double getDistance() { return distance; };
    double getVelocitydb() { return velocitydb; };
    double getVelocitydbFiltered() { return velocitydbFiltered; };
    double getVelocitydbFiltered2() { return velocitydbFiltered2; };
    double getAcceleration() { return accelerationdb; };
    double getAccelerationFiltered() { return accelerationdbFiltered; };

    double getROM() { return ROM; };
    double getMPV() { return velocidadMVP / 10; };
    double getMV() { return velocidadMV / 10; };
    double getPV() { return velocitydbFilteredMax / 10; };
    double getPower() { return power; };

    void setWeight(float weight) { this->weight = weight; };

private:
    // reset
    unsigned long resetMeasurementLastCheck = 0;
    int countReset = 0;

    // Power
    double power = 0;
    float weight = 20;
};

#endif