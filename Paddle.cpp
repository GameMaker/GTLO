#include "Paddle.h"
#if _VM_DEBUG
#pragma GCC optimize ("O0")
#endif

Paddle::Paddle() {};

Paddle::~Paddle() {/*Nothing to deconstruct*/ }

void Paddle::init(CRGB leds[NUM_LEDS]) {
	Serial.println("In the Paddle init");
	_loc = 25;
	_width = 1;
	_color = CRGB::Blue;
	_brightness = 255;
	_brightnessDir = -1;
	_brightnessSpeed = 2;
	_leds = leds;
	Serial.println("Done setting up paddle, it's:");
	Serial.println(_loc);
	Serial.println(_width);
	Serial.println(_color);
	Serial.println(_brightness);
	Serial.println(_brightnessDir);
	Serial.println(_brightnessSpeed);
}

void Paddle::update() {
}

int lowLED;
int highLED;
int intensity;
int i;

void Paddle::render() {
	// You need to start at loc - 1/2 width, rounding down
	lowLED = max(0, ((int)_loc) / 2);
	// And go up to loc + 1/2 width, rounding up
	highLED = min(_NUM_LEDS - 1, (((int)_loc) / 2) + 1);
	sprintf(debugString, "Loc: %d, width: %d, Low: %d, High: %d", _loc, _width, lowLED, highLED);
	Serial.println(debugString);
	for (i = lowLED; i < highLED; i++) {
		// The formula (scaled to 0.0-1.0) is:
		// intensity = max(0, min(1, (("half the width minus 1") + 1) - ("absolute distance from loc to i")
		// Because I said so.
		// Or you can look at the JPG or the Excel file in this folder and figure it out yourself.
		// Oh, and then you need to multiply by 255, since that was from 0 to 1
		intensity = max(0, min(1, (((_width - 1) / 2) + 1 - (abs(_loc - i))))) * 255;
		sprintf(debugString, "intensity on %d is %d", i, intensity);
		Serial.println(debugString);
		Serial.flush();
		_leds[i].r = _color.r * intensity;
		_leds[i].g = _color.g * intensity;
		_leds[i].b = _color.b * intensity;
	}
	Serial.println("Done rendering paddle, i is");
	Serial.println(i);
}
