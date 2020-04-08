#include "SegmentLED.h"
#include <Arduino.h>

/*
SegmentLED - Library to turn FastLED's arrays into 7-Segment displays

The LEDs have to be in a 'S' like pattern with the last LED at the right side.
This library has a dependency on the FastLED library.

Created by Nathaniel Bock
*/

SegmentLED::SegmentLED(int last_led, int segment) {
  end_led = last_led;
  segment_sizeX = segment;
  segment_sizeY = segment;
}

SegmentLED::SegmentLED(int last_led, int segmentX, int segmentY) {
  end_led = last_led;
  segment_sizeX = segmentX;
  segment_sizeY = segmentY;
}

void SegmentLED::getSegmentFromPattern(CRGB leds[], int index, byte pattern[]) {
  for (int current_led = 0; current_led < segment_size * 7; current_led++) {
    if ( bitRead( pattern[ index ], current_led / segment_size ) ) {
      leds[ end_led - current_led ] = display_color;
    }
  }
}

void SegmentLED::displayOff(CRGB leds[]) {
  for (int current_led = 0; current_led < segment_size * 7; current_led++) {
    leds[ end_led - current_led ] = CRGB::Black;
  }
}

void SegmentLED::displayDigit(CRGB leds[], int digit) {
  displayOff(leds);
  getSegmentFromPattern(leds, digit, segment_from_hex);
}

void SegmentLED::displayInteger(CRGB leds[], int number, int place) {
  number = (number / (int)pow(10, place)) % 10;
  displayDigit(leds, number);
}

void SegmentLED::simplePattern(CRGB leds[], int pos, int pattern[]) {
  displayOff(leds);
  for (int current_led = 0; current_led < segment_size*7; current_led++) {
    if (pattern[ pos ] == current_led / segment_size) {
      leds[ end_led - current_led ] = display_color;
    } else {
      leds[ end_led - current_led ] = CRGB::Black;
    }
  }
}
