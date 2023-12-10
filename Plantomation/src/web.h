/**
 * 
 * web.h and web.cpp are support files containing all handles 
 * for the webinterface. 
 * These are divided into 3 categories: 
 * -  page handles (load pages)
 * -  input handles (getting data from web to controller)
 * -  ouput handles (getting data from controller to web)
 * 
*/
#pragma once

#ifndef WEB_H
#define WEB_H

#include <Arduino.h>
#include <ArduinoJson.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

#include "classes.h"
#include "sites.h"
#include "config.h"
#include "html/pictures.h"

//Class Objects
extern Wifi wifi;
extern Plant plant1, plant2, plant3, plant4;
extern SysConf pconf;
extern AsyncWebServer server;

void page_handles();
void input_handles();
void output_handles();

//char string_buffer[512];

#endif