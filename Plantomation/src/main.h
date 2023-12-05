#ifndef MAIN_H
#define MAIN_H

#include <Arduino.h>
#include "tinyxml2.h"
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

// websites
#include "sites.h"

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
// Defines for Webinterface
#define SYS_OK 0
#define SYS_SPILL 1
#define SYS_FAIL 2
#define SYS_SD 3
#define SYS_EMPTY 4
#define SYS_FATAL 255

// #define serial_debug

#define FORMAT_SPIFFS_IF_FAILED false

struct Wifi
{
  char hostname[64];
  char ssid[64];
  char passwd[64];
  uint8_t mode;
};

struct Plant
{
  char name[64];
  uint8_t op_mode;
  uint8_t moisture;
  uint32_t interval_time;
  uint16_t volume;
  uint8_t log_enable;
  uint16_t sensor_raw;
  uint8_t sensor_display;
};

struct PlantConf
{
  uint16_t pumprate;
  uint8_t debug_level;
  uint8_t log_level;
  uint8_t sysstate;
};

// put function declarations here:
void ota_start();
void wifi_start();
void Web_Tasks(void *pvParameters);
void server_handles();
void page_handles();
void input_handles();
void output_handles();
bool fileExists(fs::FS &fs, const char *path);
void loadWifiConfig(fs::FS &fs, const char *path);
void saveWifiConfig(fs::FS &fs, const char *path);

#endif //MAIN_H