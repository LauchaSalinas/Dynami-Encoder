#ifndef Dynami_EnergySave_h
#define Dynami_EnergySave_h

#include "Dynami_Display.h"
#include "Dynami_Mediator.h"

class Dynami_Mediator;
class Dynami_Display;

class Dynami_EnergySave //: public MediatedComponent
{
public:
    Dynami_EnergySave();
    Dynami_Mediator *dynamiMediator = NULL;
    void set_mediator(Dynami_Mediator *mediator) {this->dynamiMediator = mediator;}
    void energySaveModeDisplay();
    void energySaveLoop();
    void energySaveSetDisplayON();
    void energySaveSetDisplayOFF();
    void energySaveService();
    void energySaveNewEvent();
    void setEnergySaveMode(bool);
    void startEnergySaveModeService();
    bool getEnergySaveMode();
    Dynami_Display *dinamyDisplay = NULL;
    void setDisplayRef(Dynami_Display *);
    bool energySaveMode = false;
    unsigned long energySaveLastCheckTime = 0;
    int energySaveTimeON = 4000;
    bool energySaveDisplayStatus;
    bool energySaveDisplayStatusLast;
};

#endif