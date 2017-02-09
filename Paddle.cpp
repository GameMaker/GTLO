#include "Paddle.h"
#if _VM_DEBUG
#pragma GCC optimize ("O0")
#endif

Paddle::Paddle() {};

Paddle::~Paddle() {/*Nothing to deconstruct*/ }

void Paddle::init(CRGB leds[NUM_LEDS]) {
	Serial.println("In the Paddle init");
	_loc = NUM_LEDS / 2;
	_width = 1;
	_color = CRGB::Blue;
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
		_loc = min(NUM_LEDS - 1, _loc + (joyX - 512) / JOY_X_SCALE_FACTOR);
	}
	else if (joyX < 512 - JOY_HALF_DEAD_ZONE) {
		_loc = max(0, _loc - ((512 - joyX) / JOY_X_SCALE_FACTOR));
	}

	if (!adjustedPaddleLastFrame) {
		if (joyY > 512 + JOY_HALF_DEAD_ZONE) {
			_width = min(NUM_LEDS / 2, _width + 1);
			adjustedPaddleLastFrame = true;
		}
		else if (joyY < 512 - JOY_HALF_DEAD_ZONE) {
			_width = max(1, _width - 1);
			adjustedPaddleLastFrame = true;
		}
	}
	else if (abs(joyY - 512) < JOY_HALF_DEAD_ZONE) {
		adjustedPaddleLastFrame = false;
	}

}

int lowLED;
int highLED;
float intensity;

void Paddle::render() {
	// You need to start at loc - 1/2 width, rounding down
	lowLED = (int)max(0, _loc - (_width / 2));
	// And go up to loc + 1/2 width, rounding up
	highLED = min(NUM_LEDS - 1, _loc + (_width / 2) + 2);
	intensity = 0;
	for (i = lowLED; i < highLED; i++) {
		// The formula (scaled to 0.0-1.0) is:
		// intensity = max(0, min(1, (("half the width minus 1") + 1) - ("absolute distance from loc to i")
		// Because I said so.
		// Or you can look at the JPG or the Excel file in this folder and figure it out yourself.
		intensity = max(0, min(1, ((((_width - 1) / 2.0) + 1.0) - (abs(_loc - i)))));
		intensity *= intensity;
		_leds[i].r = _color.r * intensity;
		_leds[i].g = _color.g * intensity;
		_leds[i].b = _color.b * intensity;
	}
}
