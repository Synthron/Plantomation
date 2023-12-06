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
    #ifdef serial_debug
      Serial.println("Load Main Page");
    #endif
  });

  server.on("/config", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    request->send_P(200, "text/html", CONFIG_page);
    #ifdef serial_debug
      Serial.println("Load Control Page");
    #endif
  });

  server.on("/about", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    request->send_P(200, "text/html", ABOUT_page);
    #ifdef serial_debug
      Serial.println("Load About Page");
    #endif
    });
}

void input_handles()
{
  server.on("/ch1", HTTP_GET, [](AsyncWebServerRequest *request)
            {
    if(request->hasParam("hume1"))
    {
      plant1.moisture = request->getParam("hume1")->value().toInt();
    }
    if(request->hasParam("Name1"))
    {
      strlcpy(plant1.name, request->getParam("Name1")->value().c_str(), sizeof(plant1.name));
    }
    if(request->hasParam("time1"))
    {
      plant1.interval_time = request->getParam("time1")->value().toInt();
    }
    if(request->hasParam("vol1"))
    {
      plant1.volume = request->getParam("vol1")->value().toInt();
    }
    #ifdef serial_debug
      memset(html_out_buffer, 0, sizeof html_out_buffer);
      sprintf(html_out_buffer, "%s: Humidity: %d; State: %d; Interval: %d; Volume: %d", 
      plant1.name, plant1.moisture, plant1.op_mode, plant1.interval_time, plant1.volume);
      Serial.println(html_out_buffer);
    #endif
    request->send(200, "text/html", "<!DOCTYPE html><html><head></head><body><script>close();</script></body></html>"); 
  });

  server.on("/ch2", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    if(request->hasParam("hume2"))
    {
      plant2.moisture = request->getParam("hume2")->value().toInt();
    }
    if(request->hasParam("Name2"))
    {
      strlcpy(plant2.name, request->getParam("Name2")->value().c_str(), sizeof(plant2.name));
    }
    if(request->hasParam("time2"))
    {
      plant2.interval_time = request->getParam("time2")->value().toInt();
    }
    if(request->hasParam("vol2"))
    {
      plant2.volume = request->getParam("vol2")->value().toInt();
    }
    #ifdef serial_debug
      memset(html_out_buffer, 0, sizeof html_out_buffer);
      sprintf(html_out_buffer, "%s: Humidity: %d; State: %d; Interval: %d; Volume: %d", 
      plant2.name, plant2.moisture, plant2.op_mode, plant2.interval_time, plant2.volume);
      Serial.println(html_out_buffer);
  #endif
    request->send(200, "text/html", "<!DOCTYPE html><html><head></head><body><script>close();</script></body></html>"); 
  });

  server.on("/ch3", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    if(request->hasParam("hume3"))
    {
      plant3.moisture = request->getParam("hume3")->value().toInt();
    }
    if(request->hasParam("Name3"))
    {
      strlcpy(plant3.name, request->getParam("Name3")->value().c_str(), sizeof(plant3.name));
    }
    if(request->hasParam("time3"))
    {
      plant3.interval_time = request->getParam("time3")->value().toInt();
    }
    if(request->hasParam("vol3"))
    {
      plant3.volume = request->getParam("vol3")->value().toInt();
    }
    #ifdef serial_debug
      memset(html_out_buffer, 0, sizeof html_out_buffer);
      sprintf(html_out_buffer, "%s: Humidity: %d; State: %d; Interval: %d; Volume: %d", 
      plant3.name, plant3.moisture, plant3.op_mode, plant3.interval_time, plant3.volume);
      Serial.println(html_out_buffer);
    #endif
    request->send(200, "text/html", "<!DOCTYPE html><html><head></head><body><script>close();</script></body></html>"); 
  });

  server.on("/ch4", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    if(request->hasParam("hume4"))
    {
      plant4.moisture = request->getParam("hume4")->value().toInt();
    }
    if(request->hasParam("Name4"))
    {
      strlcpy(plant4.name, request->getParam("Name4")->value().c_str(), sizeof(plant4.name));
    }
    if(request->hasParam("time4"))
    {
      plant4.interval_time = request->getParam("time4")->value().toInt();
    }
    if(request->hasParam("vol4"))
    {
      plant4.volume = request->getParam("vol4")->value().toInt();
    }
    #ifdef serial_debug
      memset(html_out_buffer, 0, sizeof html_out_buffer);
      sprintf(html_out_buffer, "%s: Humidity: %d; State: %d; Interval: %d; Volume: %d", 
      plant4.name, plant4.moisture, plant4.op_mode, plant4.interval_time, plant4.volume);
      Serial.println(html_out_buffer);
    #endif
    request->send(200, "text/html", "<!DOCTYPE html><html><head></head><body><script>close();</script></body></html>"); 
  });

  server.on("/modes", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    if(request->hasParam("ch1_mode"))
    {
      plant1.op_mode = request->getParam("ch1_mode")->value().toInt();
    }
    if(request->hasParam("ch2_mode"))
    {
      plant2.op_mode = request->getParam("ch2_mode")->value().toInt();
    }
    if(request->hasParam("ch3_mode"))
    {
      plant3.op_mode = request->getParam("ch3_mode")->value().toInt();
    }
    if(request->hasParam("ch4_mode"))
    {
      plant4.op_mode = request->getParam("ch4_mode")->value().toInt();
    }

    #ifdef serial_debug
      memset(html_out_buffer, 0, sizeof html_out_buffer);
      sprintf(html_out_buffer, "mode1: %d, mode2: %d, mode3: %d, mode4: %d", 
      plant1.op_mode, plant2.op_mode, plant3.op_mode, plant4.op_mode);
      Serial.println(html_out_buffer);
    #endif
    request->send(200, "text/html", "<!DOCTYPE html><html><head></head><body><script>close();</script></body></html>"); });

  server.on("/sysconf", HTTP_GET, [](AsyncWebServerRequest *request)
            {
    if(request->hasParam("pumprate"))
    {
      pconf.pumprate = request->getParam("pumprate")->value().toInt();
    }

    #ifdef serial_debug
      memset(html_out_buffer, 0, sizeof html_out_buffer);
      sprintf(html_out_buffer, "Pumprate: %d", 
      pconf.pumprate);
      Serial.println(html_out_buffer);
    #endif
    request->send(200, "text/html", "<!DOCTYPE html><html><head></head><body><script>close();</script></body></html>"); 
  });

  server.on("/wifi_set", HTTP_POST, [](AsyncWebServerRequest *request)
  {
    if(request->hasParam("ssid"))
    {
      strlcpy(wifi.ssid, request->getParam("ssid")->value().c_str(), sizeof(wifi.ssid));
    }
    if(request->hasParam("passwd"))
    {
      strlcpy(wifi.passwd, request->getParam("passwd")->value().c_str(), sizeof(wifi.passwd));
    }
    if(request->hasParam("hostname"))
    {
      strlcpy(wifi.hostname, request->getParam("hostname")->value().c_str(), sizeof(wifi.hostname));
    } 
    if(request->hasParam("wifimode"))
    {
      wifi.mode = request->getParam("wifimode")->value().toInt();
    }
    #ifdef serial_debug
      memset(html_out_buffer, 0, sizeof html_out_buffer);
      sprintf(html_out_buffer, "Hostname = %s; SSID = %s; Password= %s; Mode= %d", wifi.hostname, wifi.ssid, wifi.passwd, wifi.mode);
      Serial.println(html_out_buffer);
    #endif
    request->send(200, "text/html", "<!DOCTYPE html><html><head></head><body><script>close();</script></body></html>");
    wifi.save_config(SPIFFS, "/wifi.json");
    delay(100);
    ESP.restart(); 
  });
}

void output_handles()
{
  server.on("/initial", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    memset(html_out_buffer, 0, sizeof html_out_buffer);

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

    serializeJson(doc, html_out_buffer);

    request->send_P(200, "application/json", html_out_buffer);
    #ifdef serial_debug
      Serial.print("Initial Value Request: ");
      Serial.println(html_out_buffer);
    #endif
  });

  server.on("/conf", HTTP_GET, [](AsyncWebServerRequest *request)
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
    memset(html_out_buffer, 0, sizeof html_out_buffer);

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

    serializeJson(doc, html_out_buffer);
    request->send_P(200, "application/json", html_out_buffer);
    #ifdef serial_debug
      Serial.print("Config Values: ");
      Serial.println(html_out_buffer);
    #endif
  });

  server.on("/cyclic", HTTP_GET, [](AsyncWebServerRequest *request)
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

    memset(html_out_buffer, 0, sizeof html_out_buffer);

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

    serializeJson(doc, html_out_buffer);

    request->send_P(200, "application/json", html_out_buffer);
    #ifdef serial_debug
      Serial.print("Cyclic Value Update: ");
      Serial.println(html_out_buffer);
    #endif
  });
}