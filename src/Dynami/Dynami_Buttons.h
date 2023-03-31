#ifndef Dynami_Buttons_h
#define Dynami_Buttons_h

#define PIN_BUTTON1 12
#define PIN_BUTTON2 14
#define PIN_BUTTON3 27
#define DEBOUNCE_TIME 50

#define SHORT_PRESS_TIME 1000
#define LONG_PRESS_TIME 1000

#include <Arduino.h>
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
    bool shortPressC();
    bool shortPressR();
    bool longPressL();
    bool longPressC();
    bool longPressR();

    ezButton button1;
    ezButton button2;
    ezButton button3;

    unsigned long pressedTime = 0;
    unsigned long releasedTime = 0;
    bool isPressing = false;
    bool isLongDetected = false;

    unsigned long pressedTimeC = 0;
    unsigned long releasedTimeC = 0;
    bool isPressingC = false;
    bool isLongDetectedC = false;

    unsigned long pressedTim = 0;
    unsigned long releasedTim = 0;
    bool isPressin = false;
    bool isLongDetecte = false;
};

#endif