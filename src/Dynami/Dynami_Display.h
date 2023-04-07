#ifndef Dynami_Display_h
#define Dynami_Display_h

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

#include "Dynami_EnergySave.h"

#define i2c_Address 0x3c
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET -1    //   QT-PY / XIAO

// 'Untitled', 12x19px
#define LOGO16_HEIGHT 19
#define LOGO16_WIDTH 12

static const unsigned char PROGMEM bt_icon[] = {
    0x00, 0x00, 0x0f, 0x00, 0x3f, 0xc0, 0x7f, 0xe0, 0x7b, 0xe0, 0xf9, 0xf0, 0xfa, 0xf0, 0xeb, 0x70,
    0xf2, 0xf0, 0xf9, 0xf0, 0xf2, 0xf0, 0xeb, 0x70, 0xfa, 0xf0, 0xf9, 0xf0, 0x7b, 0xe0, 0x7f, 0xe0,
    0x3f, 0xc0, 0x0f, 0x00, 0x00, 0x00};

class Dynami_EnergySave;

#include "Dynami_Mediator.h";
class Dynami_Mediator;

class Dynami_Display //: public MediatedComponent
{
public:
    Dynami_Display();
    Adafruit_SH1106G display = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
    Dynami_EnergySave *dynamiEnergySave = NULL;
    void setEnergySaveRef(Dynami_EnergySave *);
    Dynami_Mediator *dynamiMediator = NULL;
    void set_mediator(Dynami_Mediator *mediator) { this->dynamiMediator = mediator; };
    uint8_t *displayBuffer = NULL;
    uint8_t *getCopyBuffer(void) { return displayBuffer; };
    void displaySetup();
    void displayLoop();
    void displayTemplate();

    void displayMPV(double MPV);
    void displayMV(double MV);
    void displayPV(double PV);
    void displayRep(unsigned int reps, unsigned int totalReps);
    void displayROM(double ROM);
    void displayPower(double Power);
    void turnOFFDisplay();
    void turnONDisplay();
    void displayBT();
    void displayBTOFF();
    void displayEmptyBattery();
    void clearBatteryIcon();
    void clearBatteryCells();
    void displayBatteryNotCharging();
    void blinkLastCell();
    void displayBatteryCharging();
    void displayBatteryChargingService();
    void batteryDisplayStatusChanged();
    void setDisplayBatteryCharging(bool);

    void displayBattery();

    void displayArrowChanged();

    void clearArrow();

    void displayArrow();

    // Update
    void displayKeyboard();

    // Globals
    int blinkTime = 700;

    // battery icon
    bool boolDisplayBatteryCharging = false;
    bool boolDisplayBatteryChargingLast = false;
    unsigned long batteryCellBlinkLastCheckTime = 0; // Battery voltage last check time
    int chargingCellsQty = 0;
    unsigned int getRepPosition(void) { return repPosition; };

    char c = 21;
    char mode = 1 ; 
    
    //menu
    void ShowMenuTitle(String);
    void ShowMenuOptions(int options, String* optionsTitles);
    void ShowCursor(int options, int cursorPos);

    //Weight input
    void ShowSelectedValueWeight(int currentPos,int weight);
    void ShowNumberCursor(int numberCursor);

    //Character String Selection
    void ShowSelectedCharacterString(int currentPos,char inputStr);
    void ShowCharCursor(char charCursor);

private:
    unsigned int repPosition = 0;
};

#endif