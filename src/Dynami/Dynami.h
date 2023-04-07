#ifndef Dynami_h
#define Dynami_h

#include "Dynami_Battery.h"
#include "Dynami_Bluetooth.h"
#include "Dynami_Display.h"
#include "Dynami_EnergySave.h"
#include "Dynami_Encoder.h"
#include "Dynami_Program.h"
#include "Dynami_Buttons.h"
#include "Dynami_Mediator.h"
#include "Dynami_Update.h"
#include "Dynami_Filesystem.h"
#include "Dynami_Debug.h"
#include "Dynami_Reps.h"
#include "Dynami_States.h"



class Dynami
{
public:
    Dynami();
    void dynamiSetup();
    void dynamiLoop();

private:
    Dynami_Encoder dynamiEncoder;
    Dynami_Program dynamiProgram;
    Dynami_Battery dynamiBattery;
    Dynami_Bluetooth dynamiBluetooth;
    Dynami_Display dynamiDisplay;
    Dynami_Buttons dynamiButtons;
    Dynami_EnergySave dynamiEnergySave;
    Dynami_Mediator dynamiMediator;
    Dynami_Update dynamiUpdate;
    Dynami_Filesystem dynamiFilesystem;
    Dynami_Debug dynamiDebug;
    Dynami_Reps dynamiReps;
};

#endif


//NOTES
/* Serial BT with high refresh rate is not available since it messes up with the internal clock and interrupt service of the ESP32 */