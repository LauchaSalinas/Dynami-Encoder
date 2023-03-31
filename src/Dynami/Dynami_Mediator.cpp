#include "Dynami_Mediator.h"

Dynami_Mediator::Dynami_Mediator() {}

void Dynami_Mediator::setRefs(Dynami_Battery *bat, Dynami_Bluetooth *bt, Dynami_Buttons *btns,
                              Dynami_Display *dsp, Dynami_Encoder *enc, Dynami_EnergySave *engsv,
                              Dynami_NotifyCenter *ntfcen, Dynami_Program *prgm, Dynami_Update *upd,
                              Dynami_Filesystem *file, Dynami_Debug *debug, Dynami_Reps *reps)
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
    dynamiDebug = debug;
    dynamiReps = reps;
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
    dynamiDebug->set_mediator(this);        // try to implement this later
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
    // char *debugCells = strcat("Cells: ", (char *)cells);
    dynamiNotifyCenter->debugPrint("Cells: ", cells);
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
    dynamiProgram->resetRepValues();
    // dynamiDebug->set_debug_velocity_status(true);
    // dynamiDebug->set_debug_distance_status(false);
}

void Dynami_Mediator::button2ShortPress()
{
    dynamiNotifyCenter->debugPrint("Button 2 Short Press");
    // dynamiDebug->set_debug_velocity_status(false);
    // dynamiDebug->set_debug_distance_status(true);

    // dynamiProgram->distanceMeasurementFrec = dynamiProgram->distanceMeasurementFrec + 1000;
    // dynamiProgram->velocityMeasurementFrec = dynamiProgram->distanceMeasurementFrec * 2;
    // dynamiProgram->accelerationMeasurementFrec = dynamiProgram->velocityMeasurementFrec * 2;

    // dynamiProgram->velocityFilterFreq = dynamiProgram->velocityFilterFreq - 0.1F;
    // dynamiProgram->velocityLowPassFilter.setCutOffFreq(dynamiProgram->velocityFilterFreq);

    unsigned int repPosition = dynamiDisplay->getRepPosition() - 1; // 6
    int repCounter = dynamiReps->GetRepCounter();                   // 5
    rep newRep;
    if (repPosition <= 0)
        return;
    // shows best if we are in mean screen
    if (repPosition == repCounter + 2)
    {
        newRep = dynamiReps->GetRepBest();
    }
    if (repPosition <= repCounter + 1)
    {
        newRep = dynamiReps->GetRepInfo(repPosition - 1);
    }

    dynamiDisplay->displayRep(repPosition, repCounter + 1);
    dynamiDisplay->displayROM(newRep.ROM);
    dynamiDisplay->displayMPV(newRep.MPV);
    dynamiDisplay->displayMV(newRep.MV);
    dynamiDisplay->displayPV(newRep.PV);
    dynamiDisplay->displayPower(newRep.Power);
}

void Dynami_Mediator::button3ShortPress()
{
    dynamiNotifyCenter->debugPrint("Button 3 Short Press");
    // dynamiProgram->velocityFilterFreq = dynamiProgram->velocityFilterFreq + 1.0F;
    // dynamiProgram->velocityLowPassFilter.setCutOffFreq(dynamiProgram->velocityFilterFreq);

    // dynamiProgram->distanceMeasurementFrec = 1000;
    // dynamiProgram->distanceMeasurementFrec = dynamiProgram->distanceMeasurementFrec ;
    // dynamiProgram->velocityMeasurementFrec = dynamiProgram->distanceMeasurementFrec ;
    // dynamiProgram->accelerationMeasurementFrec = dynamiProgram->distanceMeasurementFrec ;

    unsigned int repPosition = dynamiDisplay->getRepPosition() - 1; // 7
    int repCounter = dynamiReps->GetRepCounter();                   // 5
    rep newRep;
    if (repPosition >= repCounter + 2)
        return;
    if (repPosition == repCounter)
    {
        newRep = dynamiReps->GetRepBest();
    }
    if (repPosition == repCounter + 1)
    {
        newRep = dynamiReps->GetRepMean();
    }
    if (repPosition < repCounter)
    {
        newRep = dynamiReps->GetRepInfo(repPosition + 1);
    }
    dynamiDisplay->displayRep(repPosition + 1 + 1, repCounter + 1);
    dynamiDisplay->displayROM(newRep.ROM);
    dynamiDisplay->displayMPV(newRep.MPV);
    dynamiDisplay->displayMV(newRep.MV);
    dynamiDisplay->displayPV(newRep.PV);
    dynamiDisplay->displayPower(newRep.Power);
}

void Dynami_Mediator::button1LongPress()
{
    dynamiNotifyCenter->debugPrint("Button 1 Long Press");
    dynamiProgram->resetRepValues();
}

void Dynami_Mediator::button2LongPress()
{
    dynamiNotifyCenter->debugPrint("Button 2 Long Press");
    dynamiProgram->velocityMeasurementFrec = dynamiProgram->velocityMeasurementFrec + 1;
    Serial.println(dynamiProgram->velocityMeasurementFrec);
}

void Dynami_Mediator::button3LongPress()
{
    dynamiNotifyCenter->debugPrint("Button 3 Long Press");
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
    // DELETE int sets = dynamiProgram->getSets();
    // DELETE int actualRep = dynamiProgram->getActualRep();
    // DELETE int targetRep = dynamiProgram->getTargetRep();
    // long maxEncodedValue = dynamiEncoder->maxEncodedValue;
    // long encoderValue = dynamiEncoder->encoderValue;
    // DELETE int tiempoTotal = dynamiProgram->getTiempoTotal();
    // DELETE int tiempoPicoTotal = dynamiProgram->getTiempoPicoTotal();
    // DELETE int tiempoRetorno = dynamiProgram->getTiempoRetorno();
    // DELETE char *velocity = dynamiProgram->getVelocity();

    // delete dynamiNotifyCenter->SerialNotifyNewRep(sets, actualRep, targetRep, maxEncodedValue, encoderValue, tiempoTotal, tiempoPicoTotal, tiempoRetorno, velocity);
    // Informs Energy Save to turn ON the display
    dynamiEnergySave->energySaveNewEvent();

    // Informs display to display data NEEDS DEVELOPMENT (repets prints)
    // DELETE dynamiDisplay->displayVelocity();

    // Informs BT to send new value data NEEDS DEVELOPMENT check here if device is connected
    // dynamiBluetooth->BTSendValue();

    rep newRep{
        dynamiProgram->getMPV(),
        dynamiProgram->getMV(),
        dynamiProgram->getPV(),
        dynamiProgram->getROM(),
        dynamiProgram->getPower()};

    dynamiReps->AddNewRep(newRep);
    int repCounter = dynamiReps->GetRepCounter();
    dynamiDisplay->displayRep(repCounter + 1, repCounter + 1);
    dynamiDisplay->displayROM(newRep.ROM);
    dynamiDisplay->displayMPV(newRep.MPV);
    dynamiDisplay->displayMV(newRep.MV);
    dynamiDisplay->displayPV(newRep.PV);
    dynamiDisplay->displayPower(newRep.Power);
}

void Dynami_Mediator::programRepCancelled()
{
    long resetValue = dynamiEncoder->getEncoderValue();
    // char *debugResetValue = strcat("Reset at: ", (char *)resetValue);
    dynamiNotifyCenter->debugPrint("Reset: ", resetValue);
}

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

// UPDATER

// getters setters (delete this?)

void Dynami_Mediator::UpdateDynami()
{
    // Checks if SSID is an available wifi in the area, if so, connect using the stored credentials.
    // If stored password was incorrect of wifi not available , ask for the credentials, if connection is successful stores the wifi credentials.
    // if update is unsuccessful, turns off wifi.
    bool newCredentials = false;
    // START
    dynamiUpdate->StartWifi();

    // GetStoredWifiCredentials();
    dynamiUpdate->ssid = dynamiFilesystem->getSSID();
    dynamiUpdate->password = dynamiFilesystem->getPS();
    dynamiNotifyCenter->debugPrint(dynamiUpdate->ssid);
    dynamiNotifyCenter->debugPrint(dynamiUpdate->password);

    // Converts Arduino String to char * NEEDS REFACTOR, should be all char* not arduino strings
    char charArray[dynamiUpdate->ssid.length() + 1];
    dynamiUpdate->ssid.toCharArray(charArray, dynamiUpdate->ssid.length() + 1);

    // stores bool after wifi scan
    // checks if ssid is in the wifi area
    bool isSSIDAvaible = dynamiUpdate->CheckSSIDinAvailableSSIDs(charArray);

    // if SSID is not in the area checks for credentials
    if (!isSSIDAvaible)
    {
        dynamiNotifyCenter->debugPrint("SSID not available");

        // AskWifiCredentials();
        // NEEDS DEVELOPMENT, meanwhile will be trought serial debug
        dynamiNotifyCenter->debugPrint("new SSID:");
        dynamiUpdate->ssid = "Upside24"; // dynamiDebug->AskNewString();
        dynamiNotifyCenter->debugPrint(dynamiUpdate->ssid);

        dynamiNotifyCenter->debugPrint("new PS");
        dynamiUpdate->password = "1234223432344234"; // dynamiDebug->AskNewString();
        dynamiNotifyCenter->debugPrint(dynamiUpdate->password);

        newCredentials = true;
    }

    // ConnectWifi();
    dynamiUpdate->ConnectWifi();

    bool wifiConnected = dynamiUpdate->IsWifiConnected();
    int tries = 2;
    while (!wifiConnected && tries > 0)
    {
        dynamiUpdate->ConnectWifi();
        dynamiNotifyCenter->debugPrint(dynamiUpdate->get_wifi_status());
        wifiConnected = dynamiUpdate->IsWifiConnected();
        tries--;
    }
    // if connection is successful and credentials are new, stores the wifi credentials.
    if (wifiConnected)
    {
        dynamiNotifyCenter->debugPrint("Wifi is connected");
        if (newCredentials)
        {
            // StoreWifiCredentials();
            dynamiFilesystem->writeSSID(dynamiUpdate->ssid);
            dynamiFilesystem->writePS(dynamiUpdate->password);
        }

        const int webVersion = dynamiUpdate->CheckWebVersion();
        if (dynami_firmware_version_ < webVersion)
        {
            dynamiNotifyCenter->debugPrint("Theres a new version available, do you want to update? Y/N");
            if (dynamiDebug->GetCharYN())
            {
                dynamiUpdate->StartHTTPUpdate();
            }
            else
            {
                dynamiNotifyCenter->debugPrint("Server update canceled, Starting OTA Server for manual upload");
                dynamiUpdate->updateOTAWebServer();
            }
        }
        else
        {
            dynamiNotifyCenter->debugPrint("You're up to date, Starting OTA Server for manual upload");
            dynamiUpdate->updateOTAWebServer();
        }
    }
    // if update is unsuccessful, turns off wifi and closes the HTTP server
    else
    {
        dynamiNotifyCenter->debugPrint("Was not able to connect to wifi");
        dynamiUpdate->updateStopWifi();
    }
}

bool Dynami_Mediator::getArrowDirectionUp()
{
    return dynamiProgram->getArrowDirectionUp();
}