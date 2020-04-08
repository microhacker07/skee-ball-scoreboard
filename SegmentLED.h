#ifndef SegmentLED_h
#define SegmentLED_h

/*
SegmentLED - Library to turn FastLED's arrays into 7-Segment displays

The LEDs have to be in a 'S' like pattern with the last LED at the right side.
This library has a dependency on the FastLED library.

Created by Nathaniel Bock
*/

#include <FastLED.h>

class SegmentLED
{
public:
  SegmentLED(int last_led, int segment);
  SegmentLED(int last_led, int segmentX, int segmentY);
  void getSegmentFromPattern(CRGB leds[], int index, byte pattern[]);
  // Sets the segment to a pattern array in the form of 7 bits

  void displayOff(CRGB leds[]);
  // Turns Off the segment
  void displayDigit(CRGB leds[], int digit);
  // Set the segment to a base 10 number
  void displayInteger(CRGB leds[], int number, int place);
  // Set the segment to a digit at a certain number place in an integer 

  void simplePattern(CRGB leds[], int pos, int pattern[]);
  // Simplfied version of getSegmentFromPattern that simply turns on a single segment.

  CRGB display_color;

private:
  int end_led;        // Last LED in the display
  int segment_sizeX;   // Size of the segments on the X axis.
  int segment_sizeY;   // Size of the segments on the y axis.
  
  // Segment code for representing hexdecimal. Stored as bytes to save space.
  const byte segment_from_hex[16] = {
  B1110111, // 0
  B0010001, // 1
  B1101011, // 2
  B0111011, // 3
  B0011101, // 4
  B0111110, // 5
  B1111110, // 6
  B0010011, // 7
  B1111111, // 8
  B0011111, // 9
  B1011111, // a
  B1111100, // b
  B1101000, // c
  B1111001, // d
  B1101110, // e
  B1001110  // f
  };
};

#endif
