#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN1 2
#define PIN2 3

#define BLUE 75
#define RED 255
#define MAX_GREEN 50

Adafruit_NeoPixel strip1 = Adafruit_NeoPixel(30, PIN1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip2 = Adafruit_NeoPixel(30, PIN2, NEO_GRB + NEO_KHZ800);

uint8_t i;
uint32_t pixelColor;

void setup() {
  #if defined (__AVR_ATtiny85__)
    if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif

  uint8_t g;
  randomSeed(analogRead(0));
  
  strip1.begin();
  strip2.begin();
  
  for(i=0; i< strip1.numPixels(); i++) {
    g = random(MAX_GREEN);
    strip1.setPixelColor(i, strip1.Color(RED, g, BLUE+1));
  }

  for(i=0; i< strip2.numPixels(); i++) {
    g = random(MAX_GREEN);
    strip2.setPixelColor(i, strip2.Color(RED, g, BLUE+1));
  }

  strip1.show(); 
  strip2.show();
}

void loop() {
  for(i=0; i< strip1.numPixels(); i++) {
    pixelColor = purpleBeatG(strip1, i);
    strip1.setPixelColor(i, pixelColor);
  }

  for(i=0; i< strip2.numPixels(); i++) {
    pixelColor = purpleBeatG(strip2, i);
    strip2.setPixelColor(i, pixelColor);
  }

  strip1.show(); 
  strip2.show();
  delay(4);
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

