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
#define SD_CS 5
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
// Sensor Value between 1.5V (in water) and 2.8V (dry air);
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

//miscellaneous
#define pump_volume 0
#define pump_time 1
#define samplecount 10

//file paths
#define spiffs_wifi_conf "/wifi.json"
#define spiffs_system_conf "/control.json"
#define spiffs_plant1_conf "/plant1.json"
#define spiffs_plant2_conf "/plant2.json"
#define spiffs_plant3_conf "/plant3.json"
#define spiffs_plant4_conf "/plant4.json"

#define sd_wifi_conf "/config/wifi.json"
#define sd_system_conf "/config/control.json"
#define sd_plant1_conf "/config/plant1.json"
#define sd_plant2_conf "/config/plant2.json"
#define sd_plant3_conf "/config/plant3.json"
#define sd_plant4_conf "/config/plant4.json"
#define sd_plant1_logs "/log/plant1.log"
#define sd_plant2_logs "/log/plant2.log"
#define sd_plant3_logs "/log/plant3.log"
#define sd_plant4_logs "/log/plant4.log"
#define sd_events_logs "/log/events.log"

#define watering_time 5

#define moist_dry 3400
#define moist_wet 1600

#define FORMAT_SPIFFS_IF_FAILED false


#endif //  CONFIG_H