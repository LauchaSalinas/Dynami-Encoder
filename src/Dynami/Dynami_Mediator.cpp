#include "Dynami_Mediator.h"

Dynami_Mediator::Dynami_Mediator() {}

void Dynami_Mediator::setRefs
(Dynami_Battery *bat,           Dynami_Bluetooth *bt,   Dynami_Buttons *btns, 
Dynami_Display *dsp,            Dynami_Encoder *enc,    Dynami_EnergySave *engsv, 
Dynami_NotifyCenter *ntfcen,    Dynami_Program *prgm,   Dynami_Update *upd, Dynami_Filesystem *file)
{
    dynamiBattery = bat;
    dynamiBluetooth = bt;
    dynamiButtons = btns;
    dynamiDisplay = dsp;
    dynamiEncoder = enc;
    dynamiEnergySave = engsv;
    dynamiNotifyCenter = ntfcen;
    dynamiProgram = prgm;
    dynamiUpdate = upd;
    dynamiFilesystem = file;
    dynamiBattery->set_mediator(this);      // try to implement this later
    dynamiBluetooth->set_mediator(this);    // try to implement this later
    dynamiButtons->set_mediator(this);      // try to implement this later
    dynamiDisplay->set_mediator(this);      // try to implement this later
    dynamiEncoder->set_mediator(this);      // try to implement this later
    dynamiEnergySave->set_mediator(this);   // try to implement this later
    dynamiNotifyCenter->set_mediator(this); // try to implement this later
    dynamiProgram->set_mediator(this);      // try to implement this later
    dynamiUpdate->set_mediator(this);       // try to implement this later
    dynamiFilesystem->set_mediator(this);   // try to implement this later
}

// BATTERY INITIATED EVENTS

void Dynami_Mediator::chargerStatusChanged()
{
    if (dynamiBattery->getChargerStatus())
    {
        dynamiNotifyCenter->debugPrint("Charger connected");
        dynamiDisplay->setDisplayBatteryCharging(true);
    }
    else
    {
        dynamiNotifyCenter->debugPrint("Charger disconnected");
        dynamiDisplay->setDisplayBatteryCharging(false);
    }
}

void Dynami_Mediator::cellsQtyChanged()
{
    int cells = dynamiBattery->getCellsQty();
    //char *debugCells = strcat("Cells: ", (char *)cells);
    dynamiNotifyCenter->debugPrint("Cells: ",cells);
}

void Dynami_Mediator::batteryConnectionStatusChanged()
{
    if (dynamiBattery->getBatteryConnectionStatus())
        dynamiNotifyCenter->debugPrint("Battery connected");
    else
        dynamiNotifyCenter->debugPrint("Battery disconnected");
}

// BLUETOOTH INITIATED EVENTS

void Dynami_Mediator::bluetoothDeviceConnected()
{
    dynamiDisplay->displayBT();
    dynamiNotifyCenter->debugPrint("Device connected");
}

void Dynami_Mediator::bluetoothDeviceDisconnected()
{
    dynamiDisplay->displayBTOFF();
    dynamiNotifyCenter->debugPrint("Device disconnected");
    bluetoothStartAdvertising();
}

void Dynami_Mediator::bluetoothStartAdvertising()
{
    dynamiBluetooth->startAdvertising();
    dynamiNotifyCenter->debugPrint("Start advertising");
}

// BUTTON INITIATED EVENTS

void Dynami_Mediator::button1ShortPress()
{
    dynamiNotifyCenter->debugPrint("Button 1 Short Press");
    // dynamiEnergySave->setEnergySaveMode(true); // needs refactor
    // dynamiNotifyCenter->debugPrint("setEnergySaveMode(true)");
    dynamiUpdate->updateOTAWebServer();
}

void Dynami_Mediator::button2ShortPress()
{
    dynamiNotifyCenter->debugPrint("Button 2 Short Press");
    // programDirectionChange();
    getWifiCredentials();
    dynamiUpdate->updateStopWifi();
}

void Dynami_Mediator::button1LongPress()
{
    dynamiNotifyCenter->debugPrint("Button 1 Long Press");
    dynamiDisplay->turnOFFDisplay();
    dynamiNotifyCenter->debugPrint("Display Turned OFF");
}

void Dynami_Mediator::button2LongPress()
{
    dynamiNotifyCenter->debugPrint("Button 2 Long Press");
    dynamiEnergySave->setEnergySaveMode(false);
    dynamiNotifyCenter->debugPrint("setEnergySaveMode(false)");
}

// ENERGY SAVE
void Dynami_Mediator::energySaveModeChanged()
{
    if (dynamiEnergySave->getEnergySaveMode()) // needs refactor
    {
        dynamiNotifyCenter->debugPrint("Energy Save Mode: ON"); // needs refactor
    }
    else
    {
        dynamiNotifyCenter->debugPrint("Energy Save Mode: OFF"); // needs refactor
    }
}

// PROGRAM INITIATED EVENTS
void Dynami_Mediator::programNewRep()
{
    int sets = dynamiProgram->getSets();
    int actualRep = dynamiProgram->getActualRep();
    int targetRep = dynamiProgram->getTargetRep();
    long maxEncodedValue = dynamiEncoder->maxEncodedValue;
    long encoderValue = dynamiEncoder->encoderValue;
    int tiempoTotal = dynamiProgram->getTiempoTotal();
    int tiempoPicoTotal = dynamiProgram->getTiempoPicoTotal();
    int tiempoRetorno = dynamiProgram->getTiempoRetorno();
    char *velocity = dynamiProgram->getVelocity();
    dynamiNotifyCenter->SerialNotifyNewRep(sets, actualRep, targetRep, maxEncodedValue, encoderValue, tiempoTotal, tiempoPicoTotal, tiempoRetorno, velocity);
    // Informs Energy Save to turn ON the display
    dynamiEnergySave->energySaveNewEvent();

    // Informs display to display data NEEDS DEVELOPMENT (repets prints)
    dynamiDisplay->displayRep();
    dynamiDisplay->displaySet();
    dynamiDisplay->displayVelocity();

    // Informs BT to send new value data NEEDS DEVELOPMENT check here if device is connected
    dynamiBluetooth->BTSendValue(velocity);
}

void Dynami_Mediator::programRepCancelled()
{
    long resetValue = dynamiEncoder->getEncoderValue();
    //char *debugResetValue = strcat("Reset at: ", (char *)resetValue);
    dynamiNotifyCenter->debugPrint("Reset: ", resetValue);
}

// UPDATER

void Dynami_Mediator::getWifiCredentials()
{
    dynamiUpdate->ssid = dynamiFilesystem->getSSID();
    dynamiUpdate->password = dynamiFilesystem->getPS();
    dynamiNotifyCenter->debugPrint(dynamiUpdate->ssid);
    dynamiNotifyCenter->debugPrint(dynamiUpdate->password);
}

// Not initiated events
void Dynami_Mediator::programDirectionChange()
{
    dynamiProgram->changeArrowDirection();
    dynamiNotifyCenter->debugPrint("Arrow direction changed");
    if (dynamiProgram->getArrowDirectionUp())
        dynamiNotifyCenter->debugPrint("Arrow Direction UP");
    else
        dynamiNotifyCenter->debugPrint("Arrow Direction DOWN");
    dynamiDisplay->displayArrowChanged(); // refactor?
}

// DEBUGS

// Velocity

// void Dynami_NotifyCenter::SerialNotifyVelocity(double Velocity) {
//    Serial.print("MAX:");
//    Serial.print(1);
//    Serial.print(",");
//    Serial.print("MIN:");
//    Serial.print(0);
//    Serial.print(",");
//    Serial.print("Velocity:");
//    Serial.println(Velocity);
// }

// void Dynami_NotifyCenter::SerialNotifyDistance(double distance) {
//   Serial.println(distance);
// }

// void Dynami_NotifyCenter::SerialNotifyBatteryLevel() {
//   Serial.print("Analog = ");
//   Serial.print(dynamiBattery->batteryValue);
//   Serial.print("\t Voltage = ");
//   Serial.print(dynamiBattery->batVoltage);
//   Serial.print("\t Batt % = ");
//   Serial.print(dynamiBattery->batPercentage);
//   Serial.print("\t Cells = ");
//   Serial.println(dynamiBattery->getCellsQty());
// }

// if (DEBUG_BATTERY) SerialNotifyBatteryLevel(); NEEDS DEVELOPMENT

// getters setters ??

bool Dynami_Mediator::getArrowDirectionUp()
{
    return dynamiProgram->getArrowDirectionUp();
}