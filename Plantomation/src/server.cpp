#include "server.h"


// start wifi
void wifi_start(Wifi wifi, fs::FS &filesystem)
{
  

  if (fileExists(filesystem, s_wifi))
  {
    wifi.load_config(filesystem, s_wifi);
  }
  else
  {
    wifi.mode = 0;
  }

  if (wifi.mode == 1)
  {
    WiFi.mode(WIFI_STA);
    WiFi.config(INADDR_NONE, INADDR_NONE, INADDR_NONE, INADDR_NONE);
    WiFi.setHostname(wifi.hostname);
    WiFi.begin(wifi.ssid, wifi.passwd);
    delay(2000); // wait 2sec to connect to network
    // if no connection, make your own network
    if (!WiFi.isConnected())
    {
      wifi.mode = 0;
    }
  }

  if (wifi.mode == 0)
  {
    String mac = "";
    mac = WiFi.macAddress().c_str();
    mac.replace(":", "-");
    char buffer[64];
    sprintf(buffer, "Plantomation-%s", mac.substring(9, 17));
    strlcpy(wifi.hostname, buffer, sizeof(wifi.hostname));
    strlcpy(wifi.ssid, "Plantomation", sizeof(wifi.ssid));
    strlcpy(wifi.passwd, "Planto1!", sizeof(wifi.passwd));
    WiFi.mode(WIFI_AP);
    delay(250);
    IPAddress local_IP(4, 3, 2, 1);
    IPAddress subnet(255, 255, 255, 0);
    WiFi.softAPConfig(local_IP, INADDR_NONE, subnet);
    delay(250);
    WiFi.softAP(wifi.ssid, wifi.passwd);
    delay(250);
  }

  Serial.print("WiFi Started - ");
  if (wifi.mode)
    Serial.println("Station Mode");
  else
    Serial.println("Access Point Mode");
}

// configure OTA
void ota_start()
{
  ArduinoOTA
      .onStart([]()
               {
      String type;
      if (ArduinoOTA.getCommand() == U_FLASH)
        type = "sketch";
      else // U_SPIFFS
        type = "filesystem";

      // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
      Serial.println("Start updating " + type); })
      .onEnd([]()
             { Serial.println("\nEnd"); })
      .onProgress([](unsigned int progress, unsigned int total)
                  { Serial.printf("Progress: %u%%\r", (progress / (total / 100))); })
      .onError([](ota_error_t error)
               {
      Serial.printf("Error[%u]: ", error);
      if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
      else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
      else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
      else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
      else if (error == OTA_END_ERROR) Serial.println("End Failed"); });

  ArduinoOTA.begin();
}

bool fileExists(fs::FS &fs, const char *path)
{
  if (fs.exists(path))
    return true;
  else
    return false;
}