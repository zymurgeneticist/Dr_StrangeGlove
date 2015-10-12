// To be used on Adafruit Gemma in a Dr. Strange costume
// Visit http://www.instructables.com/id/Dr-Strange-Costume/

#include <TinyWireM.h>
#include <USI_TWI_Master.h>
#include <Adafruit_TinyLSM303.h>

#include <Adafruit_NeoPixel.h>

#define PIXEL_PIN 1

Adafruit_TinyLSM303 lsm;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(5, PIXEL_PIN, NEO_GRB + NEO_KHZ800);

int t1 = 0; // timer variable, one for every finger
int t2 = 0; 
int t3 = 0; 
int t4 = 0; 
int t5 = 0; 

void setup() 
{
  // Try to initialise
  if (!lsm.begin())
  {
       while (1);
  }
  strip.begin();
  colorWipe(strip.Color(255, 255, 255), 0); // check to see if its working
  strip.show(); 
  delay(1000); // wait a second
  colorWipe(strip.Color(0, 0, 0), 0); // turn the lights off at first
  strip.show(); // Initialize all pixels to 'off'
}

void loop() 
{
  lsm.read();
   if((int)lsm.accelData.y > 0){ // fling arms up quick to activate
    while((int)lsm.accelData.y > 0){ // if arms remain up...
      if(t1 == 0){
        rdmClr(t1,0);
      }
       if(t2 == 0){
        rdmClr(t2,1);
      }
       if(t3 == 0){
        rdmClr(t3,2);
      }
       if(t4 == 0){
        rdmClr(t4,3);
      }
       if(t5 == 0){
        rdmClr(t5,4);
      }
    lsm.read(); // read the sensor
    t1--;t2--;t3--;t4--;t5--; // decrement the timers
    delay(100); // wait 0.1s to cycle
    }
  }
  else
  {
    colorWipe(strip.Color(0, 0, 0), 0); // keep the lights off if not active
  }
}
void rdmClr(int t, int np){
  int n; // random number variable
  int rd; // red value variable
  int gr; // green value variable
  int bl; // blue value variable
  int clrVals[] = {0,125,255}; // values for RGB color to pick from
  t = random(2,11); // reset timer to a random number
  n = random(3);
  rd = clrVals[n]; // set red color variable to random n number
  n = random(3);
  gr = clrVals[n]; // set green color variable to random n number
  n = random(3);
  bl = clrVals[n]; // set blue color variable to random n number
  strip.setPixelColor(np,rd,gr,bl); // set color for neopixel
  strip.show(); // send color to neopixel
  if(np==0)t1=t;  if(np==1)t2=t;  if(np==2)t3=t;  if(np==3)t4=t;  if(np==4)t5=t;
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

