#include "Paddle.h"
//#if _VM_DEBUG
//#pragma GCC optimize ("O0")
//#endif

Paddle::Paddle() {};

Paddle::~Paddle() {/*Nothing to deconstruct*/ }

void Paddle::init(CRGB leds[NUM_LEDS]) {
	// _loc is on a scale from 0 to TOTAL_GAME_FIELD_UNITS, and is not scaled by number of LEDs.
	// Game starts with the paddle in the middle of the line. All spatial units are in %, but using 
	// integer math, with each unit equalling 1/100 of 1%.
	_loc = (TOTAL_GAME_FIELD_UNITS / 2) - 1;
	// Width also needs to be in percentage. Since I'm using 50 LEDs as a start, 1 light is 2%, so 20/1000ths.
	_width = LED_WIDTH; 
	// Start one LED wide
	// TODO - put a warning message if you try to play on less than 50.
	_color = CRGB::Red;
	_brightness = 255;
	_brightnessDir = -1;
	_brightnessSpeed = 2;
	_leds = leds;
}

int joyX, joyY;
bool adjustedPaddleLastFrame = false;

void Paddle::update() {
	joyX = analogRead(PIN_JOY_X);
	joyY = analogRead(PIN_JOY_Y);

	if (joyX > 512 + JOY_HALF_DEAD_ZONE) {
		_loc = min(GAME_FIELD_UPPER_LIMIT, _loc + (joyX - 512) / JOY_X_SCALE_FACTOR);
	}
	else if (joyX < 512 - JOY_HALF_DEAD_ZONE) {
		_loc = max(0, _loc - ((512 - joyX) / JOY_X_SCALE_FACTOR));
	}

	if (!adjustedPaddleLastFrame) {
		if (joyY > 512 + JOY_HALF_DEAD_ZONE) {
			_width = min(TOTAL_GAME_FIELD_UNITS / 2, _width + LED_WIDTH);
			adjustedPaddleLastFrame = true;
		}
		else if (joyY < 512 - JOY_HALF_DEAD_ZONE) {
			_width = max(100, _width - LED_WIDTH);
			adjustedPaddleLastFrame = true;
		}
	}
	else if (abs(joyY - 512) < JOY_HALF_DEAD_ZONE) {
		adjustedPaddleLastFrame = false;
	}
}

int start;
int end;
int intensity;

void Paddle::render() {
	// You need to start at loc - 1/2 width, rounding down
	start = max(0, _loc - _width);
	start = start / LED_WIDTH;
	// And go up to loc + 1/2 width, rounding up
	end = 2 + (min(GAME_FIELD_UPPER_LIMIT, _loc + _width) / LED_WIDTH);
	//intensity = 0;
	for (i = start; i < end; i++) {
		// The formula (scaled to 0.0-1.0) is:
		// intensity = max(0, min(1, (("half the width minus 1") + 1) - ("absolute distance from loc to i")
		// Because I said so.
		// Or you can look at the JPG or the Excel file in this folder and figure it out yourself.

		// EDIT - redoing it as integer, using just a simple "how far away am I, clamp that to 100%"
		intensity = 100 + _width - abs((i * LED_WIDTH) - _loc);
		intensity = max(0,min(100, intensity));
		_leds[i].r = max(0, _leds[i].r - ((_color.r * intensity) / 100));
		_leds[i].g = max(0, _leds[i].g - ((_color.g * intensity) / 100));
		_leds[i].b = max(0, _leds[i].b - ((_color.b * intensity) / 100));
	}
}
