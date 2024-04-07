#include "main.h"

AsyncWebServer server(80); // Object of WebServer(HTTP port, 80 is defult)

//Class Objects
Wifi wifi;
Plant plant1, plant2, plant3, plant4;
SysConf pconf;

TaskHandle_t WebTasks;
struct tm timeinfo;

//variables

const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 3600;
const int   daylightOffset_sec = 0;

bool sd_en;
char s_wifi[20];
char s_system[22];
char s_plant1[20];
char s_plant2[20];
char s_plant3[20];
char s_plant4[20];

bool spill_indicator = false;

hw_timer_t *Timer_Channel1 = NULL;
hw_timer_t *Timer_Channel2 = NULL;
hw_timer_t *Timer_Channel3 = NULL;
hw_timer_t *Timer_Channel4 = NULL;

uint8_t maincounter = 0;

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
  pinMode(39, INPUT_PULLDOWN);

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
  else Serial.println("no SD detected!");

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
    copy_configs();
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
    pconf.load_config(SPIFFS, spiffs_system_conf);
    plant1.load_config(SPIFFS, spiffs_plant1_conf);
    plant2.load_config(SPIFFS, spiffs_plant2_conf);
    plant3.load_config(SPIFFS, spiffs_plant3_conf);
    plant4.load_config(SPIFFS, spiffs_plant4_conf);
    wifi_start(wifi, SPIFFS);
  }

  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

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
  
  if(maincounter > 100)
  {
    if(!(pconf.sysstate == SYS_SPILL))
    {
      handle_channel(plant1, v1, sd_plant1_logs);
      handle_channel(plant2, v2, sd_plant2_logs);
      handle_channel(plant3, v3, sd_plant3_logs);
      handle_channel(plant4, v4, sd_plant4_logs);
    }
    maincounter = 0;
  }
  maincounter++;
  
}

void copy_configs()
{
   pconf.save_config(SPIFFS, spiffs_system_conf);
  plant1.save_config(SPIFFS, spiffs_plant1_conf);
  plant2.save_config(SPIFFS, spiffs_plant2_conf);
  plant3.save_config(SPIFFS, spiffs_plant3_conf);
  plant4.save_config(SPIFFS, spiffs_plant4_conf);
}

void log_moisture_info(Plant p_obj, const char *path, uint8_t log_sort)
{
  if(pconf.log_level == 2 && sd_en)
  {
    getLocalTime(&timeinfo);
    char buf[200];
    switch (log_sort)
    {
    case 0: //log moisture sensor data
      sprintf(buf, "%4d-%02d-%02d;%02d:%02d:%02d;Moisture Sensor Value; %d\%", 
      timeinfo.tm_year+1900, timeinfo.tm_mon+1, timeinfo.tm_mday, 
      timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec, 
      p_obj.sensor_display);
      break;
    case 1: //log watering for time
      sprintf(buf, "%4d-%02d-%02d;%02d:%02d:%02d;watered for seconds; %d", 
      timeinfo.tm_year+1900, timeinfo.tm_mon+1, timeinfo.tm_mday, 
      timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec, 
      watering_time);
      break;
    case 2: //log watering for amount
      sprintf(buf, "%4d-%02d-%02d;%02d:%02d:%02d;watered with volume; %d;ml", 
      timeinfo.tm_year+1900, timeinfo.tm_mon+1, timeinfo.tm_mday, 
      timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec, 
      p_obj.volume);
      break;
    }
    if(pconf.debug_level > 0)
    {
      Serial.println(buf);
    }
    
    File file = SD.open(path, FILE_APPEND);
    file.println(buf);
    file.close();
  }
}

void log_event(uint8_t event)
{
  getLocalTime(&timeinfo);
  char buf[200];
  if(event == 0)
  {
    sprintf(buf, "%4d-%2d-%2d;%2d:%2d:%2d;Spillage detected", 
    timeinfo.tm_year+1900, timeinfo.tm_mon+1, timeinfo.tm_mday, 
    timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec);
    File file = SD.open(sd_events_logs, FILE_APPEND);
    file.println(buf);
    file.close();
  }
  else if(event == 1)
  {
    sprintf(buf, "%4d-%2d-%2d;%2d:%2d:%2d;Spillage cleared", 
    timeinfo.tm_year+1900, timeinfo.tm_mon+1, timeinfo.tm_mday, 
    timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec);
    File file = SD.open(sd_events_logs, FILE_APPEND);
    file.println(buf);
    file.close();
  }
}

void handle_channel(Plant p_obj, uint8_t valve, const char *logpath)
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

  if(pconf.debug_level > 0)
    {
      char string_buffer[512];
      sprintf(string_buffer, "%s: Humidity: %d; Sensor: %d; Mode: %d; Interval: %d; Volume: %d", 
      p_obj.name, p_obj.moisture, p_obj.sensor_display, p_obj.op_mode, p_obj.interval_time, p_obj.volume);
      Serial.println(string_buffer);
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

  pconf.spill_raw = read_sensor(spill);

  if(pconf.spill_raw >= 200 && !spill_indicator)
  {
    spill_indicator = true;
    pconf.sysstate = SYS_SPILL;
    log_event(0);
  }
  else if(pconf.spill_raw < 200 && spill_indicator)
  {
    spill_indicator = false;
    pconf.sysstate = SYS_OK;
    log_event(1);
  }

  char buf[128];
  if(pconf.debug_level > 0)
  {
    sprintf(buf, "Raw :: S1: %d, S2: %d, S3: %d, S4: %d, Spill: %d", plant1.sensor_raw, plant2.sensor_raw, plant3.sensor_raw, plant4.sensor_raw, pconf.spill_raw);
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
