#ifndef Dynami_Filesystem_h
#define Dynami_Filesystem_h

#include <FS.h>
#include <SPIFFS.h>

/* You only need to format SPIFFS the first time you run a
   test or else use the SPIFFS plugin to create a partition
   https://github.com/me-no-dev/arduino-esp32fs-plugin */
#define FORMAT_SPIFFS_IF_FAILED false

#include "Dynami_Mediator.h"

class Dynami_Mediator;

class Dynami_Filesystem
{
public:
    Dynami_Filesystem();
    Dynami_Mediator *dynamiMediator = NULL;
    void set_mediator(Dynami_Mediator *mediator) { this->dynamiMediator = mediator; }
    String getSSID();
    String getPS();
    void writeSSID(String newSSID);
    void writePS(String newPS);
    const char ssidPath[10] = "/ssid.txt";
    const char psPath[10] = "/ps.txt";

private:
    void listDir(fs::FS &fs, const char *dirname, uint8_t levels);
    void readFile(fs::FS &fs, const char *path);
    String readSingleString(fs::FS &fs, const char *path);
    void writeFile(fs::FS &fs, const char *path, String message);
    void appendFile(fs::FS &fs, const char *path, const char *message);
    void renameFile(fs::FS &fs, const char *path1, const char *path2);
    void deleteFile(fs::FS &fs, const char *path);
    void testFileIO(fs::FS &fs, const char *path);
};

#endif