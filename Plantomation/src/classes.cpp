#include "classes.h"


/*
*
*   Wifi-Class Function Definitions
*
*/

void Wifi::load_config(fs::FS &fs, const char *path)
{
  if (fs.exists(path))
  {
    File file = fs.open(path);
    StaticJsonDocument<256> doc;
    DeserializationError error = deserializeJson(doc, file);
    if (error)
      Serial.println(F("Failed to read file"));
    else{
      strlcpy(hostname, doc["hostname"], sizeof(hostname));
      strlcpy(ssid, doc["ssid"], sizeof(ssid));
      strlcpy(passwd, doc["password"], sizeof(passwd));
      mode = doc["mode"];
    }
  }
}

void Wifi::save_config(fs::FS &fs, const char *path)
{
  if (fs.exists(path))
    fs.remove(path);

  File file = fs.open(path, FILE_WRITE);
  StaticJsonDocument<256> doc;
  doc["hostname"] = hostname;
  doc["ssid"] = ssid;
  doc["password"] = passwd;
  doc["mode"] = mode;

  serializeJson(doc, file);
  file.close();
}

/*
*
*   Plant-Class Function Definitions
*
*/

void Plant::load_config(fs::FS &fs, const char *path)
{
  if (fs.exists(path))
  {
    File file = fs.open(path);
    StaticJsonDocument<256> doc;
    DeserializationError error = deserializeJson(doc, file);
    if (error)
      Serial.println(F("Failed to read file"));
    else{
      strlcpy(name, doc["name"], sizeof(name));
      op_mode = doc["op_mode"];
      moisture = doc["moisture"];
      interval_time = doc["interval_time"];
      volume = doc["volume"];
      log_enable = doc["log_enagle"];
    } 
  }  
}

void Plant::save_config(fs::FS &fs, const char *path)
{
  if (fs.exists(path))
    fs.remove(path);
  File file = fs.open(path, FILE_WRITE);
  StaticJsonDocument<256> doc;
  doc["name"] = name;
  doc["op_mode"] = op_mode;
  doc["moisture"] = moisture;
  doc["interval_time"] = interval_time;
  doc["volume"] = volume;
  doc["log_enagle"] = log_enable;
}

/*
*
*   SysConf-Class Function Definitions
*
*/

void SysConf::load_config(fs::FS &fs, const char *path)
{
  if (fs.exists(path))  
  {
    File file = fs.open(path);
    StaticJsonDocument<256> doc;
    DeserializationError error = deserializeJson(doc, file);
    if (error)
      Serial.println(F("Failed to read file"));
    else{
      pumprate = doc["pumprate"];
      debug_level = doc["debug_level"];
      log_level = doc["log_level"];
      sysstate = doc["sysstate"];
    } 
  } 
}

void SysConf::save_config(fs::FS &fs, const char *path)
{
  if (fs.exists(path))
    fs.remove(path);
  File file = fs.open(path, FILE_WRITE);
  StaticJsonDocument<256> doc;
  doc["pumprate"] = pumprate;
  doc["debug_level"] = debug_level;
  doc["log_level"] = log_level;
  doc["sysstate"] = sysstate;
  
  serializeJson(doc, file);
  file.close();
}