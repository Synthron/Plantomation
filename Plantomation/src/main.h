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
#include "sites.h"
#include "web.h"

// Pin Definitions
#define pump 4
#define detect 13
#define protect 14
#define LED1 21
#define LED2 17
#define LED3 16
#define LED4 15
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

// Defines for Webinterface
#define SYS_OK 0
#define SYS_SPILL 1
#define SYS_FAIL 2
#define SYS_SD 3
#define SYS_EMPTY 4
#define SYS_FATAL 255

// #define serial_debug

#define FORMAT_SPIFFS_IF_FAILED false

//function declarations
extern TaskHandle_t WebTasks;

AsyncWebServer server(80); // Object of WebServer(HTTP port, 80 is defult)

//Class Objects
extern Wifi wifi;
extern Plant plant1, plant2, plant3, plant4;
extern SysConf pconf;

//variables
char html_out_buffer[512];

#endif //MAIN_H 