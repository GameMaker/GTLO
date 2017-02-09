#include <FastLED.h>
#include <stdio.h>
#include "Paddle.h"
#include "Constants.h"

#if _VM_DEBUG
#pragma GCC optimize ("O0")
#endif

/* Globals */
int i;
char debugString[512];

CRGB leds[NUM_LEDS];

int reading;

Paddle paddle;

void setup()
{

  /* add setup code here */
	FastLED.addLeds<WS2811, LED_DATA_PIN>(leds, NUM_LEDS);

	paddle.init(leds);
}

void loop()
{

  /* add main program code here */
	// TODO Instead of delay, use a nextFrameMillis system to try and maintain 50, so it doesn't slow down if frames start taking significant millis
	paddle.update();
	paddle.render();
	render();
}

/****************************************************************************
**                                                                         **
**                             UTILITIES                                   **
**                                                                         **
*****************************************************************************/
/* These are useful bits of code that we'll use over and over, both in the
main loop and in our custom user functions. They're usually pretty small,
and do just one very specific thing.
*/

/* updateLights(int delayTime)
Updates the string of lights based on the 'leds' array, then waits for the specified amount of time before clearing the string
(i.e. turning off all the lights)
*/
void render() {
	FastLED.show();
	FastLED.delay(FRAME_TIME);
	fill_solid(leds, NUM_LEDS, CRGB::Black);
}