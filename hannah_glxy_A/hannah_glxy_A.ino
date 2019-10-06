#include <FastLED.h>

FASTLED_USING_NAMESPACE
// Led allocation
//  1-60 = stars
// 61 - 71 = tardis
// 72 -73 = white tardis light
// 74 - 81 = stars

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
  delay(3000); // 3 second delay for recovery
  
  // tell FastLED about the LED strip configuration
  FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);

  // set master brightness control
  FastLED.setBrightness(BRIGHTNESS);
}


// List of patterns to cycle through. 
typedef void (*SimplePatternList[])();
SimplePatternList gPatterns = {confetti};

uint8_t gCurrentPatternNumber = 0; // Index number of which pattern is current
uint8_t gHue = 0; // rotating "base color" used by many of the patterns
  
void loop()
{
  // Call the current pattern function once, updating the 'leds' array
  gPatterns[gCurrentPatternNumber]();

// todo: refactor to save resources
for(int i = 61; i < 72; i++){
      leds[i] = CRGB::DarkBlue;
      FastLED.delay(50);
      leds[i].fadeToBlackBy(100);
}
leds[73] = CRGB::White;
leds[72] = CRGB::White;


  
  // send the 'leds' array out to the actual LED strip
  FastLED.show();  
  // insert a delay to keep the framerate modest
  FastLED.delay(2000/FRAMES_PER_SECOND); 

  // do some periodic updates
  EVERY_N_MILLISECONDS( 1000 ) { gHue++; } // slowly cycle the "base color" through the rainbow
     

}



void confetti() 
{
  int chanceOfGlitter = 200;
  int pos = random16(NUM_LEDS);
  int randGlitter = random16(NUM_LEDS);
  int sat = 128;
  int bri = 250;
delay(200);
if (pos < 61 || pos > 73){
  uint8_t briChk = leds[randGlitter].getLuma();
          if( random8() < chanceOfGlitter && briChk > 20) {
    leds[ randGlitter ] += CRGB::White;
    FastLED.delay(50);
  leds[randGlitter] = CHSV(gHue, sat, bri);

 }else{
  leds[pos] = CHSV(gHue, sat, bri);
 }
  }
    fadeToBlackBy( leds, NUM_LEDS, 10);
  }

  





//  if( random8() < chanceOfGlitter) {
//    leds[ random16(NUM_LEDS) ] += CRGB::White;
//  }