#include "Dynami_Filesystem.h"

Dynami_Filesystem::Dynami_Filesystem()
{
    if (!SPIFFS.begin(FORMAT_SPIFFS_IF_FAILED))
    {
        Serial.println("SPIFFS Mount Failed");
        return;
    }
}

// PUBLIC

String Dynami_Filesystem::getSSID()
{   
    return readSingleString(SPIFFS,ssidPath);
}
String Dynami_Filesystem::getPS()
{
    return readSingleString(SPIFFS,psPath);
}
void Dynami_Filesystem::writeSSID(String newSSID)
{
    deleteFile(SPIFFS,ssidPath);
    writeFile(SPIFFS,ssidPath,newSSID);
}
void Dynami_Filesystem::writePS(String newPS)
{
    deleteFile(SPIFFS,psPath);
    writeFile(SPIFFS,psPath,newPS);
}

// PRIVATE

void Dynami_Filesystem::listDir(fs::FS &fs, const char *dirname, uint8_t levels)
{
    Serial.println("Listing directory: ");
    Serial.println(dirname);

    File root = fs.open(dirname);
    if (!root)
    {
        Serial.println("- failed to open directory");
        return;
    }
    if (!root.isDirectory())
    {
        Serial.println(" - not a directory");
        return;
    }

    File file = root.openNextFile();
    while (file)
    {
        if (file.isDirectory())
        {
            Serial.println("  DIR : ");
            Serial.println(file.name());
            if (levels)
            {
                listDir(fs, file.path(), levels - 1);
            }
        }
        else
        {
            Serial.println("  FILE: ");
            Serial.println(file.name());
            Serial.println("\tSIZE: ");
            Serial.println((int)file.size());
        }
        file = root.openNextFile();
    }
}

void Dynami_Filesystem::readFile(fs::FS &fs, const char *path)
{
    //Serial.printf("Reading file: %s\r\n", path);

    File file = fs.open(path);
    if (!file || file.isDirectory())
    {
        Serial.println("- failed to open file for reading");
        return;
    }

    Serial.println("- read from file:");
    while (file.available())
    {
        Serial.write(file.read());
    }
    file.close();
}

String Dynami_Filesystem::readSingleString(fs::FS &fs, const char *path){
    String str = "noString";
    File file = fs.open(path);
    if (!file || file.isDirectory())
    {
        Serial.println("- failed to open file for reading");
        return str;
    }

    Serial.println("- read from file:");
    while (file.available())
    {
        str = file.readString();
    }
    file.close();
    return str;
}


void Dynami_Filesystem::writeFile(fs::FS &fs, const char *path, String message)
{
    Serial.println("Writing file: ");
    Serial.println(path);

    File file = fs.open(path, FILE_WRITE);
    if (!file)
    {
        Serial.println("- failed to open file for writing");
        return;
    }
    if (file.print(message))
    {
        Serial.println("- file written");
    }
    else
    {
        Serial.println("- write failed");
    }
    file.close();
}

void Dynami_Filesystem::appendFile(fs::FS &fs, const char *path, const char *message)
{
    Serial.println("Appending to file: ");
    Serial.println(path);

    File file = fs.open(path, FILE_APPEND);
    if (!file)
    {
        Serial.println("- failed to open file for appending");
        return;
    }
    if (file.print(message))
    {
        Serial.println("- message appended");
    }
    else
    {
        Serial.println("- append failed");
    }
    file.close();
}

void Dynami_Filesystem::renameFile(fs::FS &fs, const char *path1, const char *path2)
{
    Serial.println("Renaming file ");
    Serial.println(path1);
    Serial.println(" to ");
    Serial.println(path2);
    if (fs.rename(path1, path2))
    {
        Serial.println("- file renamed");
    }
    else
    {
        Serial.println("- rename failed");
    }
}

void Dynami_Filesystem::deleteFile(fs::FS &fs, const char *path)
{
    Serial.println("Deleting file:");
    Serial.println(path);
    if (fs.remove(path))
    {
        Serial.println("- file deleted");
    }
    else
    {
        Serial.println("- delete failed");
    }
}

void Dynami_Filesystem::testFileIO(fs::FS &fs, const char *path)
{
    Serial.println("Testing file I/O with ");
    Serial.println(path);

    static uint8_t buf[512];
    size_t len = 0;
    File file = fs.open(path, FILE_WRITE);
    if (!file)
    {
        Serial.println("- failed to open file for writing");
        return;
    }

    size_t i;
    Serial.println("- writing");
    uint32_t start = millis();
    for (i = 0; i < 2048; i++)
    {
        if ((i & 0x001F) == 0x001F)
        {
            Serial.println(".");
        }
        file.write(buf, 512);
    }
    Serial.println("");
    uint32_t end = millis() - start;
    //Serial.printf(" - %u bytes written in %u ms\r\n", 2048 * 512, end);
    file.close();

    file = fs.open(path);
    start = millis();
    end = start;
    i = 0;
    if (file && !file.isDirectory())
    {
        len = file.size();
        size_t flen = len;
        start = millis();
        Serial.println("- reading");
        while (len)
        {
            size_t toRead = len;
            if (toRead > 512)
            {
                toRead = 512;
            }
            file.read(buf, toRead);
            if ((i++ & 0x001F) == 0x001F)
            {
                Serial.println(".");
            }
            len -= toRead;
        }
        Serial.println("");
        end = millis() - start;
        //Serial.println("- %u bytes read in %u ms\r\n", flen, end);
        file.close();
    }
    else
    {
        Serial.println("- failed to open file for reading");
    }
}
