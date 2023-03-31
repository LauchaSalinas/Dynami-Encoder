#include "Dynami.h"

Dynami::Dynami() : dynamiProgram(), dynamiBattery(), dynamiBluetooth(), dynamiDisplay(), dynamiEnergySave(),
                   dynamiEncoder(), dynamiButtons(), dynamiNotifyCenter(), dynamiMediator(), dynamiUpdate(),
                   dynamiFilesystem(), dynamiDebug(), dynamiReps()
{
  dynamiMediator.setRefs(&dynamiBattery, &dynamiBluetooth, &dynamiButtons, &dynamiDisplay, &dynamiEncoder, &dynamiEnergySave, &dynamiNotifyCenter, &dynamiProgram, &dynamiUpdate, &dynamiFilesystem, &dynamiDebug, &dynamiReps);
  dynamiEnergySave.setDisplayRef(&dynamiDisplay);
  dynamiDisplay.setEnergySaveRef(&dynamiEnergySave);
  dynamiProgram.setPointers(&dynamiEncoder);
}

void Dynami::dynamiSetup()
{
  dynamiNotifyCenter.notifyCenterSetup();
  dynamiEncoder.encoderSetup();
  dynamiProgram.dynamiProgramSetup();
  dynamiBattery.batterySetup();
  dynamiButtons.buttonsSetup();
  dynamiBluetooth.BTSetup();
  dynamiEnergySave.startEnergySaveModeService();
  dynamiDisplay.displaySetup();
  dynamiDebug.DebugStart();
}

void Dynami::dynamiLoop()
{
  dynamiProgram.distanceMeasurement();
  dynamiProgram.velocityMeasurament();
  dynamiProgram.accelerationMeasurament();
  dynamiProgram.resetDetector();
  dynamiProgram.repControl3();
  dynamiEncoder.encoderLoop();
  dynamiBattery.batteryLoop();
  dynamiBluetooth.BTLoop();
  dynamiButtons.buttonsLoop();
  dynamiDisplay.displayLoop();
  dynamiEnergySave.energySaveLoop();
  dynamiDebug.DebugLoop();
}