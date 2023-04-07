#include "Dynami_Update.h"

Dynami_Update::Dynami_Update() : http() {}

void Dynami_Update::StartWifi()
{
    WiFi.mode(WIFI_STA);
    delay(1000);
}

bool Dynami_Update::ConnectWifi()
{
    StartWifi();
    Serial.begin(115200);
    // needs to check if no ssid was declared
    Serial.println();
    Serial.print("[WiFi] Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid.c_str(), password.c_str());
    // Auto reconnect is set true as default
    // To set auto connect off, use the following function
    //    WiFi.setAutoReconnect(false);

    // Will try for about 10 seconds (20x 500ms)
    int tryDelay = 1000;
    int numberOfTries = 20;

    // Wait for the WiFi event
    while (true)
    {

        switch (WiFi.status())
        {
        case WL_NO_SSID_AVAIL:
            Serial.println("[WiFi] SSID not found");
            break;
        case WL_CONNECT_FAILED:
            Serial.print("[WiFi] Failed - WiFi not connected! Reason: ");
            return false;
            break;
        case WL_CONNECTION_LOST:
            Serial.println("[WiFi] Connection was lost");
            break;
        case WL_SCAN_COMPLETED:
            Serial.println("[WiFi] Scan is completed");
            break;
        case WL_DISCONNECTED:
            Serial.println("[WiFi] WiFi is disconnected");
            break;
        case WL_CONNECTED:
            Serial.println("[WiFi] WiFi is connected!");
            Serial.print("[WiFi] IP address: ");
            Serial.println(WiFi.localIP());
            return true;
            break;
        default:
            Serial.print("[WiFi] WiFi Status: ");
            Serial.println(WiFi.status());
            break;
        }
        delay(tryDelay);

        if (numberOfTries <= 0)
        {
            Serial.print("[WiFi] Failed to connect to WiFi!");
            // Use disconnect function to force stop trying to connect
            WiFi.disconnect();
            return false;
        }
        else
        {
            numberOfTries--;
        }
    }
}

void Dynami_Update::updateOTAWebServer()
{
    server = new AsyncWebServer(80);
    ElegantOTA = new AsyncElegantOtaClass();

    Serial.println("Connected to ");
    Serial.println(ssid);
    Serial.println("IP address: ");
    String str = WiFi.localIP().toString().c_str();
    Serial.println(str + "/update");

    // server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
    //           { request->send(200, "text/plain", "Hi! I am ESP32."); });

    ElegantOTA->begin(server); // Start ElegantOTA
    server->begin();
    Serial.println("HTTP server started");
}

void Dynami_Update::updateOTAWebServerClose()
{
    delete server;
    server = NULL;
    delete ElegantOTA;
    ElegantOTA = NULL;
}

void Dynami_Update::TurnOffWifi()
{
    WiFi.disconnect();
    WiFi.enableSTA(false);
}

bool Dynami_Update::CheckSSIDinAvailableSSIDs(const char *storedSSID)
{
    // WiFi.scanNetworks will return the number of networks found.
    int n = WiFi.scanNetworks();
    Serial.println("n networks: " + n);
    if (n == 0)
    {
        // no networks found
        return false;
    }
    else
    {
        for (int i = 0; i < n; ++i)
        {
            Serial.println(WiFi.SSID(i));
            if (strcmp(WiFi.SSID(i).c_str(), storedSSID) == 0)
            {
                Serial.println("Found SSID");
                // Delete the scan result to free memory.
                WiFi.scanDelete();
                return true;
            }
        }
        return false;
    }
}

void Dynami_Update::ScanSSID()
{
    // WiFi.scanNetworks will return the number of networks found.
    int n = WiFi.scanNetworks();
    if (n == 0)
    {
        // no networks found
        nNetworks = 0;
        return;
    }
    else
    {
        nNetworks = 4;
        delay(50);
        for (int i = 0; i < n; i++)
        {
            //Serial.println(WiFi.SSID(i));
            if (i < 4)
            {
                Serial.println(WiFi.SSID(i).c_str());
                AvailableSSIDs.push_back(WiFi.SSID(i)) ;
            }
        }
        //WiFi.scanDelete();
    }
}

bool Dynami_Update::IsWifiConnected()
{
    wl_status_t status = WiFi.status();
    if (status == 3)
        return true;
    return false;
}

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

char *Dynami_Update::get_wifi_status()
{
    wl_status_t status = WiFi.status();
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

int Dynami_Update::CheckWebVersion()
{
    int version = 0;

    Serial.print("[HTTP] begin...\n");
    Serial.println(update_server_ + last_version_path_);
    http.begin(update_server_ + last_version_path_); // HTTP
    http.setReuse(true);
    Serial.print("[HTTP] GET...\n");
    // start connection and send HTTP header
    int httpCode = http.GET();

    // httpCode will be negative on error
    if (httpCode > 0)
    {
        // HTTP header has been send and Server response header has been handled
        Serial.printf("[HTTP] GET... code: %d\n", httpCode);

        // file found at server
        if (httpCode == HTTP_CODE_OK)
        {
            String payload = http.getString();
            last_version_path_ = payload + ".bin";
            Serial.println(payload);
            version = atoi(payload.c_str());
        }
    }
    else
    {
        Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }
    http.end();
    return version;
}

// HTTP callbacks

void update_started()
{
    Serial.println("CALLBACK:  HTTP update process started");
}

void update_finished()
{
    Serial.println("CALLBACK:  HTTP update process finished");
}

void update_progress(int cur, int total)
{
    Serial.printf("CALLBACK:  HTTP update process at %d of %d bytes...\n", cur, total);
}

void update_error(int err)
{
    Serial.printf("CALLBACK:  HTTP update fatal error code %d\n", err);
}

void Dynami_Update::StartHTTPUpdate()
{
    WiFiClient client;

    httpUpdate.onStart(update_started);
    httpUpdate.onEnd(update_finished);
    httpUpdate.onProgress(update_progress);
    httpUpdate.onError(update_error);
    http.begin(update_server_ + last_version_path_);
    Serial.println("Path to last version: " + update_server_ + last_version_path_);
    t_httpUpdate_return ret = httpUpdate.update(http);

    switch (ret)
    {
    case HTTP_UPDATE_FAILED:
        Serial.printf("HTTP_UPDATE_FAILED Error (%d): %s\n", httpUpdate.getLastError(), httpUpdate.getLastErrorString().c_str());
        break;

    case HTTP_UPDATE_NO_UPDATES:
        Serial.println("HTTP_UPDATE_NO_UPDATES");
        break;

    case HTTP_UPDATE_OK:
        Serial.println("HTTP_UPDATE_OK");
        break;
    }
}
