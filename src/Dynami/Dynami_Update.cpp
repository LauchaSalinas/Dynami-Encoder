#include "Dynami_Update.h"

Dynami_Update::Dynami_Update() {}

char *Dynami_Update::get_wifi_status(wl_status_t status)
{
    switch (status)
    {
    case WL_IDLE_STATUS:
        return "WL_IDLE_STATUS";
    case WL_SCAN_COMPLETED:
        return "WL_SCAN_COMPLETED";
    case WL_NO_SSID_AVAIL:
        return "WL_NO_SSID_AVAIL";
    case WL_CONNECT_FAILED:
        return "WL_CONNECT_FAILED";
    case WL_CONNECTION_LOST:
        return "WL_CONNECTION_LOST";
    case WL_CONNECTED:
        return "WL_CONNECTED";
    case WL_DISCONNECTED:
        return "WL_DISCONNECTED";
    }
}

void Dynami_Update::updateOTAWebServer()
{
    server = new AsyncWebServer(80);
    ElegantOTA = new AsyncElegantOtaClass();
    WiFi.mode(WIFI_STA);
    delay(2000);
    wl_status_t status = WiFi.begin(ssid, password);
    delay(2000);

    // Wait for connection
    while (WiFi.status() != WL_CONNECTED && numberOfTries >= 0)
    {
        delay(1000);
        if (WiFi.status() != WL_CONNECTED)
            status = WiFi.begin(ssid, password);
        dynamiMediator->dynamiNotifyCenter->debugPrint(get_wifi_status(WiFi.status()));
        numberOfTries--;
    }
    dynamiMediator->dynamiNotifyCenter->debugPrint("Connected to ");
    dynamiMediator->dynamiNotifyCenter->debugPrint(ssid);
    dynamiMediator->dynamiNotifyCenter->debugPrint("IP address: ");
    dynamiMediator->dynamiNotifyCenter->debugPrint(WiFi.localIP().toString().c_str());

    // server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
    //           { request->send(200, "text/plain", "Hi! I am ESP32."); });

    ElegantOTA->begin(server); // Start ElegantOTA
    server->begin();
    dynamiMediator->dynamiNotifyCenter->debugPrint("HTTP server started");
}

void Dynami_Update::updateStopWifi()
{
    delete server;
    server = NULL;
    delete ElegantOTA;
    ElegantOTA = NULL;
    WiFi.disconnect();
}