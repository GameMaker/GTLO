#include <FastLED.h>
#include <stdio.h>

#define LED_DATA_PIN 3
#define PIN_JOY_BUTTON 0
#define PIN_JOY_X 1
#define PIN_JOY_Y 2

#define NUM_LEDS 50
#define FRAME_TIME 20 // 20/1000 = 50fps

CRGB leds[NUM_LEDS];
char debugString[512];

int reading;

/****************************************************************************
**                                                                         **
**                             PADDLE                                      **
**                                                                         **
*****************************************************************************/
class Paddle {
public:
	float loc;
	int width;
	CRGB color;
	int brightness;
	int brightnessDir;
	int brightnessSpeed;
	void update();
	void render();

	Paddle() {
		loc = NUM_LEDS / 2;
		width = 1;
		color = CRGB::Blue;
		brightness = 255;
		brightnessDir = -1;
		brightnessSpeed = 2;
	}
};

void Paddle::update() {
}

int lowLED;
int highLED;
int intensity;
void Paddle::render() {
	// You need to start at loc - 1/2 width, rounding down
	lowLED = max(0, ((int)loc) / 2);
	// And go up to loc + 1/2 width, rounding up
	highLED = min(NUM_LEDS - 1, (((int)loc) / 2) + 1);
	sprintf(debugString, "Loc: %d, width: %d, Low: %d, High: %d", loc, width, lowLED, highLED);
	Serial.println(debugString);
	for (int i = lowLED; i < highLED; i++) {
		// The formula (scaled to 0.0-1.0) is:
		// intensity = max(0, min(1, (("half the width minus 1") + 1) - ("absolute distance from loc to i")
		// Because I said so.
		// Or you can look at the JPG or the Excel file in this folder and figure it out yourself.
		// Oh, and then you need to multiply by 255, since that was from 0 to 1
		intensity = max(0, min(1, (((width - 1) / 2) + 1 - (abs(loc - i))))) * 255;
		sprintf(debugString, "intensity on %d is %d", i, intensity);
		Serial.println(debugString);
		leds[i].r = color.r * intensity;
		leds[i].g = color.g * intensity;
		leds[i].b = color.b * intensity;
	}
}

Paddle paddle;

void setup()
{

  /* add setup code here */
	FastLED.addLeds<WS2811, LED_DATA_PIN>(leds, NUM_LEDS);

	paddle.loc = NUM_LEDS / 2;

	Serial.println("Done setting up!");
}

void loop()
{

  /* add main program code here */
	// TODO Instead of delay, use a nextFrameMillis system to try and maintain 50, so it doesn't slow down if frames start taking significant millis
	sprintf(debugString, "Looping millis %u", millis());
	Serial.println(debugString);
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