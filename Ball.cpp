#include "Ball.h"

Ball::Ball()
{
}

void Ball::init(CRGB leds[NUM_LEDS]) {
	_loc = rand();
	_loc = _loc / (RAND_MAX / TOTAL_GAME_FIELD_UNITS);
	//_loc = _loc / RAND_MAX;
	_width = LED_WIDTH / 2;
	_color = CRGB::Blue;
	_height = 100;
	_speedVert = 0;
	_speedHoriz = rand() % 24;
	_leds = leds;
}

Ball::~Ball()
{
}

void Ball::update() {
	_speedVert -= 1;
	_height += _speedVert;
	if (_height < 0) {
		_height = 0;
		_speedVert = -_speedVert;
	}
	_loc += _speedHoriz;
	if (_loc > TOTAL_GAME_FIELD_UNITS) {
		_loc = TOTAL_GAME_FIELD_UNITS;
		_speedHoriz *= -1;
	}
	else if (_loc < 0) {
		_loc = 0;
		_speedHoriz *= -1;
	}
}

void Ball::render() {
	// You need to start at loc - 1/2 width, rounding down
	start = max(0, _loc - _width);
	start = start / LED_WIDTH;
	// And go up to loc + 1/2 width, rounding up
	end = 2 + (min(GAME_FIELD_UPPER_LIMIT, _loc + _width) / LED_WIDTH);
	for (i = start; i < end; i++) {
		// The formula (scaled to 0.0-1.0) is:
		// intensity = max(0, min(1, (("half the width minus 1") + 1) - ("absolute distance from loc to i")
		// Because I said so.
		// Or you can look at the JPG or the Excel file in this folder and figure it out yourself.

		// EDIT - redoing it as integer, using just a simple "how far away am I, clamp that to 100%"
		intensity = 100 + _width - abs((i * LED_WIDTH) - _loc);
		intensity = (100 * max(0, min(100, intensity))) / (101 - _height);
		_leds[i].r = max(0, _leds[i].r - ((_color.r * intensity) / 100));
		_leds[i].g = max(0, _leds[i].g - ((_color.g * intensity) / 100));
		_leds[i].b = max(0, _leds[i].b - ((_color.b * intensity) / 100));
	}
}