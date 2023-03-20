#include "Dynami.h"

Dynami::Dynami() : 
dynamiProgram(),dynamiBattery(), dynamiBluetooth(), dynamiDisplay(), dynamiEnergySave(),
dynamiEncoder(),dynamiButtons(),dynamiNotifyCenter(), dynamiMediator(), dynamiUpdate()
{
  dynamiMediator.setRefs(&dynamiBattery,&dynamiBluetooth, &dynamiButtons, &dynamiDisplay, &dynamiEncoder, &dynamiEnergySave, &dynamiNotifyCenter, &dynamiProgram, &dynamiUpdate);
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
}

void Dynami::dynamiLoop()
{
  dynamiProgram.repControl(); 
  dynamiProgram.repMeasurement();
  dynamiProgram.velocityMeasurament();
  dynamiProgram.distanceMeasurement();
  dynamiEncoder.encoderLoop();
  dynamiBattery.batteryLoop();
  dynamiBluetooth.BTLoop();
  dynamiButtons.buttonsLoop();
  dynamiDisplay.displayLoop();
  dynamiEnergySave.energySaveLoop();
}