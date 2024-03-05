#include "web.h"

void notFound(AsyncWebServerRequest *request)
{
  request->send(418, "text/plain", "418: I am a teapot!");
}

void page_handles()
{
  server.onNotFound(notFound);

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
  {
      request->send_P(200, "text/html", MAIN_page);
    if(pconf.debug_level > 0)
      Serial.println("Load Main Page");
    
  });

  server.on("/config", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    request->send_P(200, "text/html", CONFIG_page);
    if(pconf.debug_level > 0)
      Serial.println("Load Control Page");

  });

  server.on("/about", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    request->send_P(200, "text/html", ABOUT_page);
    if(pconf.debug_level > 0)
      Serial.println("Load About Page");

    });

  server.on("/favicon.ico", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "image/x-icon", favicon, favicon_len);
  });
}

void input_handles()
{
  server.on("/ch1", HTTP_GET, [&](AsyncWebServerRequest *request)
  {
    int params = request->params();
    for (int i = 0; i < params; i++)
    {
        AsyncWebParameter *p = request->getParam(i);
        if (strcmp(p->name().c_str(), "hume1") == 0)
          plant1.moisture = p->value().toInt();
        if (strcmp(p->name().c_str(), "Name1") == 0)
          strlcpy(plant1.name, p->value().c_str(), sizeof(plant1.name));
        if (strcmp(p->name().c_str(), "time1") == 0)
          plant1.interval_time = p->value().toInt();
        if (strcmp(p->name().c_str(), "vol1") == 0)
          plant1.volume = p->value().toInt();
    }
    timerAlarmWrite(Timer_Channel1, plant1.interval_time*60*60*1000000, true);

    if(sd_en)
      plant1.save_config(SD, s_plant1);
    else
      plant1.save_config(SPIFFS, s_plant1);

    if(pconf.debug_level > 0)
    {
      char string_buffer[512];
      sprintf(string_buffer, "%s: Humidity: %d; State: %d; Interval: %d; Volume: %d", 
      plant1.name, plant1.moisture, plant1.op_mode, plant1.interval_time, plant1.volume);
      Serial.println(string_buffer);
    }
    request->send(200, "text/html", "<!DOCTYPE html><html><head></head><body><script>close();</script></body></html>"); 
  });

  server.on("/ch2", HTTP_GET, [&](AsyncWebServerRequest *request)
  {
    int params = request->params();
    for (int i = 0; i < params; i++)
    {
        AsyncWebParameter *p = request->getParam(i);
        if (strcmp(p->name().c_str(), "hume2") == 0)
          plant2.moisture = p->value().toInt();
        if (strcmp(p->name().c_str(), "Name2") == 0)
          strlcpy(plant2.name, p->value().c_str(), sizeof(plant2.name));
        if (strcmp(p->name().c_str(), "time2") == 0)
          plant2.interval_time = p->value().toInt();
        if (strcmp(p->name().c_str(), "vol2") == 0)
          plant2.volume = p->value().toInt();
    }
    timerAlarmWrite(Timer_Channel2, plant2.interval_time*60*60*1000000, true);

    if(sd_en)
      plant2.save_config(SD, s_plant2);
    else
      plant2.save_config(SPIFFS, s_plant2);

    if(pconf.debug_level > 0)
    {
      char string_buffer[512];
      sprintf(string_buffer, "%s: Humidity: %d; State: %d; Interval: %d; Volume: %d", 
      plant2.name, plant2.moisture, plant2.op_mode, plant2.interval_time, plant2.volume);
      Serial.println(string_buffer);
    }
    request->send(200, "text/html", "<!DOCTYPE html><html><head></head><body><script>close();</script></body></html>"); 
  });

  server.on("/ch3", HTTP_GET, [&](AsyncWebServerRequest *request)
  {
    int params = request->params();
    for (int i = 0; i < params; i++)
    {
        AsyncWebParameter *p = request->getParam(i);
        if (strcmp(p->name().c_str(), "hume3") == 0)
          plant3.moisture = p->value().toInt();
        if (strcmp(p->name().c_str(), "Name3") == 0)
          strlcpy(plant3.name, p->value().c_str(), sizeof(plant3.name));
        if (strcmp(p->name().c_str(), "time3") == 0)
          plant3.interval_time = p->value().toInt();
        if (strcmp(p->name().c_str(), "vol3") == 0)
          plant3.volume = p->value().toInt();
    }
    timerAlarmWrite(Timer_Channel3, plant3.interval_time*60*60*1000000, true);

    if(sd_en)
      plant3.save_config(SD, s_plant3);
    else
      plant3.save_config(SPIFFS, s_plant3);

    if(pconf.debug_level > 0)
    {
      char string_buffer[512];
      sprintf(string_buffer, "%s: Humidity: %d; State: %d; Interval: %d; Volume: %d", 
      plant3.name, plant3.moisture, plant3.op_mode, plant3.interval_time, plant3.volume);
      Serial.println(string_buffer);
    }
    request->send(200, "text/html", "<!DOCTYPE html><html><head></head><body><script>close();</script></body></html>"); 
  });

  server.on("/ch4", HTTP_GET, [&](AsyncWebServerRequest *request)
  {
    int params = request->params();
    for (int i = 0; i < params; i++)
    {
        AsyncWebParameter *p = request->getParam(i);
        if (strcmp(p->name().c_str(), "hume4") == 0)
          plant4.moisture = p->value().toInt();
        if (strcmp(p->name().c_str(), "Name4") == 0)
          strlcpy(plant4.name, p->value().c_str(), sizeof(plant4.name));
        if (strcmp(p->name().c_str(), "time4") == 0)
          plant4.interval_time = p->value().toInt();
        if (strcmp(p->name().c_str(), "vol4") == 0)
          plant4.volume = p->value().toInt();
    }
    timerAlarmWrite(Timer_Channel4, plant4.interval_time*60*60*1000000, true);

    if(sd_en)
      plant4.save_config(SD, s_plant4);
    else
      plant4.save_config(SPIFFS, s_plant4);

    if(pconf.debug_level > 0)
    {
      char string_buffer[512];
      sprintf(string_buffer, "%s: Humidity: %d; State: %d; Interval: %d; Volume: %d", 
      plant4.name, plant4.moisture, plant4.op_mode, plant4.interval_time, plant4.volume);
      Serial.println(string_buffer);
    }
    request->send(200, "text/html", "<!DOCTYPE html><html><head></head><body><script>close();</script></body></html>"); 
  });

  server.on("/modes", HTTP_GET, [&](AsyncWebServerRequest *request)
  {

    int params = request->params();
    for (int i = 0; i < params; i++)
    {
        AsyncWebParameter *p = request->getParam(i);
        if (strcmp(p->name().c_str(), "ch1_mode") == 0)
          plant1.op_mode = p->value().toInt();
        if (strcmp(p->name().c_str(), "ch2_mode") == 0)
          plant2.op_mode = p->value().toInt();
        if (strcmp(p->name().c_str(), "ch3_mode") == 0)
          plant3.op_mode = p->value().toInt();
        if (strcmp(p->name().c_str(), "ch4_mode") == 0)
          plant4.op_mode = p->value().toInt();
    }

    if(plant1.op_mode == 2)
      timerAlarmEnable(Timer_Channel1);
    else
      timerAlarmDisable(Timer_Channel1);
    if(plant2.op_mode == 2)
      timerAlarmEnable(Timer_Channel2);
    else
      timerAlarmDisable(Timer_Channel2);
    if(plant3.op_mode == 2)
      timerAlarmEnable(Timer_Channel3);
    else
      timerAlarmDisable(Timer_Channel3);
    if(plant4.op_mode == 2)
      timerAlarmEnable(Timer_Channel4);
    else
      timerAlarmDisable(Timer_Channel4);

    if(sd_en)
    {
      plant1.save_config(SD, s_plant1);
      plant2.save_config(SD, s_plant2);
      plant3.save_config(SD, s_plant3);
      plant4.save_config(SD, s_plant4);
    }
    else
    {
      plant1.save_config(SPIFFS, s_plant1);
      plant2.save_config(SPIFFS, s_plant2);
      plant3.save_config(SPIFFS, s_plant3);
      plant4.save_config(SPIFFS, s_plant4);
    }

    if(pconf.debug_level > 0)
    {
      char string_buffer[512];
      sprintf(string_buffer, "mode1: %d, mode2: %d, mode3: %d, mode4: %d", 
      plant1.op_mode, plant2.op_mode, plant3.op_mode, plant4.op_mode);
      Serial.println(string_buffer);
    }
    request->send(200, "text/html", "<!DOCTYPE html><html><head></head><body><script>close();</script></body></html>"); });

  server.on("/sysconf", HTTP_GET, [&](AsyncWebServerRequest *request)
    {
    if(request->hasParam("pumprate"))
    {
      pconf.pumprate = request->getParam("pumprate")->value().toInt();
    }
    if(request->hasParam("loglevel"))
    {
      pconf.log_level = request->getParam("loglevel")->value().toInt();
    }
    if(request->hasParam("debuglevel"))
    {
      pconf.debug_level = request->getParam("debuglevel")->value().toInt();
    }

    if(sd_en)
      pconf.save_config(SD, s_system);
    else
      pconf.save_config(SPIFFS, s_system);

    if(pconf.debug_level > 0)
    {
      char string_buffer[512];
      sprintf(string_buffer, "Pumprate: %d, debug: %d, log: %d", 
      pconf.pumprate, pconf.debug_level, pconf.log_level);
      Serial.println(string_buffer);
    }
    request->send(200, "text/html", "<!DOCTYPE html><html><head></head><body><script>close();</script></body></html>"); 
  });

  server.on("/wifi_set", HTTP_POST, [&](AsyncWebServerRequest *request)
  {
    int params = request->params();
    for (int i = 0; i < params; i++)
    {
        AsyncWebParameter *p = request->getParam(i);
        if (strcmp(p->name().c_str(), "ssid") == 0)
          strlcpy(wifi.ssid, p->value().c_str(), sizeof(wifi.ssid));
        if (strcmp(p->name().c_str(), "passwd") == 0)
          strlcpy(wifi.passwd, p->value().c_str(), sizeof(wifi.passwd));
        if (strcmp(p->name().c_str(), "hostname") == 0)
          strlcpy(wifi.hostname, p->value().c_str(), sizeof(wifi.hostname));
        if (strcmp(p->name().c_str(), "wifimode") == 0)
          wifi.mode = p->value().toInt();
    }

    if(pconf.debug_level > 0)
    {
      char string_buffer[512];
      sprintf(string_buffer, "Hostname = %s; SSID = %s; Password= %s; Mode= %d", wifi.hostname, wifi.ssid, wifi.passwd, wifi.mode);
      Serial.println(string_buffer);
    }
    request->send(200, "text/html", "<!DOCTYPE html><html><head></head><body><script>close();</script></body></html>");
    if(sd_en)
      wifi.save_config(SD, s_wifi);
    else
      wifi.save_config(SPIFFS, s_wifi);
    delay(1000);
    ESP.restart(); 
  });

}

void output_handles()
{
  server.on("/initial", HTTP_GET, [&](AsyncWebServerRequest *request)
  {
    char string_buffer[512];

    StaticJsonDocument<512> doc;
    // moisture values
    doc["hume1"] = plant1.moisture;
    doc["hume2"] = plant2.moisture;
    doc["hume3"] = plant3.moisture;
    doc["hume4"] = plant4.moisture;
    // Op-Mode Values
    doc["mode1"] = plant1.op_mode;
    doc["mode2"] = plant2.op_mode;
    doc["mode3"] = plant3.op_mode;
    doc["mode4"] = plant4.op_mode;
    // Name Values
    doc["Name1"] = plant1.name;
    doc["Name2"] = plant2.name;
    doc["Name3"] = plant3.name;
    doc["Name4"] = plant4.name;
    // Interval-Time Values
    doc["time1"] = plant1.interval_time;
    doc["time2"] = plant2.interval_time;
    doc["time3"] = plant3.interval_time;
    doc["time4"] = plant4.interval_time;
    // Volume Values
    doc["vol1"] = plant1.volume;
    doc["vol2"] = plant2.volume;
    doc["vol3"] = plant3.volume;
    doc["vol4"] = plant4.volume;

    serializeJson(doc, string_buffer);

    request->send_P(200, "application/json", string_buffer);
    if(pconf.debug_level > 1)
    {
      Serial.print("Initial Value Request: ");
      Serial.println(string_buffer);
    }
  });

  server.on("/conf", HTTP_GET, [&](AsyncWebServerRequest *request)
  {
    String statestring;
    String statecolor;
    switch (pconf.sysstate)
    {
    case SYS_OK:
      statestring = "Operational";
      statecolor = "green";
      break;
    case SYS_SPILL:
      statestring = "Spill Detected";
      statecolor = "crimson";
      break;
    case SYS_FAIL:
      statestring = "Setup Fail";
      statecolor = "orange";
      break;
    case SYS_SD:
      statestring = "SD Fail - Internal Fallback";
      statecolor = "orange";
      break;
    case SYS_EMPTY:
      statestring = "Reservoir Empty";
      statecolor = "lightblue";
      break;

    default:
      statestring = "System Error";
      statecolor = "crimson";
      break;
    }
    char string_buffer[512];

    StaticJsonDocument<512> doc;
    // System values
    doc["system"] = statestring;
    doc["systemcolor"] = statecolor;
    doc["pumprate"] = pconf.pumprate;
    // Op-Mode Values
    doc["mode1"] = plant1.op_mode;
    doc["mode2"] = plant2.op_mode;
    doc["mode3"] = plant3.op_mode;
    doc["mode4"] = plant4.op_mode;
    doc["debug"] = pconf.debug_level;
    doc["log"] = pconf.log_level;

    serializeJson(doc, string_buffer);
    request->send_P(200, "application/json", string_buffer);
    if(pconf.debug_level > 1)
    {
      Serial.print("Config Values: ");
      Serial.println(string_buffer);
    }
  });

  server.on("/cyclic", HTTP_GET, [&](AsyncWebServerRequest *request)
  {
    String statestring;
    String statecolor;
    switch (pconf.sysstate)
    {
    case SYS_OK:
      statestring = "Operational";
      statecolor = "green";
      break;
    case SYS_SPILL:
      statestring = "Spill Detected";
      statecolor = "crimson";
      break;
    case SYS_FAIL:
      statestring = "Setup Fail";
      statecolor = "orange";
      break;
    case SYS_SD:
      statestring = "SD Fail - Internal Fallback";
      statecolor = "orange";
      break;
    case SYS_EMPTY:
      statestring = "Reservoir Empty";
      statecolor = "lightblue";
      break;

    default:
      statestring = "System Error";
      statecolor = "crimson";
      break;
    }
    char string_buffer[512];

    StaticJsonDocument<512> doc;
    // System values
    doc["system"] = statestring;
    doc["systemcolor"] = statecolor;
    doc["pumprate"] = pconf.pumprate;
    // Moisture Values in %
    doc["ADCValue1"] = plant1.sensor_display;
    doc["ADCValue2"] = plant2.sensor_display;
    doc["ADCValue3"] = plant3.sensor_display;
    doc["ADCValue4"] = plant4.sensor_display;

    serializeJson(doc, string_buffer);

    request->send_P(200, "application/json", string_buffer);
    if(pconf.debug_level > 1)
    {
      Serial.print("Cyclic Value Update: ");
      Serial.println(string_buffer);
    }
  });
}