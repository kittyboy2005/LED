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

#ifndef led_h
#define led_h

#if (ARDUINO >=100)
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

class LED
{
  public:
    // Constructor 
   LED(byte pin, bool type);
   LED(byte pin);

    // Public Methods
    void Blink(unsigned int on, unsigned int off);
    void Blink();
    void Fade(byte fade_amount, byte update_speed);
    void Fade();
    void Power(bool en);
    void Update();
    
  private:
    // Private Methods
    void common_all();
    void common_blink();
    void common_fade();
    
    //global variables
    struct flasher_storage  
    {
      bool ledState :1;
      bool en :1;
      bool fade_en :1;
      bool blink_en :1;
      
      byte ledPin;
      byte brightness =0;
      byte fade_amount;
      byte fade_update_speed;
      
      unsigned int OnTime;
      unsigned int OffTime;
      unsigned long previousMillis;
    };
    
    flasher_storage s;

    #define DEFAULT_FADE_UPDATE  20
    #define DEFAULT_FADE_AMOUNT  5
    #define DEFAULT_BLINK_TIME  1000
};
#endif
