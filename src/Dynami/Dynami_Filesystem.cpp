#include "Dynami_Filesystem.h"

Dynami_Filesystem::Dynami_Filesystem()
{
    if (!SPIFFS.begin(FORMAT_SPIFFS_IF_FAILED))
    {
        dynamiMediator->dynamiNotifyCenter->debugPrint("SPIFFS Mount Failed");
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
    char * buf ;
    newSSID.toCharArray(buf,33);
    writeFile(SPIFFS,ssidPath,buf);
}
void Dynami_Filesystem::writePS(String newPS)
{
    char * buf ;
    newPS.toCharArray(buf,33);
    deleteFile(SPIFFS,psPath);
    writeFile(SPIFFS,psPath,buf);
}

// PRIVATE

void Dynami_Filesystem::listDir(fs::FS &fs, const char *dirname, uint8_t levels)
{
    dynamiMediator->dynamiNotifyCenter->debugPrint("Listing directory: ");
    dynamiMediator->dynamiNotifyCenter->debugPrint(dirname);

    File root = fs.open(dirname);
    if (!root)
    {
        dynamiMediator->dynamiNotifyCenter->debugPrint("- failed to open directory");
        return;
    }
    if (!root.isDirectory())
    {
        dynamiMediator->dynamiNotifyCenter->debugPrint(" - not a directory");
        return;
    }

    File file = root.openNextFile();
    while (file)
    {
        if (file.isDirectory())
        {
            dynamiMediator->dynamiNotifyCenter->debugPrint("  DIR : ");
            dynamiMediator->dynamiNotifyCenter->debugPrint(file.name());
            if (levels)
            {
                listDir(fs, file.path(), levels - 1);
            }
        }
        else
        {
            dynamiMediator->dynamiNotifyCenter->debugPrint("  FILE: ");
            dynamiMediator->dynamiNotifyCenter->debugPrint(file.name());
            dynamiMediator->dynamiNotifyCenter->debugPrint("\tSIZE: ");
            dynamiMediator->dynamiNotifyCenter->debugPrint((int)file.size());
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
        dynamiMediator->dynamiNotifyCenter->debugPrint("- failed to open file for reading");
        return;
    }

    dynamiMediator->dynamiNotifyCenter->debugPrint("- read from file:");
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
        dynamiMediator->dynamiNotifyCenter->debugPrint("- failed to open file for reading");
        return str;
    }

    dynamiMediator->dynamiNotifyCenter->debugPrint("- read from file:");
    while (file.available())
    {
        str = file.readString();
    }
    file.close();
    return str;
}


void Dynami_Filesystem::writeFile(fs::FS &fs, const char *path, const char *message)
{
    dynamiMediator->dynamiNotifyCenter->debugPrint("Writing file: ");
    dynamiMediator->dynamiNotifyCenter->debugPrint(path);

    File file = fs.open(path, FILE_WRITE);
    if (!file)
    {
        dynamiMediator->dynamiNotifyCenter->debugPrint("- failed to open file for writing");
        return;
    }
    if (file.print(message))
    {
        dynamiMediator->dynamiNotifyCenter->debugPrint("- file written");
    }
    else
    {
        dynamiMediator->dynamiNotifyCenter->debugPrint("- write failed");
    }
    file.close();
}

void Dynami_Filesystem::appendFile(fs::FS &fs, const char *path, const char *message)
{
    dynamiMediator->dynamiNotifyCenter->debugPrint("Appending to file: ");
    dynamiMediator->dynamiNotifyCenter->debugPrint(path);

    File file = fs.open(path, FILE_APPEND);
    if (!file)
    {
        dynamiMediator->dynamiNotifyCenter->debugPrint("- failed to open file for appending");
        return;
    }
    if (file.print(message))
    {
        dynamiMediator->dynamiNotifyCenter->debugPrint("- message appended");
    }
    else
    {
        dynamiMediator->dynamiNotifyCenter->debugPrint("- append failed");
    }
    file.close();
}

void Dynami_Filesystem::renameFile(fs::FS &fs, const char *path1, const char *path2)
{
    dynamiMediator->dynamiNotifyCenter->debugPrint("Renaming file ");
    dynamiMediator->dynamiNotifyCenter->debugPrint(path1);
    dynamiMediator->dynamiNotifyCenter->debugPrint(" to ");
    dynamiMediator->dynamiNotifyCenter->debugPrint(path2);
    if (fs.rename(path1, path2))
    {
        dynamiMediator->dynamiNotifyCenter->debugPrint("- file renamed");
    }
    else
    {
        dynamiMediator->dynamiNotifyCenter->debugPrint("- rename failed");
    }
}

void Dynami_Filesystem::deleteFile(fs::FS &fs, const char *path)
{
    dynamiMediator->dynamiNotifyCenter->debugPrint("Deleting file:");
    dynamiMediator->dynamiNotifyCenter->debugPrint(path);
    if (fs.remove(path))
    {
        dynamiMediator->dynamiNotifyCenter->debugPrint("- file deleted");
    }
    else
    {
        dynamiMediator->dynamiNotifyCenter->debugPrint("- delete failed");
    }
}

void Dynami_Filesystem::testFileIO(fs::FS &fs, const char *path)
{
    dynamiMediator->dynamiNotifyCenter->debugPrint("Testing file I/O with ");
    dynamiMediator->dynamiNotifyCenter->debugPrint(path);

    static uint8_t buf[512];
    size_t len = 0;
    File file = fs.open(path, FILE_WRITE);
    if (!file)
    {
        dynamiMediator->dynamiNotifyCenter->debugPrint("- failed to open file for writing");
        return;
    }

    size_t i;
    dynamiMediator->dynamiNotifyCenter->debugPrint("- writing");
    uint32_t start = millis();
    for (i = 0; i < 2048; i++)
    {
        if ((i & 0x001F) == 0x001F)
        {
            dynamiMediator->dynamiNotifyCenter->debugPrint(".");
        }
        file.write(buf, 512);
    }
    dynamiMediator->dynamiNotifyCenter->debugPrint("");
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
        dynamiMediator->dynamiNotifyCenter->debugPrint("- reading");
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
                dynamiMediator->dynamiNotifyCenter->debugPrint(".");
            }
            len -= toRead;
        }
        dynamiMediator->dynamiNotifyCenter->debugPrint("");
        end = millis() - start;
        //dynamiMediator->dynamiNotifyCenter->debugPrint("- %u bytes read in %u ms\r\n", flen, end);
        file.close();
    }
    else
    {
        dynamiMediator->dynamiNotifyCenter->debugPrint("- failed to open file for reading");
    }
}
