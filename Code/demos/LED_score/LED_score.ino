#include <FastLED.h>

#define LED_PIN     14
#define NUM_LEDS    20

CRGB leds[NUM_LEDS];


int a = 5;
int b = 3;
void setup() {

  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);

}

void loop() {

  for (int i = 0; i <= a-1; i++) {
    leds[i] = CRGB ( 0, 0, 255);
    FastLED.show();
    delay(40);
  }
  for (int i = 8; i <= 7+b; i++) {
    leds[i] = CRGB ( 255, 0, 0);
    FastLED.show();
    delay(40);
  }
}