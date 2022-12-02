#include <FastLED.h>

#define LED_PIN     14
#define NUM_LEDS    20
#include <Servo.h>
int tempPin = 12;
CRGB leds[NUM_LEDS];

int pos;


int a = 5;
int b = 3;

char current = False;
char used = False;
void setup() {

  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);

}

void loop() {

 LEDgoals();
 if (current != used & a < b){
   servoflag1();
   //update the used one into new one
 }
 if (current != used & a > b){
   servoflag2();
   //update the used one into new one
 }
 if(current != used & a = b){
   myservo.write(0);
   //update the used one into new one
}

void LEDgoals(){
  for (int i = 0; i <= a-1; i++) {
    leds[i] = CRGB ( 0, 0, 254);
    FastLED.show();
    delay(200);
  }
  for (int x = 15; x <= 14+b; x++) {
    leds[x] = CRGB ( 255, 0, 0);
    FastLED.show();
    delay(200);
  }
}


void servoFlag1(){
        myservo.write(0);
        delay(1000);
        myservo.write(180);
        delay(1000);
        myservo.write(0);
        delay(1000);
        myservo.write(180);
        delay(1000);
        myservo.write(0);
        delay(1000);
        myservo.write(180);
        delay(1000);
        myservo.write(45);
      }
}

void servoFlag2(){
        myservo.write(0);
        delay(1000);
        myservo.write(180);
        delay(1000);
        myservo.write(0);
        delay(1000);
        myservo.write(180);
        delay(1000);
        myservo.write(0);
        delay(1000);
        myservo.write(180);
        delay(1000);
        myservo.write(135);
      }
}