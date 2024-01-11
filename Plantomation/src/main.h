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
void handle_channel(Plant p_obj, uint8_t valve, char *logpath);
void sensor_update();
uint16_t read_sensor(uint8_t sensor);
void pump_channel(uint8_t channel, uint16_t amount, bool ml_secs);
void IRAM_ATTR timer1();
void IRAM_ATTR timer2();
void IRAM_ATTR timer3();
void IRAM_ATTR timer4();
void log_moisture_info(Plant p_obj, char *path);

AsyncWebServer server(80); // Object of WebServer(HTTP port, 80 is defult)

//Class Objects
Wifi wifi;
Plant plant1, plant2, plant3, plant4;
SysConf pconf;

//variables

const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 3600;
const int   daylightOffset_sec = 0;
struct tm timeinfo;

bool sd_en;
char s_wifi[20];
char s_system[22];
char s_plant1[20];
char s_plant2[20];
char s_plant3[20];
char s_plant4[20];

hw_timer_t *Timer_Channel1 = NULL;
hw_timer_t *Timer_Channel2 = NULL;
hw_timer_t *Timer_Channel3 = NULL;
hw_timer_t *Timer_Channel4 = NULL;


#endif //MAIN_H 