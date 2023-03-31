#ifndef Dynami_Mediator_h
#define Dynami_Mediator_h

#include "Dynami_Battery.h"
#include "Dynami_Bluetooth.h"
#include "Dynami_Buttons.h"
#include "Dynami_Display.h"
#include "Dynami_Encoder.h"
#include "Dynami_EnergySave.h"
#include "Dynami_NotifyCenter.h"
#include "Dynami_Program.h"
#include "Dynami_Update.h"
#include "Dynami_Filesystem.h"
#include "Dynami_Debug.h"
#include "Dynami_Reps.h"

class Dynami_Battery;
class Dynami_Bluetooth;
class Dynami_Buttons;
class Dynami_Display;
class Dynami_Encoder;
class Dynami_EnergySave;
class Dynami_NotifyCenter;
class Dynami_Program;
class Dynami_Update;
class Dynami_Filesystem;
class Dynami_Debug;
struct rep;
class Dynami_Reps;

class Dynami_Mediator
{
public:
    Dynami_Mediator();
    void setRefs(Dynami_Battery *, Dynami_Bluetooth *, Dynami_Buttons *, Dynami_Display *, Dynami_Encoder *, Dynami_EnergySave *, Dynami_NotifyCenter *, Dynami_Program *, Dynami_Update *, Dynami_Filesystem *, Dynami_Debug *, Dynami_Reps *);
    void chargerStatusChanged();
    void cellsQtyChanged();
    void batteryConnectionStatusChanged();
    // BT
    void bluetoothDeviceConnected();
    void bluetoothDeviceDisconnected();
    void bluetoothStartAdvertising();
    // BUTTONS
    void button1ShortPress();
    void button2ShortPress();
    void button3ShortPress();
    void button1LongPress();
    void button2LongPress();
    void button3LongPress();
    // DISPLAY
    // ENERGYSAVE
    void energySaveModeChanged();
    // PROGRAM
    void programNewRep();
    void programRepCancelled();
    void programDirectionChange();
    // UPDATE

    // OTHER
    void setWifiCredentials();
    void UpdateDynami();

    // DATA
    bool getArrowDirectionUp();

    Dynami_Battery *dynamiBattery = NULL;
    Dynami_Bluetooth *dynamiBluetooth = NULL;
    Dynami_Buttons *dynamiButtons = NULL;
    Dynami_Display *dynamiDisplay = NULL;
    Dynami_Encoder *dynamiEncoder = NULL;
    Dynami_EnergySave *dynamiEnergySave = NULL;
    Dynami_NotifyCenter *dynamiNotifyCenter = NULL;
    Dynami_Program *dynamiProgram = NULL;
    Dynami_Update *dynamiUpdate = NULL;
    Dynami_Filesystem *dynamiFilesystem = NULL;
    Dynami_Debug *dynamiDebug = NULL;
    Dynami_Reps *dynamiReps = NULL;
};

#endif