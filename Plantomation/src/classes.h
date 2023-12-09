#pragma once

#ifndef CLASSES_H
#define CLASSES_H

#include <Arduino.h>
#include "FS.h"
#include "SPIFFS.h"
#include <ArduinoJson.h>
#include "SD.h"
#include "SPI.h"

class Wifi
{
  public:
    char hostname[64];
    char ssid[64];
    char passwd[64];
    uint8_t mode;
    void load_config(fs::FS &fs, const char *path);
    void save_config(fs::FS &fs, const char *path);

};

class Plant
{
  public:
    char name[64];
    uint8_t op_mode;
    uint8_t moisture;
    uint32_t interval_time;
    uint16_t volume;
    uint8_t log_enable;
    uint16_t sensor_raw;
    uint8_t sensor_display;

    void load_config(fs::FS &fs, const char *path);
    void save_config(fs::FS &fs, const char *path);
};

class SysConf
{
  public:
    uint16_t pumprate;
    uint8_t debug_level;
    uint8_t log_level;
    uint8_t sysstate;
    void load_config(fs::FS &fs, const char *path);
    void save_config(fs::FS &fs, const char *path);
};



#endif //CLASSES_H