#include "Dynami_Debug.h"

Dynami_Debug::Dynami_Debug() : encoder_timer_(10), velocity_timer_(0), battery_timer_(10000), distance_timer_(30), acceleration_timer_(10) {}

void Dynami_Debug::DebugStart()
{
    Serial.begin(115200);
#if DEBUG == true
    SerialBT.begin("ESP32test"); // Bluetooth device name
    Serial.println("The device started, now you can pair it with bluetooth!");
#endif
}

void Dynami_Debug::DebugLoop()
{

    if (debug_service_status_)
    {
        SerialRead2();
        if (debug_encoder_status_)
            if (encoder_timer_.TimeoutCheck())
                DebugEncoder();
        if (debug_distance_status_)
            if (distance_timer_.TimeoutCheck())
                // DebugDistance();
                DebugPlotter();
        if (debug_velocity_status_)
            if (velocity_timer_.TimeoutCheck())
                // DebugVelocity();
                DebugPlotter();
        if (debug_acceleration_status_)
            if (acceleration_timer_.TimeoutCheck())
                DebugAcceleration();
        if (debug_battery_status_)
            if (battery_timer_.TimeoutCheck())
                DebugBattery();
    }
}

void Dynami_Debug::SerialRead()
{
    String rxStr = SERIAL.readStringUntil('\n');
    char charArray[rxStr.length() + 1];
    rxStr.toCharArray(charArray, rxStr.length() + 1);
    // if (rxStr == "wifion")
    // {
    //     SERIAL.println("Starting WIFI");
    //     getWifiCredentials();
    //     dynamiUpdate->updateOTAWebServer();
    // }
    if (strcmp(charArray, "update") == 0)
    {
        SERIAL.println("Starting UpdateDynami()");
        dynamiMediator->UpdateDynami();
    }
    if (strcmp(charArray, "encoder") == 0)
    {
        SERIAL.println("Starting encoder debug");
        debug_encoder_status_ = true;
    }
    if (strcmp(charArray, "velocity") == 0)
    {
        SERIAL.println("Starting velocity debug");
        debug_velocity_status_ = true;
    }

    if (strcmp(charArray, "distance") == 0)
    {
        SERIAL.println("Starting distance debug");
        debug_distance_status_ = true;
    }

    if (strcmp(charArray, "off") == 0)
    {
        SERIAL.println("debugs off");
        debug_distance_status_ = false;
        debug_velocity_status_ = false;
        debug_encoder_status_ = false;
    }

    if (strcmp(charArray, "bt") == 0)
    {
        SERIAL.println("bt on");
        dynamiMediator->dynamiDisplay->displayBT();
    }
    if (strcmp(charArray, "c+") == 0)
    {
        double val = dynamiMediator->dynamiProgram->calibration = dynamiMediator->dynamiProgram->calibration + 1;
        SERIAL.printf("calibration : %f", val);
    }
    if (strcmp(charArray, "c-") == 0)
    {
        double val = dynamiMediator->dynamiProgram->calibration = dynamiMediator->dynamiProgram->calibration - 1;
        SERIAL.printf("calibration : %f", val);
    }
}

void Dynami_Debug::SerialRead2()
{
    char rxStr = SERIAL.read();
    // if (rxStr == "wifion")
    // {
    //     SERIAL.println("Starting WIFI");
    //     getWifiCredentials();
    //     dynamiUpdate->updateOTAWebServer();
    // }
    if (rxStr == 'u')
    {
        SERIAL.println("Starting UpdateDynami()");
        dynamiMediator->UpdateDynami();
    }
    if (rxStr == 'e')
    {
        SERIAL.println("Starting encoder debug");
        debug_encoder_status_ = true;
    }
    if (rxStr == 'v')
    {
        SERIAL.println("Starting velocity debug");
        debug_velocity_status_ = true;
    }
    if (rxStr == 'a')
    {
        SERIAL.println("Starting acceleration debug");
        debug_acceleration_status_ = true;
    }
    if (rxStr == 'd')
    {
        SERIAL.println("Starting distance debug");
        debug_distance_status_ = true;
    }

    if (rxStr == 'o')
    {
        SERIAL.println("debugs off");
        debug_distance_status_ = false;
        debug_velocity_status_ = false;
        debug_encoder_status_ = false;
        debug_acceleration_status_ = false;
    }

    if (rxStr == 'b')
    {
        SERIAL.println("bt on");
        dynamiMediator->dynamiDisplay->displayBT();
    }
    if (rxStr == '+')
    {
        double val = dynamiMediator->dynamiProgram->calibration = dynamiMediator->dynamiProgram->calibration + 1;
        SERIAL.printf("calibration : %f", val);
    }
    if (rxStr == '-')
    {
        double val = dynamiMediator->dynamiProgram->calibration = dynamiMediator->dynamiProgram->calibration - 1;
        SERIAL.printf("calibration : %f", val);
    }
}

String Dynami_Debug::AskNewString()
{
    char *newSSID;

    String inputString = "";         // a String to hold incoming data
    bool stringCompleteBool = false; // whether the string is complete

    while (!stringCompleteBool)
    {
        while (SERIAL.available())
        {
            // get the new byte:
            char inChar = (char)SERIAL.read();

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
    SERIAL.println("entered: ");
    SERIAL.println(inputString); // DELETE THIS
    return inputString;
}

bool Dynami_Debug::GetCharYN()
{
    SERIAL.flush();
    while (SERIAL.available() == 0)
    {
    }
    char inChar = (char)SERIAL.read();
    if (inChar == 'Y')
        return true;
    return false;
}

// DEBUGS

void Dynami_Debug::DebugDistance()
{
    SERIAL.print("Distance: ");
    SERIAL.print(dynamiMediator->dynamiProgram->getDistance() / (double)100);
}

void Dynami_Debug::DebugVelocity()
{
    SERIAL.print("Velocity: ");
    SERIAL.print(dynamiMediator->dynamiProgram->getVelocitydbFiltered());
}

void Dynami_Debug::DebugAcceleration()
{
    SERIAL.print("Acceleration: ");
    SERIAL.println(dynamiMediator->dynamiProgram->getAcceleration());
}

void Dynami_Debug::DebugBattery()
{
    SERIAL.print("Analog = ");
    SERIAL.print(dynamiMediator->dynamiBattery->getBatteryValue());
    SERIAL.print("\t Voltage = ");
    SERIAL.print(dynamiMediator->dynamiBattery->getBatVoltageValue());
    SERIAL.print("\t Batt % = ");
    SERIAL.print(dynamiMediator->dynamiBattery->getBatPercentage());
    SERIAL.print("\t Cells = ");
    SERIAL.println(dynamiMediator->dynamiBattery->getCellsQty());
}

void Dynami_Debug::DebugEncoder()
{
    SERIAL.println(dynamiMediator->dynamiEncoder->getEncoderValue());
}

void Dynami_Debug::DebugPlotter()
{
    double distance = dynamiMediator->dynamiProgram->getDistance();
    if (true) //(abs(distance) > 1)
    {
        // 1 distancia
        SERIAL.print("!");
        SERIAL.print(distance);
        // 2 velocidad no filtrada
        SERIAL.print("|");
        SERIAL.print(dynamiMediator->dynamiProgram->getVelocitydb(), 6);
        // 3 velocidad filtrada rapida
        SERIAL.print("|");
        SERIAL.print(dynamiMediator->dynamiProgram->getVelocitydbFiltered(), 6);
        // 4 aceleracion
        SERIAL.print("|");
        SERIAL.print(dynamiMediator->dynamiProgram->accelerationdb, 6);
        // 5 aceleracion filtrada rapida
        SERIAL.print("|");
        SERIAL.print(dynamiMediator->dynamiProgram->getAccelerationFiltered(), 6);

        // 6 min distance
        SERIAL.print("|");
        SERIAL.print(dynamiMediator->dynamiProgram->minDistance / (double)100);

        // 7 stages
        SERIAL.print("|");
        SERIAL.print(dynamiMediator->dynamiProgram->stages);

        // 8 Rep Time printing
        SERIAL.print("|");
        double repTime;
        unsigned long t0 = dynamiMediator->dynamiProgram->initRepTime;
        unsigned long tf = dynamiMediator->dynamiProgram->finalRepTime;
        if (tf>0) repTime = (tf - t0) / (double)1000;
        else repTime = (millis() - t0) / (double)1000;
        if (repTime > 0 && repTime < 3)
            SERIAL.print(repTime);
        else
            SERIAL.print(0.00F);

        // 9 velocidad media
        SERIAL.print("|");
        double VM = dynamiMediator->dynamiProgram->velocidadMV;
        if (VM > 0 && VM < 50)
            SERIAL.print(VM);
        else
            SERIAL.print(0.00F);

        // 10 velocidad mvp
        SERIAL.print("|");
        double velocityMVP = dynamiMediator->dynamiProgram->velocidadMVP;
        if (velocityMVP > 0)
            SERIAL.print(velocityMVP);
        else
            SERIAL.print(0.00F);

        // 11 velocidad filtrada lenta
        SERIAL.print("|");
        SERIAL.print(dynamiMediator->dynamiProgram->velocitydbFiltered2, 6);

        // 12 aceleracion filtrada lenta
        SERIAL.print("|");
        SERIAL.print(dynamiMediator->dynamiProgram->accelerationdbFiltered2, 6);

        // 13 peak velocity
        SERIAL.print("|");
        double velocityPeak = dynamiMediator->dynamiProgram->velocitydbFilteredMax;
        if (velocityPeak > 0)
            SERIAL.print(velocityPeak);
        else
            SERIAL.print(0.00F);

        // Final \n printing
        SERIAL.println();
    }
}