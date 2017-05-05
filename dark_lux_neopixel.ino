#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN1 2
#define PIN2 3

#define BLUE 75
#define RED 255
#define MAX_GREEN 50

Adafruit_NeoPixel strips [] = {
  Adafruit_NeoPixel(30, PIN1, NEO_GRB + NEO_KHZ800),
  Adafruit_NeoPixel(30, PIN2, NEO_GRB + NEO_KHZ800)
};


uint8_t i, j;
uint32_t pixelColor;

void setup() {
  #if defined (__AVR_ATtiny85__)
    if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif

  uint8_t g;
  randomSeed(analogRead(0));

  for(i=0; i<2; i++) {
    strips[i].begin();
  }

  for(i=0; i<2; i++) {
    for(j=0; j< strips[i].numPixels(); j++) {
      g = random(MAX_GREEN);
      strips[i].setPixelColor(j, strips[i].Color(RED, g, BLUE+1));
    }
  }
  
  for(i=0; i<2; i++) {
    strips[i].show();
  }
}

void loop() {
  for(i=0; i<2; i++) {
    for(j=0; j< strips[i].numPixels(); j++) {
      pixelColor = purpleBeatG(strips[i], j);
      strips[i].setPixelColor(j, pixelColor);
    }
  }
  
  for(i=0; i<2; i++) {
    strips[i].show();
  }
  
  delay(2);
}

uint32_t purpleBeatG(Adafruit_NeoPixel &strip, uint16_t i) {
  uint32_t color = strip.getPixelColor(i);
  uint8_t r, g, b;
  
  r = (color >> 16);
  g = (color >>  8);
  b = (color      );

  if (b > BLUE) {
    g++;
    if (g > MAX_GREEN) {
      g = MAX_GREEN;
      b = BLUE - 1;
    }
  } else {
    g--;
    if (g < 1) {
      g = 1;
      b = BLUE + 1;
    }
  }
  return strip.Color(r, g, b); 
}

