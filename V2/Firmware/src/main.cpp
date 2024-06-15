#include "main.h"


channels ch_shift;

void setup() {
  // put your setup code here, to run once:
  //Serial.begin(115200);
  IO_Init();
  ch_shift.set_ch(0);
  ch_shift.set_pump(0);
  ch_shift.set_state(0);
  ch_shift.update();
}

void loop() {
  //Serial.println("test");
  for(uint8_t _t = 1; _t <= 12; _t++)
  {
    ch_shift.set_ch(_t);
    ch_shift.set_pump(_t%2+1);
    ch_shift.set_state(_t%2+1);
    ch_shift.update();
    delay(1000);
    ch_shift.set_ch(0);
    ch_shift.set_pump(0);
    ch_shift.update();
    delay(1000);

  }
  // put your main code here, to run repeatedly:
}


void IO_Init(void)
{
  pinMode(DOUT    , OUTPUT);
  pinMode(DCLK    , OUTPUT);
  pinMode(DLATCH  , OUTPUT);
  pinMode(CS2     , OUTPUT);
  pinMode(CS3     , OUTPUT);
  pinMode(CS1     , OUTPUT);
  pinMode(CS0     , OUTPUT);
  pinMode(DETECT  , INPUT);
  pinMode(CS4     , OUTPUT);

  digitalWrite(DOUT    , 0);
  digitalWrite(DCLK    , 0);
  digitalWrite(DLATCH  , 0);
  digitalWrite(CS2     , 1);
  digitalWrite(CS3     , 1);
  digitalWrite(CS1     , 1);
  digitalWrite(CS0     , 1);
  digitalWrite(CS4     , 1);
}