#include <FastLED.h>
#include "SegmentLED.h"

/*
Segment Display

Reads from infrared photoresistors and displays a 4 digit scoreboard.

Uses the FastLED library and the SegmentLED library to setup and easily
write to a display made up of addressable leds. Used for score keeping of
a skee-ball machine. 

Created by Nathaniel Bock
*/

#define NUM_LEDS    100
#define DATA_PIN    12
#define BRIGHTNESS  50
#define LED_TYPE    WS2811
#define COLOR_ORDER RGB
CRGB leds[NUM_LEDS];

#define SCORE_PIN 10
#define NUMBER_OF_SCORE_PINS 6
#define MAX_TIME_MILLIS 60000
#define RED_MILLIS 5000

bool previousState[NUMBER_OF_SCORE_PINS], state[NUMBER_OF_SCORE_PINS];
unsigned long previousTime, currentTime, differenceTime;

int scoreboard;

int hole_points[] = {10, 20, 30, 50, 100, 100};

int pattern_position;

SegmentLED display_1(leds, 99, 3);
SegmentLED display_2(leds, 78, 3);
SegmentLED display_3(leds, 57, 3);
SegmentLED display_4(leds, 36, 3);

int rotate_pattern[] = {1,0,4,5,6,2,1};

byte two_rotate_pattern[] = {
  B0100010,
  B1000001,
  B0010100,
  B0100010
};

byte play_text[] = {
  B1001111, // P
  B1100100, // L
  B1011111, // A
  B0111101  // Y
  };

void setup() {
  //delay( 1000 ); // power-up safety delay
  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness( BRIGHTNESS );

  pinMode(LED_BUILTIN, OUTPUT);
  for (int i = 0; i < NUMBER_OF_SCORE_PINS; i++) {
    pinMode(SCORE_PIN - NUMBER_OF_SCORE_PINS, INPUT);
  }
}

void loop() {
  CRGB color;
  scoreboard = 0;

  const unsigned long timeToYellow = MAX_TIME_MILLIS * (2/3);
  const unsigned long timeToRed = MAX_TIME_MILLIS * (1/3);
  
  byte red = 0;
  byte green = 255;

  // Read Input Pins to detect current state.
  for (int i = 0; i < NUMBER_OF_SCORE_PINS; i++) {
    state[i] = digitalRead(SCORE_PIN - i);
    previousState[i] = digitalRead(SCORE_PIN - i);
  }

  // Timer setup
  previousTime = millis();
  currentTime = millis();
  differenceTime = currentTime - previousTime;

  while (differenceTime < MAX_TIME_MILLIS) {
    currentTime = millis();
    differenceTime = currentTime - previousTime;

    for (int i = 0; i < NUMBER_OF_SCORE_PINS; i++) {
      state[i] = digitalRead(SCORE_PIN - i);
      if (state[i] != previousState[i]) {
        previousState[i] = state[i];
        if (state[i]) {
          scoreboard += hole_points[i];
        }
      }
    }

    if (differenceTime % 500 == 0) {
      if ( (differenceTime < timeToYellow) && (red < 240) ) {
        red += 15;
      }
      if ( (differenceTime < timeToRed) && (green > 15) ) {
        green -= 15;
      }
    }
    
    color = CRGB(red, green, 0);
    setDisplay(color);

    if (differenceTime >= MAX_TIME_MILLIS - RED_MILLIS && differenceTime % 500 < 250) {
      clearDisplay();
    } else {
      displayNumber(scoreboard);
    }
    
    FastLED.show();
  }

  clearDisplay();

  delay(1000);

  color = CRGB::Teal;
  setDisplay(color);

  for (int i = 0; i < scoreboard + 1; i += 10) {
    if (i < scoreboard - 300) i += 40;
    displayNumber(i);
    FastLED.show();
    delay(150);
  }

  delay(10000);

  while (true) {

  color = CHSV(random(0, 255), 255, 255);
  setDisplay(color);

  pattern_position = 0;

  int randomInt = random(0, 3);

  for (int i = 0; i < 50; i++) {
    clearDisplay();

    switch (randomInt) {
      case 0:
      display_1.simplePattern(pattern_position, rotate_pattern);
      display_2.simplePattern(pattern_position, rotate_pattern);
      display_3.simplePattern(6 - pattern_position, rotate_pattern);
      display_4.simplePattern(6 - pattern_position, rotate_pattern);

      pattern_position = (pattern_position + 1) % 6;
      break;
      
      case 1:
      display_1.getSegmentFromPattern(pattern_position, two_rotate_pattern);
      display_2.getSegmentFromPattern(pattern_position, two_rotate_pattern);
      display_3.getSegmentFromPattern(3 - pattern_position, two_rotate_pattern);
      display_4.getSegmentFromPattern(3 - pattern_position, two_rotate_pattern);

      pattern_position = (pattern_position + 1) % 3;
      break;

      case 2:
      display_1.getSegmentFromPattern(3, play_text);
      display_2.getSegmentFromPattern(2, play_text);
      display_3.getSegmentFromPattern(1, play_text);
      display_4.getSegmentFromPattern(0, play_text);

      if ( pattern_position % 10 < 3 ) clearDisplay();

      pattern_position += 1;
      break;
    }
    FastLED.show();
    delay(100);
  }

  }
}

void displayNumber(int number) {
  display_1.displayInteger(number, 0);
  display_2.displayInteger(number, 1);
  display_3.displayInteger(number, 2);
  display_4.displayInteger(number, 3);
}

void clearDisplay() {
  display_1.displayOff();
  display_2.displayOff();
  display_3.displayOff();
  display_4.displayOff();
}

void setDisplay(CRGB color) {
  display_1.display_color = color;
  display_2.display_color = color;
  display_3.display_color = color;
  display_4.display_color = color;
}
