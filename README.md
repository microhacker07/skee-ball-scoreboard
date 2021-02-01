# skee-ball-scoreboard

This is coded part of a project that was made and entered into the JCC STEM WARS.

![Image of project](https://raw.githubusercontent.com/microhacker07/skee-ball-scoreboard/main/images/skee-ball_team.jpg)

As part of this team I programmed an ardiuno to detect, count, and display points for a skee-ball machine my teammates made out of plywood. We won first place for the Maker Event.

# The Hardware

The led display is made from an addressable string of christmas leds (specifically ws2811 leds). Also, to detect the balls falling through the hole, I used 
infrared leds and infrared sensors. When the ball falls through the hole it toggles the output of the "blue led" circuit to the ardiuno. The leds are aligned with a 3D printed bracket that
I designed to be mounted to the wooden scoreplate.

![Image of project](https://raw.githubusercontent.com/microhacker07/skee-ball-scoreboard/main/images/scoreplate_underside.png)

The program runs on an Ardiuno Nano (Blue Circuit with green led in the middle). Also a 5v power supply (on the right) was neccessary to power the microcontroller and leds.
The row of blue leds on the left are indictor leds to show if the infared sensors are working.

![Electronic hardware setup](https://raw.githubusercontent.com/microhacker07/skee-ball-scoreboard/main/images/hardware_setup.jpg)

The leds for the scoreboard display are also held in with a 3D printed frame that I designed. The leds I got have a little notch and I made it so they would be fitted into the holes.

![Electronic hardware setup](https://raw.githubusercontent.com/microhacker07/skee-ball-scoreboard/main/images/led_backpanel.jpg)

# The Software

The leds are controlled by the ardiuno help from the FastLED library.
I also created the SegmentLED class to help abstract and handle the display as a set of led digit segments instead of a set of 100 leds. This class makes it easier to change the number and color for each segment.
Also it has support for some simple byte-sized animations.
