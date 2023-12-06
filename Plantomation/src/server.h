#pragma once

#ifndef SERVER_H
#define SERVER_H

#include "main.h"

void ota_start();
void wifi_start();
void Web_Tasks(void *pvParameters);
bool fileExists(fs::FS &fs, const char *path);

#endif