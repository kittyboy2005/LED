/*
 ===================================================================== 
                             LED LIBRARY
 =====================================================================
 
MIT License

Copyright (c) 2021 Manzar-E-Hassin

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

Published on Friday, 12th November, 2021
Publisher: Manzar E Hassin

Library URL: https://github.com/kittyboy2005/LED 

*/


#include "LED.h"

LED::LED(byte pin, bool type)
{
  switch(type)
  {
    case 0: LED::Blink();
            break;
            
    case 1: LED::Fade();
            break;
  }
  s.ledPin = pin;
  LED::common_all();
}

LED::LED(byte pin)
{
  LED::Blink();
  s.ledPin = pin;
  LED::common_all();
}

void LED::Blink(unsigned int on, unsigned int off)
{
  LED::common_blink();
  s.OnTime = on;
  s.OffTime = off;
  
}

void LED::Blink()
{
  LED::common_blink();
  s.OnTime = s.OffTime = DEFAULT_BLINK_TIME;
}

void LED::Fade(byte fade_amount, byte update_speed)
{
  LED::common_fade();
  s.fade_amount = fade_amount;
  s.fade_update_speed = update_speed;

}

void LED::Fade()
{
  LED::common_fade();
  s.fade_amount = DEFAULT_FADE_AMOUNT;
  s.fade_update_speed= DEFAULT_FADE_UPDATE;
}

void LED::Power(bool en)
{
  s.en=en;
  if(en==0)
  {
    s.ledState = LOW;
    digitalWrite(s.ledPin, s.ledState);
  }
}

void LED::Update()
{
  unsigned long now = millis();
  if((s.blink_en) and (s.fade_en == 0) and (s.en) and (s.ledState == HIGH) and (now - s.previousMillis >= s.OnTime)) //ON
  {
    s.ledState = LOW;
    s.previousMillis = now;
    digitalWrite(s.ledPin, s.ledState);
  }
  
  else if ((s.blink_en) and (s.fade_en == 0) and (s.en) and (s.ledState == LOW) and (now - s.previousMillis >= s.OffTime)) //OFF
  {
    s.ledState = HIGH;
    s.previousMillis = now;
    digitalWrite(s.ledPin, s.ledState);
  }
  
  else if((s.blink_en==0) and (s.fade_en) and (s.en) and (now - s.previousMillis >= s.fade_update_speed)) //FADE
  {
    analogWrite(s.ledPin, s.brightness);
    s.brightness = s.brightness + s.fade_amount;
    if(s.brightness <= 0 or s.brightness >= 255) 
    {
      s.fade_amount = -s.fade_amount;
    }
    s.previousMillis = now;
  }
}

void LED::common_all()
{
  pinMode(s.ledPin, OUTPUT);
  s.en=1;
  s.previousMillis = 0;
}

void LED::common_blink()
{
  s.blink_en = 1;
  s.fade_en = 0;
  s.ledState = LOW;
}

void LED::common_fade()
{
  s.blink_en=0;
  s.fade_en = 1;
  s.brightness=0;
}
