#ifndef Dynami_Update_h
#define Dynami_Update_h

#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <AsyncElegantOTA.h>

#include "Dynami_Mediator.h"

class Dynami_Update
{
public:
    Dynami_Update();
    Dynami_Mediator *dynamiMediator = NULL;
    void set_mediator(Dynami_Mediator *mediator) { this->dynamiMediator = mediator; }
    const char *ssid = "upside";
    const char *password = "fuckpass";
    AsyncWebServer *server = NULL;
    AsyncElegantOtaClass *ElegantOTA= NULL;
    char *get_wifi_status(wl_status_t status); // its not int
    int numberOfTries = 20;
    void updateOTAWebServer();
    void updateStopWifi();
};

#endif