#ifndef Dynami_Program_h
#define Dynami_Program_h

#include "Dynami_Encoder.h"
#include "Dynami_Mediator.h"
#include "Dynami_Filter.h"

// 1.usar encoder en vez de distancia
// ver lo de la ventana
// probar si con el adaptativo cambia algo // cambia, no tanto pero cambia
// probar con el arduino si existe la misma variacion usando el serial en diferentes valores // serial en 0 da valores mas altos, serial con retardo da valores mucho mas smooth pero mas chicos.
// aprender los parametros del filtro y modificarlos
// programar filtro variable
// insertar calculo de potencia
// ultimasolucion, usar un arduino aparte
// chequear si el serial monitor corre en core 0
// aplicar freertos , tareas prioridades

class Dynami_Mediator;
class Dynami_Encoder;

class Dynami_Program //: public MediatedComponent
{
public:
    Dynami_Program();
    Dynami_Mediator *dynamiMediator = NULL;
    void set_mediator(Dynami_Mediator *mediator) { this->dynamiMediator = mediator; }
    unsigned long startValue = 0;

    unsigned long tiempoInicial = 0;
    unsigned long tiempoPico = 0;
    unsigned long tiempoPicoVMP = 0;
    unsigned long tiempoFinal = 0;
    int tiempoTotal = 0;
    int tiempoPicoTotal = 0;

    // Distance
    double distance = 0;
    double calibration = -0.79F;
    unsigned long distanceMeasurementLastCheck = 0;
    int distanceMeasurementFrec = 2500;

    LowPass<1> velocityLowPassFilter;
    LowPass<1> velocityLowPassFilter2;

    // Velocity
    char velocityStr[5];
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
    double accelerationdb = 0;
    double velocitydbLast = 0;
    double accelerationdbFiltered = 0;
    double accelerationFilterFreq = 1.5;
    LowPass<1> accelerationLowPassFilter;
    double accelerationdbFiltered2 = 0;
    LowPass<1> accelerationLowPassFilter2;

    unsigned long accelerationMeasurementLastCheck = 0;
    int accelerationMeasurementFrec = 10000;

    // Arrow
    bool arrowDirectionUp = true;

    //
    bool up = false;
    int countReset = 0;
    unsigned int actualRep = 0;
    unsigned int targetRep = 1;
    unsigned int sets = 1;

    void dynamiProgramSetup();
    void repControl();
    void resetDetector();
    void repControl2();
    void repControl3();
    double minDistance = 1;
    double ROM = 0;
    unsigned long initRepTime = 0;
    unsigned long finalRepTime = 0;
    double velocitydbFilteredMax = 0;
    unsigned long velocitydbFilteredMaxTime = 0;
    bool peakReached = false;
    bool newRep = false;
    unsigned long accelerationdbFilteredMaxTime = 0;
    double accelerationdbFilteredMax = 0;
    int stages = -3;
    void repMeasurement2();
    unsigned long repMeasurementLastCheck = 0;
    int repMeasurementFrec = 1000;
    double velocidadMVP = 0;
    double velocidadMV = 0;

    //Power
    double power=0;
    float weight=20;

    void repMeasurement();
    void distanceMeasurement();
    void velocityMeasurament();
    void accelerationMeasurament();
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
    double getDistance();
    char *getVelocity();
    double getVelocitydb();
    double getVelocitydbFiltered();
    double getVelocitydbFiltered2();
    double getAcceleration();
    double getAccelerationFiltered();
    int getTiempoPicoTotal();
    int getTiempoTotal();
    int getTiempoRetorno();
    bool getArrowDirectionUp();

    double getROM() { return ROM; };
    double getMPV() { return velocidadMVP / 10; };
    double getMV() { return velocidadMV / 10; };
    double getPV() { return velocitydbFilteredMax / 10; };
    double getPower() { return power; };
    // Delete this part
    Dynami_Encoder *dynamiEncoder = NULL;
    void setPointers(Dynami_Encoder *);
};

#endif