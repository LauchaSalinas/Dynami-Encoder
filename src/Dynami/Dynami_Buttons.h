#ifndef Dynami_Buttons_h
#define Dynami_Buttons_h

#define PIN_BUTTON1 12
#define PIN_BUTTON2 14

#include <Arduino.h> // Check if this is already included inside the EzButton.h
#include <ezButton.h>
#include "Dynami_Mediator.h"

class Dynami_Mediator;

class Dynami_Buttons //: public MediatedComponent
{
public:
    Dynami_Buttons();
    Dynami_Mediator *dynamiMediator = NULL;
    void set_mediator(Dynami_Mediator *mediator) {this->dynamiMediator = mediator;}
    void buttonsSetup();
    void buttonsLoop();
    bool shortPressL();
    bool shortPressR();
    bool longPressL();
    bool longPressR();

    ezButton button1; // create ezButton object that attach to pin
    ezButton button2;

    const int SHORT_PRESS_TIME = 1000; // 1000 milliseconds
    const int LONG_PRESS_TIME = 1000;  // 1000 milliseconds

    unsigned long pressedTime = 0;
    unsigned long releasedTime = 0;
    bool isPressing = false;
    bool isLongDetected = false;

    unsigned long pressedTim = 0;
    unsigned long releasedTim = 0;
    bool isPressin = false;
    bool isLongDetecte = false;
};

#endif