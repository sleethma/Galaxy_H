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
int fadeAmount10 = 5;  // Set the amount to fade I usually do 5, 10, 15, 20, 25 etc even up to 255.
int fadeAmount15 = 5;  // Set the amount to fade I usually do 5, 10, 15, 20, 25 etc even up to 255.
int fadeAmount13 = 5;  // Set the amount to fade I usually do 5, 10, 15, 20, 25 etc even up to 255.


int brightness = 0; 
int brightness10 = 0;
int brightness13 = 0;
int brightness15 = 0;
int randRed, randGreen, randBlue;

  const int BLUE = 0x0000FF; // 70%
 //const int BLUE_WHITE = 0x48D1CC; // 11%
const int WHITE = 0x48D1CC ; // 8%
const int YELLOW_WHITE = 0xFFFF00; // 5%
// const int YELLOW = 0xFFD700; // 3%
const int LIGHT_ORANGE = 0xFF8C00; // 2%
// const int ORANGE_RED = 0x800000 ; // 1%

 

void setup()
{
  FastLED.addLeds<WS2812B, PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
    randRed = rand() % 255;
       randGreen = rand() % 255;
       randBlue = rand() % 255;
 
 
}

void loop()
{ 
  
  int ledNum = rand() % 10 + 18;

  //testing();

  pulse10(ledNum, BLUE, 2, &brightness10, &fadeAmount10);  
  // pulse10(12,randRed,randGreen,randBlue, 2, &brightness13, &fadeAmount13);
  // pulse10(15, randRed,randGreen,randBlue,2, &brightness15, &fadeAmount15);
  
  FastLED.show();

}


// todo, generate random color inside this function
void pulse10(int num, int color,  int delayTime, int *brightness10P, int *fadeAmount10){

  
//leds[num].setRGB(red,green,blue);  
  *brightness10P = *brightness10P + *fadeAmount10;
  
  // reverse the direction of the fading at the ends of the fade: 
  if(*brightness10P < 1 || *brightness10P > 254)
  {
    *fadeAmount10 = -*fadeAmount10; 
    if( *brightness10P < 1){
//       randRed = rand() % 254;
//       randGreen = rand() % 254;
//       randBlue = rand() % 254;
         setNewColor(num);
    }
  }  

  delay(delayTime);  // This delay sets speed of the fade. I usually do from 5-75 but you can always go higher.
  leds[num].fadeLightBy(*brightness10P);
  // delete this comment
}

// todo: implement map below
void setNewColor(int num){
  int colorSelector = rand() % 7 + 1;
  switch (colorSelector)
  {
    case 1:
        leds[num] = CRGB(BLUE);
    break;
    default:
    leds[num] = CRGB(YELLOW_WHITE);
  }
  
}

void testing(){
  leds[18] = CRGB(BLUE); // blue
  leds[19] = CRGB(0x48D1CC); //blue white
  leds[20] = CRGB(WHITE); 
  leds[21] = CRGB(YELLOW_WHITE); 
  leds[22] = CRGB(0xFFD700);
  leds[23] = CRGB(LIGHT_ORANGE);
  leds[24] = CRGB(0x800000);
}
