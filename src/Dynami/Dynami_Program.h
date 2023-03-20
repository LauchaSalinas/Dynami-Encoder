#ifndef Dynami_Program_h
#define Dynami_Program_h

#include "Dynami_Encoder.h"
#include "Dynami_Mediator.h"

class Dynami_Mediator;
class Dynami_Encoder;

class Dynami_Program //: public MediatedComponent
{
public:
    Dynami_Program();
    Dynami_Mediator *dynamiMediator = NULL;
    void set_mediator(Dynami_Mediator *mediator) {this->dynamiMediator = mediator;}
    unsigned long startValue = 0;

    unsigned long tiempoInicial = 0;
    unsigned long tiempoPico = 0;
    unsigned long tiempoFinal = 0;
    int tiempoTotal = 0;
    int tiempoPicoTotal = 0;

    // Velocity
    char velocityStr[5];
    double velocitydb = 0;
    unsigned long velocityMeasurementLastCheck = 0;
    int velocityMeasurementFrec = 200;
    double velocityLastEncodedValue = 0;

    // Distance
    double distance = 0;
    double distanceLast = 0;

    // Arrow
    bool arrowDirectionUp = false;

    //
    bool up = false;
    int countReset = 0;
    unsigned int actualRep = 0;
    unsigned int targetRep = 1;
    unsigned int sets = 1;

    void dynamiProgramSetup();

    void repControl();

    void repMeasurement();

    void velocityMeasurament();

    void distanceMeasurement();

    void setStartOfRep();

    void setEndOfRep();

    void calculateROM();

    void calculateMVP();

    void calculateMV();
    void calculatePeakVelocity();

    // Resets
    void resetSetsReps();

    void resetRepValues();

    // Arrow

    void changeArrowDirection();
    // Getters & Setters

    void addSet();

    void addActualRep();

    void addTargetRep();

    int getSets();

    int getActualRep();

    int getTargetRep();

    char * getVelocity();

    int getTiempoPicoTotal();

    int getTiempoTotal();

    int getTiempoRetorno();

    bool getArrowDirectionUp();


    //Delete this part
    Dynami_Encoder *dynamiEncoder = NULL;
    void setPointers (Dynami_Encoder *);

};

#endif