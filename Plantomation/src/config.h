/**
 * 
 * Global config file for Plantomation
 * 
 * Pin Definitions, Label definitions and 
 * Compile-Options like debug and resetting the SPIFFS
 * 
*/

#pragma once

#ifndef CONFIG_H
#define CONFIG_H

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

#endif //  CONFIG_H