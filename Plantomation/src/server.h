/**
 * 
 * server.h and server.cpp are the support files for handling 
 * OTA and the webserver. Both processes are running on Core0
 * of the ESP32, thus leaving Core1 for the application of 
 * Plantonmation. This helps spreading out the load and
 * will make the website response as soon as possible.
 * 
*/

#pragma once

#ifndef SERVER_H
#define SERVER_H

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

#include "classes.h"

void ota_start();
void wifi_start(Wifi wifi);
bool fileExists(fs::FS &fs, const char *path);

#endif