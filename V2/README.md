# Plantomation

DIY plant watering system based on ESP32-S3-WROVER

## Features

- up to 12 channels simultaneously
- water spill detection
- Ambient Temperature and Humidity Sensor
- two pumps for all channels, selected via valves
  - Water pump
  - fertilizer pump
- simple Web-Interface for quick overview and configuration
- SD-Card for local wifi config and logging

## ToDos

- Documentation
  - [ ] Config Explanation
  - [ ] Wifi Management Explanation
  - [ ] UI Explanation
  - [ ] Control Modes Explanation
  - [ ] General Mode of Operation Explanation
- PCB
  - [x] Finish Design
  - [ ] Order
  - [ ] Assemble
  - [ ] Test
- Firmware
  - Frontend
    - [ ] Ajax working
    - [ ] Multi-Page working
    - [ ] Main-Page with all necessary information
    - [ ] Config page
    - [ ] About page
  - Backend
    - [ ] Wifi Management
    - [ ] File Management
      - [ ] SPIFFS
      - [ ] SD Card (preferred if available)
      - [ ] Copy config from SD to SPIFFS
    - [ ] Implement Setup via Webpage
      - [ ] Channels
      - [ ] WiFi
      - [ ] General Config
      - [ ] Debug
      - [ ] Sensor calibration
    - [ ] Objects for channels
    - [ ] Config object
    - [ ] Wifi object
    - [ ] implement sensor read
    - [ ] implement spill detection
    - [ ] implement Moisture Control
    - [ ] implement Time Control (timers)
    - [ ] implement internal water volume counter
    - [ ] implement low-water-alarm
    - [ ] Debug-Levels
    - [ ] Log-Levels


