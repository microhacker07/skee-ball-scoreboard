#include "SegmentLED.h"
#include <Arduino.h>

/*
SegmentLED - Library to turn FastLED's arrays into 7-Segment displays

The LEDs have to be in a 'S' like pattern with the last LED at the right side.
This library has a dependency on the FastLED library.

Created by Nathaniel Bock
*/

SegmentLED::SegmentLED(CRGB leds[], int last_led, int segment) {
  end_led = last_led;
  segment_size = segment;

  for (int i = 0; i < segment_size * 7; i++) {
    segment_leds[i] = &leds[end_led - i];
  }
}

void SegmentLED::getSegmentFromPattern(int index, byte pattern[]) {
  for (int current_led = 0; current_led < segment_size * 7; current_led++) {
    if ( bitRead( pattern[ index ], current_led / segment_size ) ) {
      *segment_leds[current_led] = display_color;
    }
  }
}

void SegmentLED::displayOff() {
  for (int current_led = 0; current_led < segment_size * 7; current_led++) {
    *segment_leds[current_led] = CRGB::Black;
  }
}

void SegmentLED::displayDigit(int digit) {
  displayOff();
  getSegmentFromPattern(digit, segment_from_hex);
}

void SegmentLED::displayInteger(int number, int place) {
  number = (number / (int)pow(10, place)) % 10;
  displayDigit(number);
}

void SegmentLED::simplePattern(int pos, int pattern[]) {
  displayOff();
  for (int current_led = 0; current_led < segment_size*7; current_led++) {
    if (pattern[ pos ] == current_led / segment_size) {
      *segment_leds[current_led] = display_color;
    } else {
      *segment_leds[current_led] = CRGB::Black;
    }
  }
}
