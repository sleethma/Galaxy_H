#include <FastLED.h>

FASTLED_USING_NAMESPACE

// FastLED "100-lines-of-code" demo reel, showing just a few 
// of the kinds of animation patterns you can quickly and easily 
// compose using FastLED.  
//
// This example also shows one easy way to define multiple 
// animations patterns and have them automatically rotate.
//
// -Mark Kriegsman, December 2014

#if defined(FASTLED_VERSION) && (FASTLED_VERSION < 3001000)
#warning "Requires FastLED 3.1 or later; check github for latest code."
#endif

#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB
#define NUM_LEDS    81

CRGB leds[NUM_LEDS];
#define PIN 4 // Output Pin to Data Line on Strip
#define COLOR_ORDER GRB  // I had to change this for my strip if your color is off then you know.
int fadeAmount10 = 1;  // Set the amount to fade I usually do 5, 10, 15, 20, 25 etc even up to 255.
int fadeAmount15 = 1;  // Set the amount to fade I usually do 5, 10, 15, 20, 25 etc even up to 255.

int brightness = 0; 
int brightness10 = 0;
int brightness15 = 40;

void setup()
{
  FastLED.addLeds<WS2812B, PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
}

void loop()
{ 
  pulse10(10, 10);
  pulse15(15, 10);
  //  for(int i = 0; i < NUM_LEDS; i++ )
  //  {
  //  leds[i].setRGB(50,255,250);  // Set Color HERE!!!
  //  leds[i].fadeLightBy(brightness);
  // }
  
  FastLED.show();

}

void pulse10(int num, int delayTime){
leds[num].setRGB(50,255,25);  // Set Color HERE!!!
  brightness10 = brightness10 + fadeAmount10;
  // reverse the direction of the fading at the ends of the fade: 
  if(brightness10 < 1 || brightness10 > 254)
  {
    fadeAmount10 = -fadeAmount10 ; 
  }    
  delay(25);  // This delay sets speed of the fade. I usually do from 5-75 but you can always go higher.
  leds[num].fadeLightBy(brightness10);
}

void pulse15(int num, int delayTime){
leds[num].setRGB(50,255,25);  // Set Color HERE!!!
  brightness15 = brightness15 + fadeAmount15;
  // reverse the direction of the fading at the ends of the fade: 
  if(brightness15 < 1 || brightness15 > 254)
  {
    fadeAmount15 = -fadeAmount15 ; 
  }    
  delay(25);  // This delay sets speed of the fade. I usually do from 5-75 but you can always go higher.
  leds[num].fadeLightBy(brightness15);
}
