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

#include "main.h"

const char *ssid = "xxxxx";
const char *password = "xxxx";

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

TaskHandle_t WebTasks;

char html_out_buffer[200];
String Name1, Name2, Name3, Name4;
uint8_t checkstate1, checkstate2, checkstate3, checkstate4;
uint8_t hume1, hume2, hume3, hume4;

// put function declarations here:
void ota_start();
void wifi_start();
void Web_Tasks(void *pvParameters);
void server_handles();

void notFound(AsyncWebServerRequest *request)
{
  request->send(404, "text/plain", "Not found");
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
}

//AsyncWebServer handles and functions
void server_handles()
{
  server.onNotFound(notFound);

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send_P(200, "text/html", MAIN_page); });

  server.on("/get", HTTP_GET, [](AsyncWebServerRequest *request)
            {
    Serial.println();
    if(request->hasParam("hume1"))
    {
      hume1 = request->getParam("hume1")->value().toInt();
    }
    if(request->hasParam("channel1"))
    {
      checkstate1 = request->getParam("channel1")->value().toInt();
    }
    if(request->hasParam("Name1"))
    {
      Name1 = request->getParam("Name1")->value();
      sprintf(html_out_buffer, "%s: Humidity: %d; State: %d", Name1, hume1, checkstate1);
    } 
    if(request->hasParam("hume2"))
    {
      hume2 = request->getParam("hume2")->value().toInt();
    }
    if(request->hasParam("channel2"))
    {
      checkstate2 = request->getParam("channel2")->value().toInt();
    }
    if(request->hasParam("Name2"))
    {
      Name2 = request->getParam("Name2")->value();
      sprintf(html_out_buffer, "%s: Humidity: %d; State: %d", Name2, hume2, checkstate2);
    } 
    if(request->hasParam("hume3"))
    {
      hume3 = request->getParam("hume3")->value().toInt();
    }
    if(request->hasParam("channel3"))
    {
      checkstate3 = request->getParam("channel3")->value().toInt();
    }
    if(request->hasParam("Name3"))
    {
      Name3 = request->getParam("Name3")->value();
      sprintf(html_out_buffer, "%s: Humidity: %d; State: %d", Name3, hume3, checkstate3);
    } 
    if(request->hasParam("hume4"))
    {
      hume4 = request->getParam("hume4")->value().toInt();
    }
    if(request->hasParam("channel4"))
    {
      checkstate4 = request->getParam("channel4")->value().toInt();
    }
    if(request->hasParam("Name4"))
    {
      Name4 = request->getParam("Name4")->value();
      sprintf(html_out_buffer, "%s: Humidity: %d; State: %d", Name4, hume4, checkstate4);
    } 
    Serial.println(html_out_buffer); 
    request->send(200, "text/html", "<!DOCTYPE html><html><head></head><body><script>close();</script></body></html>");
    });

  server.begin();
  Serial.println("Server Start");
  
}

//Run OTA and Web Service on different core than main loop
void Web_Tasks(void *pvParameters)
{
  server_handles();
  for (;;)
  {
    ArduinoOTA.handle();
    vTaskDelay(10);
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
  Serial.println("WiFi Start");
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


/* variable update for later
//cyclic getData()
sprintf(html_out_buffer, "{\"system\": %s, \"sytemcolor\": %s,
          \"ADCValue1\": %d, \"state1\": %d,
          \"ADCValue2\": %d, \"state2\": %d,
          \"ADCValue3\": %d, \"state3\": %d,
          \"ADCValue4\": %d, \"state4\": %d}",
          "Operational", "green",
          sensor1, state1,
          sensor2, state2,
          sensor3, state3,
          sensor4, state4);

//initial fillData()
sprintf(html_out_buffer, "{
          \"hume1\": %d, \"cb1\": %d, \"Name1\": %s,
          \"hume2\": %d, \"cb2\": %d, \"Name2\": %s,
          \"hume3\": %d, \"cb3\": %d, \"Name3\": %s,
          \"hume4\": %d, \"cb4\": %d, \"Name4\": %s}",
          hume1, checkstate1, Name1,
          hume2, checkstate2, Name2,
          hume3, checkstate3, Name3,
          hume4, checkstate4, Name4);


server.on("/", handleRoot);     //This is display page
server.on("/cyclic", getData);  //To get update of ADC Value only
server.on("/initial", fillData);//Names and set levels
*/
