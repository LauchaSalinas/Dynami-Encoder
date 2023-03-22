#include "Dynami_Debug.h"

Dynami_Debug::Dynami_Debug() : encoder_timer_(200), velocity_timer_(200), battery_timer_(2000) {}

void Dynami_Debug::DebugStart()
{
    Serial.begin(115200);
}

void Dynami_Debug::DebugLoop()
{
    if (debug_service_status_)
    {
        SerialRead();
        if (debug_encoder_status_)
            if (encoder_timer_.TimeoutCheck())
                DebugEncoder();
        if (debug_velocity_status_)
            if (velocity_timer_.TimeoutCheck())
                DebugVelocity();
        if (debug_battery_status_)
            if (battery_timer_.TimeoutCheck())
                DebugBattery();
    }
}

void Dynami_Debug::SerialRead()
{
    String rxStr = Serial.readStringUntil('\n');
    char charArray[rxStr.length() + 1];
    rxStr.toCharArray(charArray, rxStr.length() + 1);
    // if (rxStr == "wifion")
    // {
    //     Serial.println("Starting WIFI");
    //     getWifiCredentials();
    //     dynamiUpdate->updateOTAWebServer();
    // }
    if (strcmp(charArray, "update") == 0)
    {
        Serial.println("Starting UpdateDynami()");
        dynamiMediator->UpdateDynami();
    }
}

String Dynami_Debug::AskNewString()
{
    char *newSSID;

    String inputString = "";         // a String to hold incoming data
    bool stringCompleteBool = false; // whether the string is complete

    while (!stringCompleteBool)
    {
        while (Serial.available())
        {
            // get the new byte:
            char inChar = (char)Serial.read();

            // if the incoming character is a newline, set a flag so the main loop can
            // do something about it:
            if (inChar == '#')
            {
                stringCompleteBool = true;
            }
            else
            {
                // add it to the inputString:
                inputString += inChar;
            }
        }
        delay(10);
    }
    newSSID = (char *)inputString.c_str();
    Serial.println("entered: ");
    Serial.println(inputString); // DELETE THIS
    return inputString;
}

bool Dynami_Debug::GetCharYN()
{
    Serial.flush();
    while (Serial.available() == 0){}
    char inChar = (char)Serial.read();
    if (inChar == 'Y') return true;
    return false;
}

// DEBUGS

// Velocity

void Dynami_Debug::DebugVelocity()
{
    Serial.print("MAX:");
    Serial.print(2);
    Serial.print(",");
    Serial.print("MIN:");
    Serial.print(0);
    Serial.print(",");
    Serial.print("Velocity:");
    Serial.println(dynamiMediator->dynamiProgram->getVelocity());
}

// void Dynami_NotifyCenter::SerialNotifyDistance(double distance) {
//   Serial.println(distance);
// }

void Dynami_Debug::DebugBattery()
{
    Serial.print("Analog = ");
    Serial.print(dynamiMediator->dynamiBattery->batteryValue);
    Serial.print("\t Voltage = ");
    Serial.print(dynamiMediator->dynamiBattery->batVoltage);
    Serial.print("\t Batt % = ");
    Serial.print(dynamiMediator->dynamiBattery->batPercentage);
    Serial.print("\t Cells = ");
    Serial.println(dynamiMediator->dynamiBattery->getCellsQty());
}

void Dynami_Debug::DebugEncoder() {}