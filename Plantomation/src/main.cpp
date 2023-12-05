#include "main.h"

uint8_t nowificonfig = 0;
Wifi wifi;

AsyncWebServer server(80); // Object of WebServer(HTTP port, 80 is defult)

TaskHandle_t WebTasks;

char html_out_buffer[512];

Plant plant1, plant2, plant3, plant4;
PlantConf pconf;

void notFound(AsyncWebServerRequest *request)
{
  request->send(418, "text/plain", "418: I am a teapot!");
}

void setup()
{
  delay(2000);
  Serial.begin(115200);
  Serial.println("Booting...");
  if (!SPIFFS.begin(FORMAT_SPIFFS_IF_FAILED))
  {
    Serial.println("SPIFFS Mount Failed");
    ESP.restart();
  }
  Serial.println("SPIFFS mounted");

  wifi_start();

  ota_start();
  Serial.println("OTA Start");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  delay(500);

  // create special task for OTA and Webserver on seperate core
  xTaskCreatePinnedToCore(
      Web_Tasks, /* Task function. */
      "Web_OTA", /* name of task. */
      10000,     /* Stack size of task */
      NULL,      /* parameter of the task */
      1,         /* priority of the task */
      &WebTasks, /* Task handle to keep track of created task */
      0);        /* pin task to core 0 */
  delay(500);

  // LED-pin on NodeMCU for testing purposes
  pinMode(2, OUTPUT);

  /* Pin Config for final board
    pinMode(pump, OUTPUT);
    pinMode(detect, INPUT);
    pinMode(protect, INPUT);
    pinMode(LED1, OUTPUT);
    pinMode(LED2, OUTPUT);
    pinMode(LED3, OUTPUT);
    pinMode(LED4, OUTPUT);
    pinMode(v1, OUTPUT);
    pinMode(v2, OUTPUT);
    pinMode(v3, OUTPUT);
    pinMode(v4, OUTPUT);
    pinMode(set1, INPUT);
    pinMode(set2, INPUT);*/

  Serial.println("Booting complete");
  // SD.begin();
}

void loop()
{
  // LED blinking with delay

  delay(1000);
  digitalWrite(2, LOW);
  delay(1000);
  digitalWrite(2, HIGH);

  if (plant1.sensor_display < 100)
    plant1.sensor_display++;
  else
    plant1.sensor_display = 0;
}

// AsyncWebServer handles and functions
void server_handles()
{
  page_handles();
  input_handles();
  output_handles();

  server.begin();
  Serial.println("Webserver Started");
}

void page_handles()
{
  server.onNotFound(notFound);

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
            {
              request->send_P(200, "text/html", MAIN_page);
#ifdef serial_debug
              Serial.println("Load Main Page");
#endif
            });

  server.on("/config", HTTP_GET, [](AsyncWebServerRequest *request)
            {
              request->send_P(200, "text/html", CONFIG_page);
#ifdef serial_debug
              Serial.println("Load Control Page");
#endif
            });

  server.on("/about", HTTP_GET, [](AsyncWebServerRequest *request)
            {
              request->send_P(200, "text/html", ABOUT_page);
#ifdef serial_debug
              Serial.println("Load About Page");
#endif
            });
}

void input_handles()
{
  server.on("/ch1", HTTP_GET, [](AsyncWebServerRequest *request)
            {
    if(request->hasParam("hume1"))
    {
      plant1.moisture = request->getParam("hume1")->value().toInt();
    }
    if(request->hasParam("Name1"))
    {
      strlcpy(plant1.name, request->getParam("Name1")->value().c_str(), sizeof(plant1.name));
    }
    if(request->hasParam("time1"))
    {
      plant1.interval_time = request->getParam("time1")->value().toInt();
    }
    if(request->hasParam("vol1"))
    {
      plant1.volume = request->getParam("vol1")->value().toInt();
    }
#ifdef serial_debug
      memset(html_out_buffer, 0, sizeof html_out_buffer);
      sprintf(html_out_buffer, "%s: Humidity: %d; State: %d; Interval: %d; Volume: %d", 
      plant1.name, plant1.moisture, plant1.op_mode, plant1.interval_time, plant1.volume);
      Serial.println(html_out_buffer);
#endif
    request->send(200, "text/html", "<!DOCTYPE html><html><head></head><body><script>close();</script></body></html>"); });

  server.on("/ch2", HTTP_GET, [](AsyncWebServerRequest *request)
            {
    if(request->hasParam("hume2"))
    {
      plant2.moisture = request->getParam("hume2")->value().toInt();
    }
    if(request->hasParam("Name2"))
    {
      strlcpy(plant2.name, request->getParam("Name2")->value().c_str(), sizeof(plant2.name));
    }
    if(request->hasParam("time2"))
    {
      plant2.interval_time = request->getParam("time2")->value().toInt();
    }
    if(request->hasParam("vol2"))
    {
      plant2.volume = request->getParam("vol2")->value().toInt();
    }
#ifdef serial_debug
      memset(html_out_buffer, 0, sizeof html_out_buffer);
      sprintf(html_out_buffer, "%s: Humidity: %d; State: %d; Interval: %d; Volume: %d", 
      plant2.name, plant2.moisture, plant2.op_mode, plant2.interval_time, plant2.volume);
      Serial.println(html_out_buffer);
#endif
    request->send(200, "text/html", "<!DOCTYPE html><html><head></head><body><script>close();</script></body></html>"); });

  server.on("/ch3", HTTP_GET, [](AsyncWebServerRequest *request)
            {
    if(request->hasParam("hume3"))
    {
      plant3.moisture = request->getParam("hume3")->value().toInt();
    }
    if(request->hasParam("Name3"))
    {
      strlcpy(plant3.name, request->getParam("Name3")->value().c_str(), sizeof(plant3.name));
    }
    if(request->hasParam("time3"))
    {
      plant3.interval_time = request->getParam("time3")->value().toInt();
    }
    if(request->hasParam("vol3"))
    {
      plant3.volume = request->getParam("vol3")->value().toInt();
    }
#ifdef serial_debug
      memset(html_out_buffer, 0, sizeof html_out_buffer);
      sprintf(html_out_buffer, "%s: Humidity: %d; State: %d; Interval: %d; Volume: %d", 
      plant3.name, plant3.moisture, plant3.op_mode, plant3.interval_time, plant3.volume);
      Serial.println(html_out_buffer);
#endif
    request->send(200, "text/html", "<!DOCTYPE html><html><head></head><body><script>close();</script></body></html>"); });

  server.on("/ch4", HTTP_GET, [](AsyncWebServerRequest *request)
            {
    if(request->hasParam("hume4"))
    {
      plant4.moisture = request->getParam("hume4")->value().toInt();
    }
    if(request->hasParam("Name4"))
    {
      strlcpy(plant4.name, request->getParam("Name4")->value().c_str(), sizeof(plant4.name));
    }
    if(request->hasParam("time4"))
    {
      plant4.interval_time = request->getParam("time4")->value().toInt();
    }
    if(request->hasParam("vol4"))
    {
      plant4.volume = request->getParam("vol4")->value().toInt();
    }
#ifdef serial_debug
      memset(html_out_buffer, 0, sizeof html_out_buffer);
      sprintf(html_out_buffer, "%s: Humidity: %d; State: %d; Interval: %d; Volume: %d", 
      plant4.name, plant4.moisture, plant4.op_mode, plant4.interval_time, plant4.volume);
      Serial.println(html_out_buffer);
#endif
    request->send(200, "text/html", "<!DOCTYPE html><html><head></head><body><script>close();</script></body></html>"); });

  server.on("/modes", HTTP_GET, [](AsyncWebServerRequest *request)
            {
    if(request->hasParam("ch1_mode"))
    {
      plant1.op_mode = request->getParam("ch1_mode")->value().toInt();
    }
    if(request->hasParam("ch2_mode"))
    {
      plant2.op_mode = request->getParam("ch2_mode")->value().toInt();
    }
    if(request->hasParam("ch3_mode"))
    {
      plant3.op_mode = request->getParam("ch3_mode")->value().toInt();
    }
    if(request->hasParam("ch4_mode"))
    {
      plant4.op_mode = request->getParam("ch4_mode")->value().toInt();
    }

#ifdef serial_debug
      memset(html_out_buffer, 0, sizeof html_out_buffer);
      sprintf(html_out_buffer, "mode1: %d, mode2: %d, mode3: %d, mode4: %d", 
      plant1.op_mode, plant2.op_mode, plant3.op_mode, plant4.op_mode);
      Serial.println(html_out_buffer);
#endif
    request->send(200, "text/html", "<!DOCTYPE html><html><head></head><body><script>close();</script></body></html>"); });

  server.on("/sysconf", HTTP_GET, [](AsyncWebServerRequest *request)
            {
    if(request->hasParam("pumprate"))
    {
      pconf.pumprate = request->getParam("pumprate")->value().toInt();
    }

#ifdef serial_debug
      memset(html_out_buffer, 0, sizeof html_out_buffer);
      sprintf(html_out_buffer, "Pumprate: %d", 
      pconf.pumprate);
      Serial.println(html_out_buffer);
#endif
    request->send(200, "text/html", "<!DOCTYPE html><html><head></head><body><script>close();</script></body></html>"); });

  server.on("/wifi_set", HTTP_POST, [](AsyncWebServerRequest *request)
            {
    if(request->hasParam("ssid"))
    {
      strlcpy(wifi.ssid, request->getParam("ssid")->value().c_str(), sizeof(wifi.ssid));
    }
    if(request->hasParam("passwd"))
    {
      strlcpy(wifi.passwd, request->getParam("passwd")->value().c_str(), sizeof(wifi.passwd));
    }
    if(request->hasParam("hostname"))
    {
      strlcpy(wifi.hostname, request->getParam("hostname")->value().c_str(), sizeof(wifi.hostname));
    } 
    if(request->hasParam("wifimode"))
    {
      wifi.mode = request->getParam("wifimode")->value().toInt();
    }
#ifdef serial_debug
      memset(html_out_buffer, 0, sizeof html_out_buffer);
      sprintf(html_out_buffer, "Hostname = %s; SSID = %s; Password= %s; Mode= %d", wifi.hostname, wifi.ssid, wifi.passwd, wifi.mode);
      Serial.println(html_out_buffer);
#endif
    request->send(200, "text/html", "<!DOCTYPE html><html><head></head><body><script>close();</script></body></html>");
    saveWifiConfig(SPIFFS, "/wifi.json");
    delay(100);
    ESP.restart(); });
}

void output_handles()
{
  server.on("/initial", HTTP_GET, [](AsyncWebServerRequest *request)
            {
              memset(html_out_buffer, 0, sizeof html_out_buffer);

              StaticJsonDocument<512> doc;
              // moisture values
              doc["hume1"] = plant1.moisture;
              doc["hume2"] = plant2.moisture;
              doc["hume3"] = plant3.moisture;
              doc["hume4"] = plant4.moisture;
              // Op-Mode Values
              doc["mode1"] = plant1.op_mode;
              doc["mode2"] = plant2.op_mode;
              doc["mode3"] = plant3.op_mode;
              doc["mode4"] = plant4.op_mode;
              // Name Values
              doc["Name1"] = plant1.name;
              doc["Name2"] = plant2.name;
              doc["Name3"] = plant3.name;
              doc["Name4"] = plant4.name;
              // Interval-Time Values
              doc["time1"] = plant1.interval_time;
              doc["time2"] = plant2.interval_time;
              doc["time3"] = plant3.interval_time;
              doc["time4"] = plant4.interval_time;
              // Volume Values
              doc["vol1"] = plant1.volume;
              doc["vol2"] = plant2.volume;
              doc["vol3"] = plant3.volume;
              doc["vol4"] = plant4.volume;

              serializeJson(doc, html_out_buffer);

              request->send_P(200, "application/json", html_out_buffer);
#ifdef serial_debug
              Serial.print("Initial Value Request: ");
              Serial.println(html_out_buffer);
#endif
            });

  server.on("/conf", HTTP_GET, [](AsyncWebServerRequest *request)
            {
              String statestring;
              String statecolor;
              switch (pconf.sysstate)
              {
              case SYS_OK:
                statestring = "Operational";
                statecolor = "green";
                break;
              case SYS_SPILL:
                statestring = "Spill Detected";
                statecolor = "crimson";
                break;
              case SYS_FAIL:
                statestring = "Setup Fail";
                statecolor = "orange";
                break;
              case SYS_SD:
                statestring = "SD Fail - Internal Fallback";
                statecolor = "orange";
                break;
              case SYS_EMPTY:
                statestring = "Reservoir Empty";
                statecolor = "lightblue";
                break;

              default:
                statestring = "System Error";
                statecolor = "crimson";
                break;
              }
              memset(html_out_buffer, 0, sizeof html_out_buffer);

              StaticJsonDocument<512> doc;
              // System values
              doc["system"] = statestring;
              doc["systemcolor"] = statecolor;
              doc["pumprate"] = pconf.pumprate;
              // Op-Mode Values
              doc["mode1"] = plant1.op_mode;
              doc["mode2"] = plant2.op_mode;
              doc["mode3"] = plant3.op_mode;
              doc["mode4"] = plant4.op_mode;

              serializeJson(doc, html_out_buffer);
              request->send_P(200, "application/json", html_out_buffer);
#ifdef serial_debug
              Serial.print("Config Values: ");
              Serial.println(html_out_buffer);
#endif
            });

  server.on("/cyclic", HTTP_GET, [](AsyncWebServerRequest *request)
            {
              String statestring;
              String statecolor;
              switch (pconf.sysstate)
              {
              case SYS_OK:
                statestring = "Operational";
                statecolor = "green";
                break;
              case SYS_SPILL:
                statestring = "Spill Detected";
                statecolor = "crimson";
                break;
              case SYS_FAIL:
                statestring = "Setup Fail";
                statecolor = "orange";
                break;
              case SYS_SD:
                statestring = "SD Fail - Internal Fallback";
                statecolor = "orange";
                break;
              case SYS_EMPTY:
                statestring = "Reservoir Empty";
                statecolor = "lightblue";
                break;

              default:
                statestring = "System Error";
                statecolor = "crimson";
                break;
              }

              memset(html_out_buffer, 0, sizeof html_out_buffer);

              StaticJsonDocument<512> doc;
              // System values
              doc["system"] = statestring;
              doc["systemcolor"] = statecolor;
              doc["pumprate"] = pconf.pumprate;
              // Moisture Values in %
              doc["ADCValue1"] = plant1.sensor_display;
              doc["ADCValue2"] = plant2.sensor_display;
              doc["ADCValue3"] = plant3.sensor_display;
              doc["ADCValue4"] = plant4.sensor_display;

              serializeJson(doc, html_out_buffer);

              request->send_P(200, "application/json", html_out_buffer);
#ifdef serial_debug
              Serial.print("Cyclic Value Update: ");
              Serial.println(html_out_buffer);
#endif
            });
}

// Run OTA and Web Service on different core than main loop
void Web_Tasks(void *pvParameters)
{
  server_handles();
  for (;;)
  {
    ArduinoOTA.handle();
    vTaskDelay(1);
  }
}

// start wifi
void wifi_start()
{
  if (fileExists(SPIFFS, "/wifi.json"))
  {
    loadWifiConfig(SPIFFS, "/wifi.json");
  }
  else
  {
    strlcpy(wifi.hostname, "Plantomation-Standalone", sizeof(wifi.hostname));
    strlcpy(wifi.ssid, "Plantomation", sizeof(wifi.ssid));
    strlcpy(wifi.passwd, "Planto1!", sizeof(wifi.passwd));
    wifi.mode = 0;
    saveWifiConfig(SPIFFS, "/wifi.json");
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
      nowificonfig = 1;
    }
  }

  if (wifi.mode == 0)
  {
    if (nowificonfig)
    {
      strlcpy(wifi.hostname, "Plantomation-Standalone", sizeof(wifi.hostname));
      strlcpy(wifi.ssid, "Plantomation", sizeof(wifi.ssid));
      strlcpy(wifi.passwd, "123456789", sizeof(wifi.passwd));
      wifi.mode = 0;
    }
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

void loadWifiConfig(fs::FS &fs, const char *path)
{
  File file = fs.open(path);
  StaticJsonDocument<256> doc;
  DeserializationError error = deserializeJson(doc, file);
  if (error)
    Serial.println(F("Failed to read file, using default configuration"));
  strlcpy(wifi.hostname, doc["hostname"], sizeof(wifi.hostname));
  strlcpy(wifi.ssid, doc["ssid"], sizeof(wifi.ssid));
  strlcpy(wifi.passwd, doc["password"], sizeof(wifi.passwd));
  wifi.mode = doc["mode"];
}

void saveWifiConfig(fs::FS &fs, const char *path)
{
  if (fs.exists(path))
    fs.remove(path);

  File file = fs.open(path, FILE_WRITE);
  StaticJsonDocument<256> doc;
  doc["hostname"] = wifi.hostname;
  doc["ssid"] = wifi.ssid;
  doc["password"] = wifi.passwd;
  doc["mode"] = wifi.mode;

  serializeJson(doc, file);
  file.close();
}