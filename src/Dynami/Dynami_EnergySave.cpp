#include "Dynami_EnergySave.h"

Dynami_EnergySave::Dynami_EnergySave()
{
}

void Dynami_EnergySave::setDisplayRef(Dynami_Display *dsp)
{
    dinamyDisplay = dsp;
}

// Every time we set the Energy Save ON we start this routine,
// stores the time when we started the service.
//
// Checks if energySaveMode is true since we could start the device without the mode enabled.
// then sets the variables indicating that the display is already on, and previous to that, it was on. If not, it will turn it again.
void Dynami_EnergySave::startEnergySaveModeService()
{
    energySaveLastCheckTime = millis() + energySaveTimeON; // time added to avoid the screen to start turned off
    if (energySaveMode)
    {
        energySaveDisplayStatus = true;
        energySaveDisplayStatusLast = true;
    }
}

void Dynami_EnergySave::energySaveModeDisplay()
{
    if (!energySaveMode)
        dinamyDisplay->display.display();
    else if (energySaveMode && energySaveDisplayStatus)
        dinamyDisplay->display.display();
}

void Dynami_EnergySave::energySaveLoop()
{
    energySaveService();
    if (energySaveMode)
    {
        if (energySaveDisplayStatus)
        {
            energySaveSetDisplayON();
        }
        else
            energySaveSetDisplayOFF();
    }
}

// turns on the screen only once
void Dynami_EnergySave::energySaveSetDisplayON()
{
    if (!energySaveMode)
        return;
    if (energySaveDisplayStatus == true && energySaveDisplayStatusLast == false)
    {
        energySaveDisplayStatusLast = true;
        dinamyDisplay->turnONDisplay();
    }
}

// turns off the screen only once
void Dynami_EnergySave::energySaveSetDisplayOFF()
{
    if (!energySaveMode)
        return;
    if (energySaveDisplayStatus == false && energySaveDisplayStatusLast == true)
    {
        energySaveDisplayStatusLast = false;
        dinamyDisplay->turnOFFDisplay();
    }
}

void Dynami_EnergySave::energySaveService()
{

    // loop to turn off display after 4sec (energySaveTimeON)
    if (energySaveMode)
    {
        if (energySaveDisplayStatus)
        {
            if (millis() > energySaveLastCheckTime + energySaveTimeON)
            {
                energySaveDisplayStatus = false;
            }
        }
    }
}

//
void Dynami_EnergySave::energySaveNewEvent()
{
    if (energySaveMode)
    {
        energySaveDisplayStatus = true;
        energySaveLastCheckTime = millis();
    }
}

// Turns on energy save mode
void Dynami_EnergySave::setEnergySaveMode(bool b)
{
    energySaveMode = b;
    dynamiMediator->energySaveModeChanged(); // needs refactor
    if (b)
        startEnergySaveModeService();
    if (!b)
        dinamyDisplay->turnONDisplay();
}



bool Dynami_EnergySave::getEnergySaveMode()
{
    return energySaveMode;
}
