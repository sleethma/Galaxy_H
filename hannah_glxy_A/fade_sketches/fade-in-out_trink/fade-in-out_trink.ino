#include <FastLED.h>

FASTLED_USING_NAMESPACE

#if defined(FASTLED_VERSION) && (FASTLED_VERSION < 3001000)
#warning "Requires FastLED 3.1 or later; check github for latest code."
#endif

#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB
#define NUM_LEDS    81

CRGB leds[NUM_LEDS];
#define PIN 4 // Output Pin to Data Line on Strip
#define COLOR_ORDER GRB  // I had to change this for my strip if your color is off then you know.

// how often the sequence fires 
int fadeAmount = 1;
int fadeAmount10 = 1;  
int fadeAmount13 = 5; 
int fadeAmount15 = 5;  
int ledNum;
int ledNum2;

int brightness = 150; 
int brightness10 = 10;
int brightness13 = 100;
int brightness15 = 0;
int randRed, randGreen, randBlue;
int delayTime10;

const int BLUE = 0x0000FF; // 70%
const int BLUE_WHITE = 0x48D1CC; // 11%
const int WHITE = 0x48D1CC ; // 8%
const int YELLOW_WHITE = 0xFFFF00; // 5%
const int YELLOW = 0xFFD700; // 3%
const int LIGHT_ORANGE = 0xFF8C00; // 2%
const int ORANGE_RED = 0x800000 ; // 1%

int lastColor = 2;

void setup()
{
  FastLED.addLeds<WS2812B, PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
//    randRed = rand() % 255;
//       randGreen = rand() % 255;
//       randBlue = rand() % 255;
// Serial.begin(9600);
 //delay(1000);
 //ledNum = rand() % 10;
setLastColor(9, lastColor);

}

void loop()
{ 
  //ledNum2 = rand() % 10 + 18;
  

   //pulse10(ledNum, BLUE, delayTime10, &brightness10, fadeAmount10); 
   pulse(9); 
  //pulse13(ledNum2, BLUE, 2, &brightness13, &fadeAmount13);
  // pulse10(12,randRed,randGreen,randBlue, 2, 0, &fadeAmount13);
  // pulse10(15, randRed,randGreen,randBlue,2, &brightness15, &fadeAmount15);
  FastLED.show();


}
void pulse(int num){

  brightness= brightness + fadeAmount;

  if(brightness > 250){
      fadeAmount = -fadeAmount;
      setNewColor(num);
    //  Serial.println("new color");
  }
  if(brightness < 10){
    fadeAmount = -fadeAmount;
  }
  setLastColor(num, lastColor);
  leds[num].fadeLightBy(brightness);

  delay(50);
}

void setLastColor(int num, int color){
  switch (color)
 {
    case 1:
        leds[num] = CRGB(BLUE);
          //   Serial.println("Last Set........1");

    break;
    case 2:
        leds[num] = CRGB(0x48D1CC);
        //Serial.println("Last Set........2");

    break;
    case 3:
        leds[num] = CRGB(WHITE);
                   //  Serial.println("Last Set........3");

    break;
    case 4:
        leds[num] = CRGB(YELLOW_WHITE);   
                 //    Serial.println("Last Set........4");
     
    break;
    case 5:
        leds[num] = CRGB(0xFFD700);  
                //     Serial.println("Last Set........5");
      
    break;
    case 6:
        leds[num] = CRGB(LIGHT_ORANGE);
                //     Serial.println("Last Set........6");

    break;
    default:
    leds[num] = CRGB(0x800000);   
               //  Serial.println("Last Set........default");
     
  }
}

// todo, generate random color inside this function
void pulse10(int num, int color,  int delayTime, int brightness, int fadeAmount){  
brightness = brightness + fadeAmount;
// Serial.println(brightness);
  // reverse the direction of the fading at the ends of the fade: 
  if(brightness > 250){
    brightness10 = 0;
    fadeAmount10 = -fadeAmount10; 
  }  
  if(brightness < 1){
        fadeAmount10 = -fadeAmount10; 
        brightness10 = 10;
         setNewColor(num);
         ledNum = rand() % 10;
    }  

  delay(delayTime);  // This delay sets speed of the fade. I usually do from 5-75 but you can always go higher.
  leds[num] = lastColor;
  leds[num].fadeLightBy(brightness);
}

// todo: implement timing logic, & implement map below
void setNewColor(int num){
  int newColor = rand() % 7 + 1;
  lastColor = newColor;
  switch (newColor)
  {
    case 1:
        leds[num] = CRGB(BLUE);
    break;
    case 2:
        leds[num] = CRGB(0x48D1CC);
    break;
    case 3:
        leds[num] = CRGB(WHITE);
    break;
    case 4:
        leds[num] = CRGB(YELLOW_WHITE);        

    break;
    case 5:
        leds[num] = CRGB(0xFFD700);        
    break;
    case 6:
        leds[num] = CRGB(LIGHT_ORANGE);
    break;
    default:
    leds[num] = CRGB(0x800000);        
  }

}

void testing(){
  leds[18] = CRGB(BLUE); // blue
  leds[19] = CRGB(0x48D1CC); // blue white
  leds[20] = CRGB(WHITE); 
  leds[21] = CRGB(YELLOW_WHITE); 
  leds[22] = CRGB(0xFFD700);  // yellow
  leds[23] = CRGB(LIGHT_ORANGE);
  leds[24] = CRGB(0x800000);  // red
}

// todo, generate random color inside this function
void pulse13(int num, int color,  int delayTime, int *brightnessP, int *fadeAmountP){ 
//leds[num].setRGB(red,green,blue);  
  *brightnessP = *brightnessP + *fadeAmountP;
  
  // reverse the direction of the fading at the ends of the fade: 
  if(*brightnessP < 1 || *brightnessP > 254)
  {
    *fadeAmountP = -*fadeAmountP; 
    if( *brightnessP < 1){
         setNewColor(num);
    }
  }  

  delay(delayTime);  // This delay sets speed of the fade. I usually do from 5-75 but you can always go higher.
  leds[num].fadeLightBy(*brightnessP);
}
