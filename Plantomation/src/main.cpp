#include "main.h"


void setup()
{

  // Pin Config for final board
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

  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, HIGH);
  digitalWrite(LED3, HIGH);
  digitalWrite(LED4, HIGH);

  plant1.interval_ready = false;
  plant2.interval_ready = false;
  plant3.interval_ready = false;
  plant4.interval_ready = false;

  delay(2000);
  Serial.begin(115200);
  Serial.println("Booting...");

  Serial.print("Setup Timers");
  Timer_Channel1 = timerBegin(0, 240, true);
  Timer_Channel2 = timerBegin(1, 240, true);
  Timer_Channel3 = timerBegin(2, 240, true);
  Timer_Channel4 = timerBegin(3, 240, true);
  timerAlarmWrite(Timer_Channel1, 4000000000000, true);
  timerAlarmWrite(Timer_Channel2, 4000000000000, true);
  timerAlarmWrite(Timer_Channel3, 4000000000000, true);
  timerAlarmWrite(Timer_Channel4, 4000000000000, true);
  timerAttachInterrupt(Timer_Channel1, &timer1, true);
  timerAttachInterrupt(Timer_Channel2, &timer2, true);
  timerAttachInterrupt(Timer_Channel3, &timer3, true);
  timerAttachInterrupt(Timer_Channel4, &timer4, true);
  Serial.println("... done");

  Serial.println("Setup File Systems");
  if(!digitalRead(detect))
    sd_en = true;
  
  if (!SPIFFS.begin(FORMAT_SPIFFS_IF_FAILED))
  {
    Serial.println("SPIFFS Mount Failed");
    ESP.restart();
  }
  Serial.println("SPIFFS mounted");

  if(sd_en)
  {
    SPI.begin(18, 19, 22, SD_CS);
    if(!SD.begin(SD_CS))
    {
      Serial.println("SD Mount Failed");
      ESP.restart();
    }
    Serial.println("SD Mounted");
  }

  Serial.println("Setup WiFi");
  if(sd_en)
  {
    strlcpy(s_wifi, sd_wifi_conf, sizeof(s_wifi));
    strlcpy(s_system, sd_system_conf, sizeof(s_system));
    strlcpy(s_plant1, sd_plant1_conf, sizeof(s_plant1));
    strlcpy(s_plant2, sd_plant2_conf, sizeof(s_plant2));
    strlcpy(s_plant3, sd_plant3_conf, sizeof(s_plant3));
    strlcpy(s_plant4, sd_plant4_conf, sizeof(s_plant4));
    pconf.load_config(SD, sd_system_conf);
    plant1.load_config(SD, sd_plant1_conf);
    plant2.load_config(SD, sd_plant2_conf);
    plant3.load_config(SD, sd_plant3_conf);
    plant4.load_config(SD, sd_plant4_conf);
    wifi_start(wifi, SD);
  }
  else
  {
    strlcpy(s_wifi, spiffs_wifi_conf, sizeof(s_wifi));
    strlcpy(s_system, spiffs_system_conf, sizeof(s_system));
    strlcpy(s_plant1, spiffs_plant1_conf, sizeof(s_plant1));
    strlcpy(s_plant2, spiffs_plant2_conf, sizeof(s_plant2));
    strlcpy(s_plant3, spiffs_plant3_conf, sizeof(s_plant3));
    strlcpy(s_plant4, spiffs_plant4_conf, sizeof(s_plant4));
    pconf.load_config(SPIFFS, sd_system_conf);
    plant1.load_config(SPIFFS, sd_plant1_conf);
    plant2.load_config(SPIFFS, sd_plant2_conf);
    plant3.load_config(SPIFFS, sd_plant3_conf);
    plant4.load_config(SPIFFS, sd_plant4_conf);
    wifi_start(wifi, SPIFFS);
  }

  if(WiFi.getMode() == WIFI_STA)
  {
    Serial.println("Update Time Data");
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
    if(!getLocalTime(&timeinfo))
    {
      Serial.println("Failed to obtain time, setting 01-01-2000 00:00:00");
      timeinfo.tm_hour = 0;
      timeinfo.tm_min = 0;
      timeinfo.tm_sec = 0;
      timeinfo.tm_mday = 1;
      timeinfo.tm_mon = 1;
      timeinfo.tm_year = 2000;
    }
    Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
    timeinfo.tm_year += 1900;
  }

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

  Serial.println("Booting complete");
  // SD.begin();
}

void loop()
{
  sensor_update();

  handle_channel(plant1, v1, sd_plant1_logs);
  handle_channel(plant2, v2, sd_plant2_logs);
  handle_channel(plant3, v3, sd_plant3_logs);
  handle_channel(plant4, v4, sd_plant4_logs);

  delay(1000);
}

void log_moisture_info(Plant p_obj, char *path, uint8_t log_sort)
{
  if(pconf.log_level == 2 && sd_en)
  {
    getLocalTime(&timeinfo);
    char buf[200];
    if(log_sort == 0)
    {
      sprintf(buf, "%d-%d-%d;%d:%d:%d;Moisture Sensor Value; %d\%", 
      timeinfo.tm_year, timeinfo.tm_mon, timeinfo.tm_mday, 
      timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec, 
      p_obj.sensor_display);
    }
    else if(log_sort == 1)
    {
      sprintf(buf, "%d-%d-%d;%d:%d:%d;watered for seconds; %d", 
      timeinfo.tm_year, timeinfo.tm_mon, timeinfo.tm_mday, 
      timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec, 
      watering_time);
    }
    else if(log_sort == 2)
    {
      sprintf(buf, "%d-%d-%d;%d:%d:%d;watered with volume; %d;ml", 
      timeinfo.tm_year, timeinfo.tm_mon, timeinfo.tm_mday, 
      timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec, 
      p_obj.volume);
    }
    
    File file = SD.open(path, FILE_APPEND);
    file.println(buf);
    file.close();
  }
}

void handle_channel(Plant p_obj, uint8_t valve, char *logpath)
{

  if(p_obj.op_mode == 1) //moisture
  {
    if(p_obj.moisture > p_obj.sensor_display)
    {
      pump_channel(valve, watering_time, pump_time);
      log_moisture_info(plant1, logpath, 1);
    }
  }
  else if(p_obj.op_mode == 2) //time
  {
    if(p_obj.interval_ready)
    {
      p_obj.interval_ready = false;
      pump_channel(valve, p_obj.volume, pump_volume);
      log_moisture_info(plant1, logpath, 2);
    }
  }
}

void sensor_update()
{
  uint16_t moist_degree = (moist_dry - moist_wet)/100;
  if(plant1.op_mode == 1)
  {
    plant1.sensor_raw = read_sensor(s1);
    plant1.sensor_display = 100-((plant1.sensor_raw - moist_wet)/moist_degree);
    log_moisture_info(plant1, sd_plant1_logs, 0);
  }
  if(plant1.op_mode == 1)
  {
    plant2.sensor_raw = read_sensor(s2);
    plant2.sensor_display = 100-((plant2.sensor_raw - moist_wet)/moist_degree);
    log_moisture_info(plant2, sd_plant2_logs, 0);
  }
  if(plant1.op_mode == 1)
  {
    plant3.sensor_raw = read_sensor(s3);
    plant3.sensor_display = 100-((plant3.sensor_raw - moist_wet)/moist_degree);
    log_moisture_info(plant3, sd_plant3_logs, 0);
  }
  if(plant1.op_mode == 1)
  {
    plant4.sensor_raw = read_sensor(s4);
    plant4.sensor_display = 100-((plant4.sensor_raw - moist_wet)/moist_degree);
    log_moisture_info(plant4, sd_plant4_logs, 0);
  }
  
  char buf[128];
  if(pconf.debug_level > 0)
  {
    sprintf(buf, "Raw :: S1: %d, S2: %d, S3: %d, S4: %d", plant1.sensor_raw, plant2.sensor_raw, plant3.sensor_raw, plant4.sensor_raw);
    Serial.println(buf);
    sprintf(buf, "100 :: S1: %d, S2: %d, S3: %d, S4: %d", plant1.sensor_display, plant2.sensor_display, plant3.sensor_display, plant4.sensor_display);
    Serial.println(buf);
  }

}

uint16_t read_sensor(uint8_t sensor)
{
  uint32_t value_sum = 0;

  for(uint8_t i = 0; i < samplecount; i++)
  {
    value_sum += analogRead(sensor);
    delay(100);
  }
  return (uint16_t)(value_sum / samplecount);
}

void pump_channel(uint8_t channel, uint16_t amount, bool ml_secs)
{
  uint16_t pumptime = 60 * amount / pconf.pumprate;
  uint8_t led;
  switch (channel)
  {
  case v1:
    led = LED1;
    break;
  case v2:
    led = LED2;
    break;
  case v3:
    led = LED3;
    break;
  case v4:
    led = LED4;
    break;
  }

  digitalWrite(channel, HIGH);
  digitalWrite(led, LOW);
  delay(100);
  digitalWrite(pump, HIGH);
  if(ml_secs)
    delay(pumptime * 1000);
  else 
    delay(amount*1000);
  digitalWrite(pump, LOW);
  delay(100);
  digitalWrite(channel, LOW);
  digitalWrite(led, HIGH);

}

void IRAM_ATTR timer1()
{
plant1.interval_ready = true;
}

void IRAM_ATTR timer2()
{
plant2.interval_ready = true;
}

void IRAM_ATTR timer3()
{
plant3.interval_ready = true;
}

void IRAM_ATTR timer4()
{
plant4.interval_ready = true;
}

// Run OTA and Web Service on different core than main loop
void Web_Tasks(void *pvParameters)
{
  page_handles();
  input_handles();
  output_handles();

  server.begin();
  Serial.println("Webserver Started");

  for (;;)
  {
    ArduinoOTA.handle();
    vTaskDelay(1);
  }
}
