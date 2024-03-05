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


void Web_Tasks(void *pvParameters);
void handle_channel(Plant p_obj, uint8_t valve, const char *logpath);
void log_moisture_info(Plant p_obj, const char *path);
void sensor_update();
uint16_t read_sensor(uint8_t sensor);
void pump_channel(uint8_t channel, uint16_t amount, bool ml_secs);
void IRAM_ATTR timer1();
void IRAM_ATTR timer2();
void IRAM_ATTR timer3();
void IRAM_ATTR timer4();
void copy_configs();
void log_event(uint8_t event);

extern AsyncWebServer server; // Object of WebServer(HTTP port, 80 is defult)

//Class Objects
extern Wifi wifi;
extern Plant plant1, plant2, plant3, plant4;
extern SysConf pconf;

extern TaskHandle_t WebTasks;
extern struct tm timeinfo;

//variables

extern const char* ntpServer;
extern const long  gmtOffset_sec;
extern const int   daylightOffset_sec;

extern bool sd_en;
extern char s_wifi[20];
extern char s_system[22];
extern char s_plant1[20];
extern char s_plant2[20];
extern char s_plant3[20];
extern char s_plant4[20];

extern hw_timer_t *Timer_Channel1;
extern hw_timer_t *Timer_Channel2;
extern hw_timer_t *Timer_Channel3;
extern hw_timer_t *Timer_Channel4;


#endif //MAIN_H 