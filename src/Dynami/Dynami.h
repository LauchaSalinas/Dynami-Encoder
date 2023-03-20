#ifndef Dynami_h
#define Dynami_h

#include "Dynami_Battery.h"
#include "Dynami_Bluetooth.h"
#include "Dynami_Display.h"
#include "Dynami_EnergySave.h"
#include "Dynami_Encoder.h"
#include "Dynami_Program.h"
#include "Dynami_NotifyCenter.h"
#include "Dynami_Buttons.h"
#include "Dynami_Mediator.h"
#include "Dynami_Update.h"

class Dynami
{
public:
    Dynami();
    void dynamiSetup();
    void dynamiLoop();

private:
    Dynami_Encoder      dynamiEncoder;
    Dynami_Program      dynamiProgram;
    Dynami_Battery      dynamiBattery;
    Dynami_Bluetooth    dynamiBluetooth;
    Dynami_Display      dynamiDisplay;
    Dynami_Buttons      dynamiButtons;
    Dynami_EnergySave   dynamiEnergySave;
    Dynami_NotifyCenter dynamiNotifyCenter;
    Dynami_Mediator     dynamiMediator;
    Dynami_Update       dynamiUpdate;
};

#endif