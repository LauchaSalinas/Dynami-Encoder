#ifndef Dynami_Update_h
#define Dynami_Update_h

#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <AsyncElegantOTA.h>
#include <HTTPClient.h>
#include <HTTPUpdate.h>

#include <vector>
#include <string>

#include "Dynami_Mediator.h"

#define dynami_firmware_version_ 1

class Dynami_Update
{
public:
    Dynami_Update();
    Dynami_Mediator *dynamiMediator = NULL;
    void set_mediator(Dynami_Mediator *mediator) { this->dynamiMediator = mediator; }
    String ssid; // needs refactor
    String password;
    AsyncWebServer *server = NULL;
    AsyncElegantOtaClass *ElegantOTA = NULL;
    char *get_wifi_status(wl_status_t status);
    char *get_wifi_status();
    HTTPClient http;
    void StartWifi();
    bool ConnectWifi();
    bool IsWifiConnected();
    void updateOTAWebServerClose();
    void updateOTAWebServer();
    void TurnOffWifi();
    bool CheckSSIDinAvailableSSIDs(const char *storedSSID);
    void ScanSSID();
    std::vector<String> AvailableSSIDs;
    int nNetworks = 0;
    int CheckWebVersion();
    void StartHTTPUpdate();

private:
    String update_server_ = "https://lauchasalinas.com.ar/DynamiFirmware/";
    String last_version_path_ = "lastversion.txt";
    String new_version_path_ = ""; // NEEDS development should be in SPIFFS to store txt if we dont want to update but want to avoid another check 
};

#endif