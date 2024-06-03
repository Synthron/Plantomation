#pragma once

#include <Arduino.h>
#include "config.h" 

class channels {
    public:
        bool p0;
        bool p1;
        uint16_t ch;
        bool s0;
        bool s1;
        void set_ch(uint8_t channel);
        void set_pump(uint8_t pump);
        void set_state(uint8_t state);
        void update(void);
};