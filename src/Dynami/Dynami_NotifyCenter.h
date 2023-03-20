#ifndef Dynami_NotifyCenter_h
#define Dynami_NotifyCenter_h

#include "Dynami_Mediator.h"
#include <Arduino.h>

class Dynami_Mediator;

class Dynami_NotifyCenter// : public MediatedComponent
{
public:
    Dynami_NotifyCenter();
    Dynami_Mediator *dynamiMediator = NULL;
    void set_mediator(Dynami_Mediator *mediator) {this->dynamiMediator = mediator;}
    void notifyCenterSetup();
    void SerialNotifyNewRep(int sets, int actualRep, int targetRep, long maxEncodedValue, long encoderValue, int tiempoTotal, int tiempoPicoTotal, int tiempoRetorno, char *velocity);
    void debugPrint(const char *);
    void debugPrint(char *, long);
    void debugPrint(char *, int);
    void debugPrint(int);
    void debugPrint(String);
};

#endif