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

#define DATA_PIN    4
//#define CLK_PIN   4
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB
#define NUM_LEDS    81
CRGB leds[NUM_LEDS];

#define BRIGHTNESS          125
#define FRAMES_PER_SECOND  40

void setup() {
  Serial.begin(9600);
  delay(3000); // 3 second delay for recovery
  
  // tell FastLED about the LED strip configuration
  FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);

  // set master brightness control
  FastLED.setBrightness(BRIGHTNESS);
}


// List of patterns to cycle through.  Each is defined as a separate function below.
typedef void (*SimplePatternList[])();
SimplePatternList gPatterns = {confetti};

uint8_t gCurrentPatternNumber = 0; // Index number of which pattern is current
uint8_t gHue = 0; // rotating "base color" used by many of the patterns
  
void loop()
{
  // Call the current pattern function once, updating the 'leds' array
  gPatterns[gCurrentPatternNumber]();

// todo: refactor to save resources
for(int i = 60; i < 73; i++){
  Serial.print(i);
      leds[i] = CRGB::DarkBlue;
}

  
  // send the 'leds' array out to the actual LED strip
  FastLED.show();  
  // insert a delay to keep the framerate modest
  FastLED.delay(2000/FRAMES_PER_SECOND); 

  // do some periodic updates
  EVERY_N_MILLISECONDS( 1000 ) { gHue++; } // slowly cycle the "base color" through the rainbow
     

}



void confetti() 
{
  int chanceOfGlitter = 80;
  int pos = random16(NUM_LEDS);
  int sat = 128;
  int lastLit = 0;
delay(400);
if (pos < 60 || pos > 72){
  lastLit = pos;
  leds[pos] = CHSV(gHue, sat, 255);


//  leds[pos] += CHSV( gHue + random8(64), 200, brighten8_raw(50));
      
     // leds[pos].fadeToBlackBy( 125 );
}
    fadeToBlackBy( leds, NUM_LEDS, 10);


  }

  



//  if( random8() < chanceOfGlitter) {
//    leds[ random16(NUM_LEDS) ] += CRGB::White;
//  }


//  if( random8() < chanceOfGlitter) {
//    leds[ random16(NUM_LEDS) ] += CRGB::White;
//  }