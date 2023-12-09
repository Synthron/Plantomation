#pragma once

#ifndef MAIN_H
#define MAIN_H

#include <Arduino.h>
#include "FS.h"
#include "SPIFFS.h"
#include <ArduinoJson.h>
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

// project specific
#include "classes.h"
#include "server.h"
#include "web.h"
#include "config.h"

//function declarations
TaskHandle_t WebTasks;

void Web_Tasks(void *pvParameters);

AsyncWebServer server(80); // Object of WebServer(HTTP port, 80 is defult)

//Class Objects
Wifi wifi;
Plant plant1, plant2, plant3, plant4;
SysConf pconf;

//variables

#endif //MAIN_H 