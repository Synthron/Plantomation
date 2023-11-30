#include <Arduino.h>
#include "tinyxml2.h"
#include "FS.h"
#include "SD.h"
#include "SPI.h"
#include <WiFi.h>
#include "time.h"
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

// OTA
#include <ESPmDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

#include "sites.h"

const char *ssid = "HollaDieWaldfee";
const char *password = "LuisenStr11";

String hostname = "ESP32-Test";

// HTML & CSS contents which display on web server
String HTML = "<!DOCTYPE html>\
<html>\
<body>\
<h1>My First Web Server with ESP32 - Station Mode &#128522;</h1>\
<p> Erster Test ESP32 und OTA mit Webserver</p>\
</body>\
</html>";

AsyncWebServer server(80); // Object of WebServer(HTTP port, 80 is defult)

#define pump 4
#define detect 16
#define protect 17
#define LED1 22
#define LED2 21
#define LED3 19
#define LED4 18
#define v1 23
#define v2 25
#define v3 26
#define v4 27
// Sensor Value between 1.5V (in water) and 2.8V (dry air)
#define s1 34
#define s2 35
#define s3 32
#define s4 33
#define spill 36
#define set1 14
#define set2 13
//Defines for Webinterface
#define SYS_OK 0
#define SYS_SPILL 1
#define SYS_FAIL 2
#define SYS_SD 3
#define SYS_EMPTY 4
#define SYS_FATAL 255

//#define serial_debug

TaskHandle_t WebTasks;

char html_out_buffer[200];
String Name1="", Name2="", Name3="", Name4="";
uint8_t checkstate1=0, checkstate2=0, checkstate3=0, checkstate4=0;
uint8_t hume1=0, hume2=0, hume3=0, hume4=0;
uint8_t sysstate = 0;
uint8_t sensor1=0, sensor2=0, sensor3=0, sensor4=0;
uint8_t state1=0, state2=0, state3=0, state4=0;

// put function declarations here:
void ota_start();
void wifi_start();
void Web_Tasks(void *pvParameters);
void server_handles();

void notFound(AsyncWebServerRequest *request)
{
  request->send(418, "text/plain", "418: I am a teapot!");
}

void setup()
{
  Serial.begin(115200);
  Serial.println("Booting...");

  wifi_start();

  ota_start();
  Serial.println("OTA Start");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  delay(500);


  //create special task for OTA and Webserver on seperate core
  xTaskCreatePinnedToCore(
      Web_Tasks, /* Task function. */
      "Web_OTA", /* name of task. */
      10000,     /* Stack size of task */
      NULL,      /* parameter of the task */
      1,         /* priority of the task */
      &WebTasks, /* Task handle to keep track of created task */
      0);        /* pin task to core 0 */
  delay(500);

//LED-pin on NodeMCU for testing purposes
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
  //LED blinking with delay

  delay(1000);
  digitalWrite(2, LOW);
  delay(1000);
  digitalWrite(2, HIGH);

  if(sensor1 < 100)
    sensor1++;
  else 
    sensor1=0;
}

//AsyncWebServer handles and functions
void server_handles()
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

  server.on("/ch1", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    if(request->hasParam("hume1"))
    {
      hume1 = request->getParam("hume1")->value().toInt();
    }
    if(request->hasParam("channel1"))
    {
      state1 = request->getParam("channel1")->value().toInt();
    }else state1 = 0;
    if(request->hasParam("Name1"))
    {
      Name1 = request->getParam("Name1")->value();
    } 
    #ifdef serial_debug
      memset(html_out_buffer, 0, sizeof html_out_buffer);
      sprintf(html_out_buffer, "%s: Humidity: %d; State: %d", Name1, hume1, state1);
      Serial.println(html_out_buffer); 
    #endif
    request->send(200, "text/html", "<!DOCTYPE html><html><head></head><body><script>close();</script></body></html>");
  });

  server.on("/ch2", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    if(request->hasParam("hume2"))
    {
      hume2 = request->getParam("hume2")->value().toInt();
    }
    if(request->hasParam("channel2"))
    {
      state2 = request->getParam("channel2")->value().toInt();
    }else state2 = 0;
    if(request->hasParam("Name2"))
    {
      Name2 = request->getParam("Name2")->value();
    } 
    #ifdef serial_debug
      memset(html_out_buffer, 0, sizeof html_out_buffer);
      sprintf(html_out_buffer, "%s: Humidity: %d; State: %d", Name2, hume2, checkstate2);
      Serial.println(html_out_buffer); 
    #endif
    request->send(200, "text/html", "<!DOCTYPE html><html><head></head><body><script>close();</script></body></html>");
  });

  server.on("/ch3", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    if(request->hasParam("hume3"))
    {
      hume3 = request->getParam("hume3")->value().toInt();
    }
    if(request->hasParam("channel3"))
    {
      state3 = request->getParam("channel3")->value().toInt();
    }else state3 = 0;
    if(request->hasParam("Name3"))
    {
      Name3 = request->getParam("Name3")->value();
    } 
    #ifdef serial_debug
      memset(html_out_buffer, 0, sizeof html_out_buffer);
      sprintf(html_out_buffer, "%s: Humidity: %d; State: %d", Name3, hume3, checkstate3);
      Serial.println(html_out_buffer); 
    #endif
    request->send(200, "text/html", "<!DOCTYPE html><html><head></head><body><script>close();</script></body></html>");
  });

  server.on("/ch4", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    if(request->hasParam("hume4"))
    {
      hume4 = request->getParam("hume4")->value().toInt();
    }
    if(request->hasParam("channel4"))
    {
      state4 = request->getParam("channel4")->value().toInt();
    }else state4 = 0;
    if(request->hasParam("Name4"))
    {
      Name4 = request->getParam("Name4")->value();
    } 
    #ifdef serial_debug
      memset(html_out_buffer, 0, sizeof html_out_buffer);
      sprintf(html_out_buffer, "%s: Humidity: %d; State: %d", Name4, hume4, checkstate4);
      Serial.println(html_out_buffer); 
    #endif
    request->send(200, "text/html", "<!DOCTYPE html><html><head></head><body><script>close();</script></body></html>");
  });

  server.on("/initial", HTTP_GET, [](AsyncWebServerRequest *request)
  { 
    memset(html_out_buffer, 0, sizeof html_out_buffer);
    sprintf(html_out_buffer, "{\"hume1\": %d, \"cb1\": %d, \"Name1\": \"%s\", \"hume2\": %d, \"cb2\": %d, \"Name2\": \"%s\", \"hume3\": %d, \"cb3\": %d, \"Name3\": \"%s\", \"hume4\": %d, \"cb4\": %d, \"Name4\": \"%s\"}",
      hume1, state1, Name1,
      hume2, state2, Name2,
      hume3, state3, Name3,
      hume4, state4, Name4);
    request->send_P(200, "application/json", html_out_buffer); 
    #ifdef serial_debug
      Serial.print("Initial Value Request: ");
      Serial.println(html_out_buffer);
    #endif
  });

    server.on("/cyclic", HTTP_GET, [](AsyncWebServerRequest *request)
  { 
    String statestring;
    String statecolor;
    switch (sysstate)
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
    String _state1, _state2, _state3, _state4;
    if(state1)
      _state1 = "Active";
    else
      _state1 = "Inactive";
    if(state2)
      _state2 = "Active";
    else
      _state2 = "Inactive";
    if(state3)
      _state3 = "Active";
    else
      _state3 = "Inactive";
    if(state4)
      _state4 = "Active";
    else
      _state4 = "Inactive";
    memset(html_out_buffer, 0, sizeof html_out_buffer);
    sprintf(html_out_buffer, "{\"system\": \"%s\", \"sytemcolor\": \"%s\", \"ADCValue1\": %d, \"state1\": \"%s\", \"ADCValue2\": %d, \"state2\": \"%s\", \"ADCValue3\": %d, \"state3\": \"%s\", \"ADCValue4\": %d, \"state4\": \"%s\"}",
      statestring, statecolor,
      sensor1, _state1,
      sensor2, _state2,
      sensor3, _state3,
      sensor4, _state4);
    request->send_P(200, "application/json", html_out_buffer); 
    #ifdef serial_debug
      Serial.print("Cyclic Value Update: ");
      Serial.println(html_out_buffer);
    #endif
  });


  server.begin();
  Serial.println("Webserver Started");
  
}

//Run OTA and Web Service on different core than main loop
void Web_Tasks(void *pvParameters)
{
  server_handles();
  for (;;)
  {
    ArduinoOTA.handle();
    vTaskDelay(1);
  }
}

//start wifi
void wifi_start()
{
  WiFi.mode(WIFI_STA);
  WiFi.config(INADDR_NONE, INADDR_NONE, INADDR_NONE, INADDR_NONE);
  WiFi.setHostname(hostname.c_str());
  WiFi.begin(ssid, password);
  while (WiFi.waitForConnectResult() != WL_CONNECTED)
  {
    delay(5000);
    ESP.restart();
  }
  Serial.println("WiFi Started");
}

//configure OTA
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
