# Plantomation

DIY plant watering system based on ESP32-WROOM32

## Features

- up to 4 channels simultaneously
- water spill detection
- one pump for all channels, selected via valves
- simple Web-Interface for quick overview and configuration
- SD-Card for local wifi config and logging

## ToDos

- PCB
  - [x] Finish Design
  - [x] Order
  - [ ] Assemble
  - [ ] Test
- Firmware
  - Frontend
    - [x] Ajax working
    - [x] Multi-Page working
    - [x] Main-Page with all necessary information
    - [ ] Config page
    - [ ] About page
  - Backend
    - [x] Wifi Management
    - [ ] File Management
      - [x] SPIFFS
      - [ ] SD Card (preferred if available)
    - [ ] Implement Setup via Webpage
      - [x] Channels
      - [ ] General Config
      - [ ] Debug
      - [ ] Sensor calibration
    - [x] Objects for channels
    - [x] Config object
    - [x] Wifi object
    - [ ] implement sensor read
    - [ ] implement spill detection
    - [ ] implement Moisture Control
    - [ ] implement Time Control (timers)
    - [ ] implement internal water volume counter
    - [ ] implement low-water-alarm
    - [ ] Debug-Levels
    - [ ] Log-Levels
