#include "main.h"


void setup()
{
  delay(2000);
  Serial.begin(115200);
  Serial.println("Booting...");
  if (!SPIFFS.begin(FORMAT_SPIFFS_IF_FAILED))
  {
    Serial.println("SPIFFS Mount Failed");
    ESP.restart();
  }
  Serial.println("SPIFFS mounted");

  wifi_start();

  ota_start();
  Serial.println("OTA Start");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  delay(500);

  // create special task for OTA and Webserver on seperate core
  xTaskCreatePinnedToCore(
      Web_Tasks, /* Task function. */
      "Web_OTA", /* name of task. */
      10000,     /* Stack size of task */
      NULL,      /* parameter of the task */
      1,         /* priority of the task */
      &WebTasks, /* Task handle to keep track of created task */
      0);        /* pin task to core 0 */
  delay(500);

  // LED-pin on NodeMCU for testing purposes
  pinMode(2, OUTPUT);

  /* Pin Config for final board
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
    pinMode(set2, INPUT);*/

  Serial.println("Booting complete");
  // SD.begin();
}

void loop()
{
  // LED blinking with delay

  delay(1000);
  digitalWrite(2, LOW);
  delay(1000);
  digitalWrite(2, HIGH);

  if (plant1.sensor_display < 100)
    plant1.sensor_display++;
  else
    plant1.sensor_display = 0;
}
