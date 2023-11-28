#include <Arduino.h>
#include "tinyxml2.h"
#include "FS.h"
#include "SD.h"
#include "SD_MMC.h"

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
//Sensor Value between 1.5V (in water) and 2.8V (dry air)
#define s1 34
#define s2 35
#define s3 32
#define s4 33
#define spill 36
#define set1 14
#define set2 13

// put function declarations here:
int myFunction(int, int);

void setup() {
  pinMode(pump, OUTPUT);
  pinMode(detect, INPUT);
  pinMode(protect, INPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(v1, OUTPUT);
  pinMode(v2, OUTPUT);
  pinMode(v3, OUTPUT);
  pinMode(v4, OUTPUT);
  pinMode(set1, INPUT);
  pinMode(set2, INPUT);


  SD_MMC.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
}

