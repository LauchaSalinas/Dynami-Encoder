#ifndef Dynami_BluetoothSerial_h
#define Dynami_BluetoothSerial_h

#include "BluetoothSerial.h"

class Dynami_BluetoothSerial{
  public:
  BluetoothSerial SerialBT;
  void BTSerialSetup();
  void BTSerialLoop();
};

#endif