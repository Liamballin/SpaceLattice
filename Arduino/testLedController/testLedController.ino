#include <FastLED.h>

#define SECTIONS 7
#define LEDS_PER_SECTION 10
#define DATA_PIN 5

CRGB leds[SECTIONS*LEDS_PER_SECTION];
int indexes[SECTIONS][LEDS_PER_SECTION];


void setup() {
  int step = 0;
  for(int s = 0; s < SECTIONS; s++){
    for(int l = 0; l < LEDS_PER_SECTION; l++){
      indexes[s][l] = step;
      step++;
    }
  }

    FastLED.addLeds<WS2811, DATA_PIN, GRB>(leds,SECTIONS*LEDS_PER_SECTION);  

  Serial.begin(9600);

}

int getIndex(int section, int led){
  return(indexes[section-1][led-1]);
}


void loop() {
  for(int i=0;i<SECTIONS*LEDS_PER_SECTION;i+=LEDS_PER_SECTION){
    CHSV col = CHSV(random8(),255,255);
    for(int j = 0; j < LEDS_PER_SECTION; j++){
      leds[i+j] = CRGB::Black;
//      Serial.println(i+j);

    }
  }
  
  leds[getIndex(4, 5)] = CRGB::Red;

  
  FastLED.show();
  delay(500);
  
}
