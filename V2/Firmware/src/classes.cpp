#include "classes.h"

void channels::set_ch(uint8_t channel)
{
    if(channel == 0 || channel > 12)
        ch = 0;
    else if(channel <= 12)
    {
        ch = 0x1000;
        for(uint8_t i = 0; i < channel; i++)
            ch = ch >> 1;
    }
}

void channels::set_pump(uint8_t pump)
{
    switch (pump)
    {
    case 1:
        p0 = 1;
        p1 = 0;
        break;
    case 2:
        p0 = 0;
        p1 = 1;
        break;
    
    default:
        p0 = 0;
        p1 = 0;
        break;
    }
}

void channels::set_state(uint8_t state)
{
    switch (state)
    {
    case 1:
        s0 = 1;
        s1 = 0;
        break;
    case 2:
        s0 = 0;
        s1 = 1;
        break;
    
    default:
        s0 = 0;
        s1 = 0;
        break;
    }
}

void channels::update(void)
{
    bool data[16];
    data[0] = s0;
    data[1] = s1;
    for(uint8_t c = 0; c < 12; c++)
        data[c+2] = (ch >> c) & 0x0001;
    data[14] = p0;
    data[15] = p1;

    for(uint8_t i = 0; i < 16; i++)
    {
        digitalWrite(DOUT, data[i]);
        delayMicroseconds(1);
        digitalWrite(DCLK, HIGH);
        delayMicroseconds(1);
        digitalWrite(DCLK, LOW);
    }
    delayMicroseconds(1);
    digitalWrite(DLATCH, HIGH);
    delayMicroseconds(1);
    digitalWrite(DLATCH, LOW);
}
