# Plantomation

DIY plant watering system based on ESP32-WROOM32

## Features

- up to 4 channels simultaneously
- water spill detection
- one pump for all channels, selected via valves
- simple Web-Interface for quick overview and configuration
- SD-Card for local wifi config and logging

## ToDos

- Documentation
  - [x] Config Explanation
  - [x] Wifi Management Explanation
  - [ ] UI Explanation
  - [x] Control Modes Explanation
  - [x] General Mode of Operation Explanation
- PCB
  - [x] Finish Design
  - [x] Order
  - [x] Assemble
  - [x] Test
- Firmware
  - Frontend
    - [x] Ajax working
    - [x] Multi-Page working
    - [x] Main-Page with all necessary information
    - [x] Config page
    - [x] About page
  - Backend
    - [x] Wifi Management
    - [x] File Management
      - [x] SPIFFS
      - [x] SD Card (preferred if available)
      - [X] Copy config from SD to SPIFFS
    - [ ] Implement Setup via Webpage
      - [x] Channels
      - [x] WiFi
      - [x] General Config
      - [x] Debug
      - [ ] Sensor calibration
    - [x] Objects for channels
    - [x] Config object
    - [x] Wifi object
    - [x] implement sensor read
    - [x] implement spill detection
    - [x] implement Moisture Control
    - [x] implement Time Control (timers)
    - [ ] implement internal water volume counter
    - [ ] implement low-water-alarm
    - [x] Debug-Levels
    - [x] Log-Levels


