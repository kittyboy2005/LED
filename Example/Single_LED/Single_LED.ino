/*
 ===================================================================== 
                        LED LIBRARY EXAMPLE Sketch
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

#include <LED.h>

byte temp; //storage for LED pattern info

LED led1(11); //Declaring D11 as led pin (single LED)

void setup()
{
  led_pattern(0);
}

void loop()
{
  led1.Update();
  
  static unsigned long prev;
  if(millis()> prev + 10*1000)  //10 second interval for each pattern
  {
    if(temp<5)
    {
      temp++;
    }
    else
    {
      temp=0;
    }
    led_pattern(temp);
    
    prev=millis();
  }  
}

void led_pattern(byte type)  //LED PATTERN MAKER
{
  switch(type)
  {
    case 0: //short blink
            led1.Power(1);         // Power on
            led1.Blink(10, 2000);  // Blink: 10ms on, 2000ms off
            break;
            
    case 1: //long blink
            led1.Power(1);         // power on
            led1.Blink(1000,1000); // Blink: 1s on, 1s off
            break; 
            
    case 2: //short fade effect
            led1.Power(1);         // Power on
            led1.Fade();           // Fade: fading amount= 5, refresh rate=20ms [default values]
            break;
            
    case 3: //long fade effect
            led1.Power(1);         // Power on
            led1.Fade(1, 20);      // Fade: fading amount= 1, refresh rate=20ms
            break;
            
    case 4: //Power off
            led1.Power(0);         // Power off
            break;        
  }
}
