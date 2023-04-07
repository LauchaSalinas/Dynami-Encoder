#include "Dynami_Mediator.h"

Dynami_Mediator::Dynami_Mediator()
{
    TransitionTo(new View_Reps);
}

void Dynami_Mediator::setRefs(Dynami_Battery *bat, Dynami_Bluetooth *bt, Dynami_Buttons *btns,
                              Dynami_Display *dsp, Dynami_Encoder *enc, Dynami_EnergySave *engsv,
                              Dynami_Program *prgm, Dynami_Update *upd,
                              Dynami_Filesystem *file, Dynami_Debug *debug, Dynami_Reps *reps)
{
    dynamiBattery = bat;
    dynamiBluetooth = bt;
    dynamiButtons = btns;
    dynamiDisplay = dsp;
    dynamiEncoder = enc;
    dynamiEnergySave = engsv;
    dynamiProgram = prgm;
    dynamiUpdate = upd;
    dynamiFilesystem = file;
    dynamiDebug = debug;
    dynamiReps = reps;
    dynamiBattery->set_mediator(this);
    dynamiBluetooth->set_mediator(this);
    dynamiButtons->set_mediator(this);
    dynamiDisplay->set_mediator(this);
    dynamiEncoder->set_mediator(this);
    dynamiEnergySave->set_mediator(this);
    dynamiProgram->set_mediator(this);
    dynamiUpdate->set_mediator(this);
    dynamiFilesystem->set_mediator(this);
    dynamiDebug->set_mediator(this);
}

void Dynami_Mediator::Notify(BaseComponent *sender, std::string event)
{
    if (event == "cellsQtyChanged")
        cellsQtyChanged();
    if (event == "batteryConnectionStatusChanged")
        batteryConnectionStatusChanged();
    if (event == "chargerStatusChanged")
        chargerStatusChanged();
}

// BATTERY INITIATED EVENTS

void Dynami_Mediator::chargerStatusChanged()
{
    if (dynamiBattery->getChargerStatus())
    {
        Serial.println("Charger connected");
        dynamiDisplay->setDisplayBatteryCharging(true);
    }
    else
    {
        Serial.println("Charger disconnected");
        dynamiDisplay->setDisplayBatteryCharging(false);
    }
}

void Dynami_Mediator::cellsQtyChanged()
{
    int cells = dynamiBattery->getCellsQty();
    // char *debugCells = strcat("Cells: ", (char *)cells);
    Serial.println("Cells: " + cells);
}

void Dynami_Mediator::batteryConnectionStatusChanged()
{
    if (dynamiBattery->getBatteryConnectionStatus())
        Serial.println("Battery connected");
    else
        Serial.println("Battery disconnected");
}

// BLUETOOTH INITIATED EVENTS

void Dynami_Mediator::bluetoothDeviceConnected()
{
    dynamiDisplay->displayBT();
    Serial.println("Device connected");
}

void Dynami_Mediator::bluetoothDeviceDisconnected()
{
    dynamiDisplay->displayBTOFF();
    Serial.println("Device disconnected");
    bluetoothStartAdvertising();
}

void Dynami_Mediator::bluetoothStartAdvertising()
{
    dynamiBluetooth->startAdvertising();
    Serial.println("Start advertising");
}

// BUTTON INITIATED EVENTS

void Dynami_Mediator::button1ShortPress()
{
    Serial.println("Button 1 Short Press");

    // dynamiDebug->set_debug_velocity_status(true);
    // dynamiDebug->set_debug_distance_status(false);

    // if (dynamiDisplay->mode == 1)
    // {
    //     dynamiProgram->resetRepValues();
    // }
    state_->Button1ShortPress();
}

void Dynami_Mediator::button2ShortPress()
{
    Serial.println("Button 2 Short Press");
    // dynamiDebug->set_debug_velocity_status(false);
    // dynamiDebug->set_debug_distance_status(true);

    // dynamiProgram->distanceMeasurementFrec = dynamiProgram->distanceMeasurementFrec + 1000;
    // dynamiProgram->velocityMeasurementFrec = dynamiProgram->distanceMeasurementFrec * 2;
    // dynamiProgram->accelerationMeasurementFrec = dynamiProgram->velocityMeasurementFrec * 2;

    // dynamiProgram->velocityFilterFreq = dynamiProgram->velocityFilterFreq - 0.1F;
    // dynamiProgram->velocityLowPassFilter.setCutOffFreq(dynamiProgram->velocityFilterFreq);
    state_->Button2ShortPress();
}

void Dynami_Mediator::button3ShortPress()
{
    Serial.println("Button 3 Short Press");
    // dynamiProgram->velocityFilterFreq = dynamiProgram->velocityFilterFreq + 1.0F;
    // dynamiProgram->velocityLowPassFilter.setCutOffFreq(dynamiProgram->velocityFilterFreq);

    // dynamiProgram->distanceMeasurementFrec = 1000;
    // dynamiProgram->distanceMeasurementFrec = dynamiProgram->distanceMeasurementFrec ;
    // dynamiProgram->velocityMeasurementFrec = dynamiProgram->distanceMeasurementFrec ;
    // dynamiProgram->accelerationMeasurementFrec = dynamiProgram->distanceMeasurementFrec ;
    state_->Button3ShortPress();
}

void Dynami_Mediator::button1LongPress()
{
    Serial.println("Button 1 Long Press");
    // dynamiProgram->resetRepValues();
    state_->Button1LongPress();
}

void Dynami_Mediator::button2LongPress()
{
    Serial.println("Button 2 Long Press");
    state_->Button2LongPress();
    // dynamiProgram->velocityMeasurementFrec = dynamiProgram->velocityMeasurementFrec + 1;
    // Serial.println(dynamiProgram->velocityMeasurementFrec);

    // dynamiDebug->set_debug_velocity_status(false);

    // Our duplicate buffer

    // ...draw bitmaps, images, etc and show with display.display();...
    // // // dynamiDisplay->display.clearDisplay();
    // // // dynamiDisplay->display.display();
    // // // dynamiDisplay->display.setTextSize(2);
    // // // dynamiDisplay->display.setCursor(0, 0);
    // // // dynamiDisplay->display.println("UPDATE");
    // // // dynamiDisplay->display.display();

    // Copy over the contents of the display buffer to the duplicate
    // memcpy(dynamiDisplay->getCopyBuffer(), dynamiDisplay->display.getBuffer(), ((SCREEN_WIDTH * SCREEN_HEIGHT + 7) / 8));

    // // // delay(2000);

    // // Copy back from the duplicate buffer
    // memcpy(dynamiDisplay->display.getBuffer(), dynamiDisplay->getCopyBuffer(), ((SCREEN_WIDTH * (SCREEN_HEIGHT)) / 8));
    // // Display it
    // dynamiDisplay->display.display();

    // Serial.println("Copia");
    // buffer = dynamiDisplay->getCopyBuffer();
    // for (int i = 0; i < ((SCREEN_WIDTH * (SCREEN_HEIGHT)) / 8); i++)
    // {
    //     printf("%02hhX ", buffer[i]);
    // }
    // Serial.println();
    // buffer2 = dynamiDisplay->display.getBuffer();
    // Serial.println("Original");
    // for (int i = 0; i < ((SCREEN_WIDTH * (SCREEN_HEIGHT)) / 8); i++)
    // {
    //     printf("%02hhX ", buffer2[i]);
    // }
    // Serial.println();
}

void Dynami_Mediator::button3LongPress()
{
    Serial.println("Button 3 Long Press");
    state_->Button3LongPress();

    // Serial.println("Button 3 Long Press");
    // // dynamiDisplay->display.drawBitmapVertical(0,0,dynamiDisplay->getCopyBuffer(),128,64,1);
    // dynamiDisplay->display.fillRect(0, 0, 128, 64, 1);
    // dynamiDisplay->display.display(dynamiDisplay->getCopyBuffer());
    // Serial.println("Copia");
    // uint8_t *buffer = dynamiDisplay->getCopyBuffer();
    // for (int i = 0; i < 1024; i++)
    // {
    //     printf("%02hhX", buffer[i]);
    //     delay(1);
    // }
    // Serial.println();
}

void Dynami_Mediator::allButtonsLongPress()
{
    Serial.println("All Buttons Long Press");
}

void Dynami_Mediator::PrevRep()
{
    Serial.printf("PrevRep\n");
    int repPosition = dynamiDisplay->getRepPosition() - 1; // 6
    int repCounter = dynamiReps->GetRepCounter();          // 5
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

void Dynami_Mediator::NextRep()
{
    Serial.printf("NextRep\n");
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

// ENERGY SAVE
void Dynami_Mediator::energySaveModeChanged()
{
    if (dynamiEnergySave->getEnergySaveMode()) // needs refactor
    {
        Serial.println("Energy Save Mode: ON"); // needs refactor
    }
    else
    {
        Serial.println("Energy Save Mode: OFF"); // needs refactor
    }
}

// PROGRAM INITIATED EVENTS
void Dynami_Mediator::programNewRep()
{
    // Informs Energy Save to turn ON the display
    dynamiEnergySave->energySaveNewEvent();

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
    Serial.printf("ResetEncoder\n");
    long resetValue = dynamiEncoder->getEncoderValue();
    // char *debugResetValue = strcat("Reset at: ", (char *)resetValue);
    Serial.printf("Reset: %d\n", resetValue);
}

// UPDATER

void Dynami_Mediator::UpdateDynami()
{
    const int webVersion = dynamiUpdate->CheckWebVersion();
    if (dynami_firmware_version_ < webVersion)
    {
        Serial.println("Theres a new version available, do you want to update? Y/N");
        dynamiUpdate->StartHTTPUpdate();
    }
}

void Dynami_Mediator::LaunchWebserverUpdate(){
    dynamiUpdate->updateOTAWebServer();
}

bool Dynami_Mediator::ConnectToWifi()
{

    Serial.println(dynamiUpdate->ssid);
    Serial.println(dynamiUpdate->password);

    // ConnectWifi();
    dynamiUpdate->ConnectWifi();

    bool wifiConnected = dynamiUpdate->IsWifiConnected();
    int tries = 2;
    while (!wifiConnected && tries > 0)
    {
        dynamiUpdate->ConnectWifi();
        Serial.println(dynamiUpdate->get_wifi_status());
        wifiConnected = dynamiUpdate->IsWifiConnected();
        tries--;
    }
    // if connection is successful and credentials are new, stores the wifi credentials.
    if (wifiConnected)
    {
        Serial.println("Wifi is connected");
        return true;
        // go to update menu
    }
    // if update is unsuccessful, turns off wifi and closes the HTTP server
    else
    {
        Serial.println("Was not able to connect to wifi");
        return false;
        dynamiUpdate->TurnOffWifi();

        // cambio a estado main menu
    }
}

void Dynami_Mediator::ResetRepVector()
{
}

void Dynami_Mediator::SwapMainParameter()
{
}

// INIT SCREEN
void Dynami_Mediator::ShowInitScreen()
{
    TransitionTo(new View_Reps); // this could be the same state, since i can change the options
    Serial.printf("Context: Transition to %s\n", "View_Reps");
    dynamiDisplay->display.display(dynamiDisplay->getCopyBuffer());
}

// STATE MENU
void Dynami_Mediator::OpenMainMenu()
{
    TransitionTo(new MenuSelectOptionState);
    Serial.printf("Context: Transition to %s\n", "MainMenuState");

    PopulateOptionsMainMenu();
    cursorOption = 0;

    // DEBUG
    Serial.printf("INDEX\tNAME\n");
    for (auto &option : OptionsVector)
    {
        Serial.printf("%s\n", option.optionName);
    }

    // DISPLAY
    dynamiDisplay->display.clearDisplay();
    dynamiDisplay->display.display();
    dynamiDisplay->ShowMenuTitle("MAIN MENU");
    String optionTitles[optionsVectorSize];
    for (int i = 0; i < optionsVectorSize; i++)
    {
        optionTitles[i] = OptionsVector[i].optionName;
    }
    dynamiDisplay->ShowMenuOptions(optionsVectorSize, optionTitles);
    dynamiDisplay->ShowCursor(optionsVectorSize, cursorOption);
}

// OPTIONS

void Dynami_Mediator::PopulateOptionsMainMenu()
{
    OptionsVector.clear();
    optionMenu optionObject;
    OptionsVector.push_back(optionObject = {"WEIGHT", &Dynami_Mediator::OpenWeightInput});
    OptionsVector.push_back(optionObject = {"BLUETOOTH", &Dynami_Mediator::OpenBluetoothMenu});
    OptionsVector.push_back(optionObject = {"CALIBRATION", NULL});
    OptionsVector.push_back(optionObject = {"DISPLAY", NULL});
    OptionsVector.push_back(optionObject = {"UPDATE", &Dynami_Mediator::InitUpdate});
    OptionsVector.push_back(optionObject = {"EXIT", &Dynami_Mediator::ShowInitScreen});
    optionsVectorSize = OptionsVector.size();
}

void Dynami_Mediator::PopulateOptionsUpdate()
{
    OptionsVector.clear();
    optionMenu optionObject;
    OptionsVector.push_back(optionObject = {"CHECK UPDATES", &Dynami_Mediator::UpdateDynami});
    OptionsVector.push_back(optionObject = {"WEBSERVER UPDATE", &Dynami_Mediator::LaunchWebserverUpdate});
    OptionsVector.push_back(optionObject = {"BACK", &Dynami_Mediator::OpenMainMenu});
    optionsVectorSize = OptionsVector.size();
}

void Dynami_Mediator::PopulateSSIDs()
{
    OptionsVector.clear();
    optionMenu optionObject;
    Serial.print("degub1");
    dynamiUpdate->ScanSSID();

    int n = dynamiUpdate->nNetworks;
    if (n == 0)
    {
        Serial.println("no networks");
        dynamiUpdate->TurnOffWifi();
        OpenMainMenu();
    }

    Serial.println("degub5");

    for (int i = 0; i < n; i++)
    {
        OptionsVector.push_back(optionObject = {dynamiUpdate->AvailableSSIDs[i], &Dynami_Mediator::SelectSSID});
    }
    OptionsVector.push_back(optionObject = {"EXIT", &Dynami_Mediator::OpenMainMenu});

    optionsVectorSize = OptionsVector.size();
}

void Dynami_Mediator::PrevOption()
{
    cursorOption--;
    if (cursorOption < 0)
        cursorOption = optionsVectorSize - 1;
    Serial.printf("Option: %d\n", cursorOption);
    dynamiDisplay->ShowCursor(optionsVectorSize, cursorOption);
}

void Dynami_Mediator::NextOption()
{
    cursorOption++;
    if (cursorOption >= optionsVectorSize)
        cursorOption = 0;
    Serial.printf("Option: %d\n", cursorOption);
    dynamiDisplay->ShowCursor(optionsVectorSize, cursorOption);
}
void Dynami_Mediator::SelectOptionMainMenu()
{
    if (OptionsVector[cursorOption].func_ptr != NULL)
        (this->*(OptionsVector[cursorOption].func_ptr))();

    // for (auto &option : OptionsVector)
    // {
    //     if (option.index == cursorOption)
    //     {
    //         Serial.printf("Option selected: %s\n", option.optionName);
    //         (this->*(option.func_ptr))();
    //     }
    // }
}

void Dynami_Mediator::SelectSSID()
{
    dynamiUpdate->ssid = dynamiUpdate->AvailableSSIDs[cursorOption];

    if (dynamiFilesystem->getSSID() == dynamiUpdate->ssid)
    {
        dynamiUpdate->password = dynamiFilesystem->getPS();

        bool connected = ConnectToWifi();
        if (connected)
            OpenUpdateMenu();
        else
        {
            dynamiUpdate->TurnOffWifi();
            Serial.print("Not able to connect");
            OpenMainMenu();
        }
    }
    else
    {
        InputPasswordSSID();
    }
}

void Dynami_Mediator::InputPasswordSSID()
{
    TransitionTo(new Select_Chars);
    Serial.printf("Context: Transition to %s\n", "Select_Chars");
    dynamiDisplay->display.clearDisplay();
    dynamiDisplay->display.display();
    dynamiDisplay->ShowMenuTitle("PASSWORD");
    dynamiDisplay->ShowSelectedCharacterString(0, ' ');
    dynamiDisplay->ShowCharCursor(charCursor);
}

// weight

void Dynami_Mediator::OpenWeightInput()
{
    TransitionTo(new WeightInputState);
    Serial.printf("Context: Transition to %s\n", "WeightInputState");
    weightSelected = 0;
    // DISPLAY
    dynamiDisplay->display.clearDisplay();
    dynamiDisplay->display.display();
    dynamiDisplay->ShowMenuTitle("WEIGHT");

    numberPosition = 0;
    dynamiDisplay->ShowSelectedValueWeight(weightSelected, 0);
    dynamiDisplay->ShowNumberCursor(numberCursor);
}

void Dynami_Mediator::InitUpdate()
{
    // Select SSID
    TransitionTo(new MenuSelectOptionState);
    Serial.printf("Context: Transition to %s\n", "MenuSelectOptionState");
    dynamiDisplay->display.clearDisplay();
    dynamiDisplay->display.display();
    dynamiDisplay->ShowMenuTitle("WIFI");
    cursorOption = 0;
    PopulateSSIDs();

    Serial.printf("INDEX\tNAME\n");
    for (auto &option : OptionsVector)
    {
        Serial.printf("%s\n", option.optionName.c_str());
    }

    // DISPLAY
    String optionTitles[optionsVectorSize];
    for (int i = 0; i < optionsVectorSize; i++)
    {
        optionTitles[i] = OptionsVector[i].optionName;
    }
    dynamiDisplay->ShowMenuOptions(optionsVectorSize, optionTitles);
    dynamiDisplay->ShowCursor(optionsVectorSize, cursorOption);
}

void Dynami_Mediator::OpenUpdateMenu()
{
    TransitionTo(new MenuSelectOptionState);
    Serial.printf("Context: Transition to %s\n", "MenuSelectOptionState");
    dynamiDisplay->display.clearDisplay();
    dynamiDisplay->display.display();
    dynamiDisplay->ShowMenuTitle("UPDATE");
    PopulateOptionsUpdate();

    cursorOption = 0;

    // DEBUG
    Serial.printf("INDEX\tNAME\n");
    for (auto &option : OptionsVector)
    {
        Serial.printf("%s\n", option.optionName);
    }

    // DISPLAY
    String optionTitles[optionsVectorSize];
    for (int i = 0; i < optionsVectorSize; i++)
    {
        optionTitles[i] = OptionsVector[i].optionName;
    }
    dynamiDisplay->ShowMenuOptions(optionsVectorSize, optionTitles);
    dynamiDisplay->ShowCursor(optionsVectorSize, cursorOption);
}

void Dynami_Mediator::PrevNumber()
{
    numberCursor--;
    if (numberCursor <= -1)
        numberCursor = 0;
    Serial.printf("Number: %d\n", numberCursor);
    dynamiDisplay->ShowNumberCursor(numberCursor);
}

void Dynami_Mediator::NextNumber()
{
    numberCursor++;
    if (numberCursor >= 10)
        numberCursor = 9;
    Serial.printf("Number: %d\n", numberCursor);
    dynamiDisplay->ShowNumberCursor(numberCursor);
}

void Dynami_Mediator::SelectNumber()
{
    numberPosition++;
    weightSelected = weightSelected * 10 + numberCursor;
    Serial.printf("Weight: %d\n", weightSelected);
    dynamiDisplay->ShowSelectedValueWeight(numberPosition, weightSelected);
    if (numberPosition == 3)
    {
        Serial.printf("Final weight: %d\n", weightSelected);
        dynamiProgram->setWeight(weightSelected);
        delay(1000); // DELETE THIS
        OpenMainMenu();
    }
}

// String input

void Dynami_Mediator::PrevChar()
{
    char lowerLimit = 32;
    char upperLimit = 127;
    if (charCursor == lowerLimit)
        charCursor = upperLimit;
    else
        charCursor--;
    Serial.printf("Character: %c\n", charCursor);
    dynamiDisplay->ShowCharCursor(charCursor);
}

void Dynami_Mediator::NextChar()
{
    char lowerLimit = 32;
    char upperLimit = 127;
    if (charCursor == upperLimit)
        charCursor = lowerLimit;
    else
        charCursor++;
    Serial.printf("Character: %c\n", charCursor);
    dynamiDisplay->ShowCharCursor(charCursor);
}

void Dynami_Mediator::SelectChar()
{
    charArrSelected = charArrSelected + charCursor;
    int size = charArrSelected.length();
    dynamiDisplay->ShowSelectedCharacterString(size, charCursor);
    Serial.printf("String: %s\n", charArrSelected);
}

void Dynami_Mediator::ConfirmString()
{
    dynamiUpdate->password = charArrSelected;
    bool connected = ConnectToWifi();
    if (connected)
    {
        dynamiFilesystem->writeSSID(dynamiUpdate->ssid);
        dynamiFilesystem->writePS(dynamiUpdate->password);
        OpenUpdateMenu();
    }
    else
    {
        Serial.println("cant connect");
        dynamiUpdate->TurnOffWifi();
        OpenMainMenu();
    }
}

// Bluetooth Sub Menu

void Dynami_Mediator::OpenBluetoothMenu()
{
    TransitionTo(new MenuSelectOptionState);
    Serial.printf("Context: Transition to %s\n", "BluetoothState");
    cursorOption = 0;
}

void Dynami_Mediator::SelectOptionBluetoothMenu()
{
    switch (cursorOption)
    {
    case 1: // bt1();
        break;
    case 2: // bt2();
        break;
    case 3: // bt3();
        break;
    case 4: // exit();
        break;
    }
}

// display memory buffer

// uint8_t *buffer2 = display.getBuffer();
// Serial.println("Original");
// for (int i = 0; i < 1024; i++)
// {
//   printf("%02hhX", buffer2[i]);
//   delay(1);
// }
// Serial.println();
// Serial.println("Copia");
// uint8_t *buffer = getCopyBuffer();
// for (int i = 0; i < 1024; i++)
// {
//   printf("%02hhX", buffer[i]);
//   delay(1);
// }
// Serial.println();

void Dynami_Mediator::TransitionTo(State *state)
{
    if (this->state_ != nullptr)
        delete this->state_;
    this->state_ = state;
    this->state_->set_context(this);
}