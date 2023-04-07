#ifndef Dynami_Mediator_h
#define Dynami_Mediator_h

#include <typeinfo>

#include "./abstractions/Mediator.h"

#include "Dynami_Battery.h"
#include "Dynami_Bluetooth.h"
#include "Dynami_Buttons.h"
#include "Dynami_Display.h"
#include "Dynami_Encoder.h"
#include "Dynami_EnergySave.h"
#include "Dynami_Program.h"
#include "Dynami_Update.h"
#include "Dynami_Filesystem.h"
#include "Dynami_Debug.h"
#include "Dynami_Reps.h"
#include "./abstractions/State.h"
#include "Dynami_States.h"
#include "./resources/optionMenu.h"

class Dynami_Battery;
class Dynami_Bluetooth;
class Dynami_Buttons;
class Dynami_Display;
class Dynami_Encoder;
class Dynami_EnergySave;
class Dynami_Program;
class Dynami_Update;
class Dynami_Filesystem;
class Dynami_Debug;
struct rep;
class Dynami_Reps;
class State;
struct optionMenu;

class Dynami_Mediator : Mediator
{
public:
    Dynami_Mediator();
    void setRefs(Dynami_Battery *, Dynami_Bluetooth *, Dynami_Buttons *, Dynami_Display *, Dynami_Encoder *, Dynami_EnergySave *, Dynami_Program *, Dynami_Update *, Dynami_Filesystem *, Dynami_Debug *, Dynami_Reps *);
    void Notify(BaseComponent *, std::string) override;
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
    void allButtonsLongPress();
    // DISPLAY
    // ENERGYSAVE
    void energySaveModeChanged();
    // PROGRAM
    void programNewRep();

    void programDirectionChange();

    // UPDATE

    // STATES
    //// main screen
    void PrevRep();
    void programRepCancelled();
    void NextRep();
    void ResetRepVector();
    void SwapMainParameter();

    // state menu
    void OpenMainMenu();
    void PrevOption();
    void SelectOptionMainMenu();
    void NextOption();
    int cursorOption = 0;

    // WeightInput
    void OpenWeightInput();
    void PrevNumber();
    void NextNumber();
    void SelectNumber();
    int numberCursor = 0;
    int weightSelected = 0;
    int numberPosition = 1;

    // StringInput
    void PrevChar();
    void NextChar();
    void SelectChar();
    void ConfirmString();
    char charCursor = 'A';
    String charArrSelected = "";

    // BT menu
    void OpenBluetoothMenu();
    void SelectOptionBluetoothMenu();

    // Update Menu
    void InitUpdate();
    bool ConnectToWifi();
    void UpdateDynami();
    void LaunchWebserverUpdate();
    void PopulateSSIDs();
    void SelectSSID();
    void InputPasswordSSID();
    void OpenUpdateMenu();

    // Others
    void setWifiCredentials();

    // DATA
    bool getArrowDirectionUp();

    Dynami_Battery *dynamiBattery = NULL;
    Dynami_Bluetooth *dynamiBluetooth = NULL;
    Dynami_Buttons *dynamiButtons = NULL;
    Dynami_Display *dynamiDisplay = NULL;
    Dynami_Encoder *dynamiEncoder = NULL;
    Dynami_EnergySave *dynamiEnergySave = NULL;
    Dynami_Program *dynamiProgram = NULL;
    Dynami_Update *dynamiUpdate = NULL;
    Dynami_Filesystem *dynamiFilesystem = NULL;
    Dynami_Debug *dynamiDebug = NULL;
    Dynami_Reps *dynamiReps = NULL;

private:
    State *state_ = NULL;
    void TransitionTo(State *state);

    //init screen
    void ShowInitScreen();
    //optionMenu
    std::vector<optionMenu> OptionsVector;
    int optionsVectorSize=0;
    void PopulateOptionsMainMenu();
    void PopulateOptionsUpdate();
};

#endif