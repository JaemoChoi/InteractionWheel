/*
 TouchWheel.pde
 MPR121 WhellPad Example Code
 
 by:Waiman Zhao
 Mail:Binpower@foxmail.com
 created on: 11/2/14
 license: CC-SA 3.0
 
 Hardware: 3.3V Arduino Pro Mini
           SDA -> A4
           SCL -> A5
           IRQ -> D2
*/


#include <Wire.h>
#include <mpr121.h>
#include <drv2605.h>
#include <Adafruit_NeoPixel.h>

Adafruit_NeoPixel strip = Adafruit_NeoPixel(10, 6, NEO_GRB + NEO_KHZ800);
DRV2605 haptic;

int key = 0;
int pre_key;

void setup()
{ 
  Serial.begin(19200);
   if (haptic.init(false, true) != 0) Serial.println("init failed!");
   if (haptic.drv2605_AutoCal() != 0) Serial.println("auto calibration failed!");

  Wire.begin();
  CapaTouch.begin();
  strip.begin();
  strip.show();

  delay(500);
  Serial.println("START"); 
}


// =========  loop  =========
void loop()
{
  key=CapaTouch.wheelKey();

  if (key == 1) key =1;
      else if (key == 3)  key =2;
      else if (key == 5)  key =3;
      else if (key == 7)  key =4;
      else if (key == 9)  key =5;
      else if (key == 11) key =6;
      else if (key == 13) key =7;
            else key = 0;

  if((pre_key != key)&&(key !=0)){
//    Serial.print("wheel:"); 
//    Serial.println(key); 
     colorWipe(strip.Color(0, 0, 50), 10); // Red
     pre_key = key;
     }
 
	//delay(100);
}

void colorWipe(uint32_t c, uint8_t wait) { {
      strip.setPixelColor(key, c);
      strip.show();
      haptic.drv2605_Play_Waveform(1);
      // delay(wait);
       }

delay(100);

      for(int i=0; i<10; i++) {
      strip.setPixelColor(i, strip.Color(0, 0, 0));
      strip.show();
      //delay(wait);
      }
}

 
