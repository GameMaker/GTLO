#include <FastLED.h>
#include <stdio.h>

#define LED_DATA_PIN 3
#define PIN_JOY_BUTTON 0
#define PIN_JOY_X 1
#define PIN_JOY_Y 2

#define NUM_LEDS 50
CRGB leds[NUM_LEDS];
char debugString[512];

int currentLED;
int brightness;
int brightnessDir;
int brightnessSpeed;
int reading;

void setup()
{

  /* add setup code here */
	FastLED.addLeds<WS2811, LED_DATA_PIN>(leds, NUM_LEDS);

	currentLED = NUM_LEDS / 2;
	brightness = 255;
	brightnessDir = -1;
	brightnessSpeed = 5;
}

void loop()
{

  /* add main program code here */
	leds[currentLED] = CRGB(brightness, brightness, brightness);
	updateLights(10);
	sprintf(debugString, "current: %d, bright: %d, brightD: %d, bspeed: %d", currentLED, brightness, brightnessDir, brightnessSpeed);
	Serial.println(debugString);
	brightness += (brightnessDir * brightnessSpeed);
	if (brightness < 2) {
		brightnessDir = 1;
	}
	else if (brightness > 253) {
		brightnessDir = -1;
	}
	reading = analogRead(PIN_JOY_X);
	if (reading < 412) {
		currentLED = min(NUM_LEDS -1, currentLED + 1);
	}
	else if (reading > 612) {
		currentLED = max(0, currentLED - 1);
	}
	reading = analogRead(PIN_JOY_Y);
	if (reading < 412) {
		brightnessSpeed = max(0, brightnessSpeed - 1);
	}
	else if (reading > 612) {
		brightnessSpeed = brightnessSpeed + 1;
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