#include <FastLED.h>

#define DATA_PIN 3
#define NUM_LEDS 50
CRGB leds[NUM_LEDS];

void setup()
{

  /* add setup code here */
	FastLED.addLeds<WS2811, DATA_PIN>(leds, NUM_LEDS);

}

int i;
void loop()
{

  /* add main program code here */
	for (i = 0; i < NUM_LEDS; i++) {
		fill_solid(leds, NUM_LEDS, CRGB::Black);
		leds[i] = CRGB::Wheat;
		updateLights(100);
	}
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
void updateLights(int delayTime) {
	FastLED.show();
	FastLED.delay(delayTime);
	fill_solid(leds, NUM_LEDS, CRGB::Black);
}