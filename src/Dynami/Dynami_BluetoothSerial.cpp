#include "Dynami_BluetoothSerial.h"

void Dynami_BluetoothSerial::BTSerialSetup()
{
    Serial.begin(115200);
    SerialBT.begin("ESP32test"); // Bluetooth device name
    Serial.println("The device started, now you can pair it with bluetooth!");
}

void Dynami_BluetoothSerial::BTSerialLoop()
{
    if (Serial.available())
    {
        SerialBT.write(Serial.read());
    }
    if (SerialBT.available())
    {
        Serial.write(SerialBT.read());
    }
}
