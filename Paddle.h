#pragma once
#include <stdio.h>
#include <FastLED.h>
#include <Arduino.h>
#include "Constants.h"

/****************************************************************************
**                                                                         **
**                             PADDLE                                      **
**                                                                         **
*****************************************************************************/
class Paddle {
public:
	int _loc; // 0 to GAME_FIELD_UPPER_LIMIT, which translates to 0.00  to 100.00%
	int _width;
	CRGB _color;
	int _brightness;
	int _brightnessDir;
	int _brightnessSpeed;
	CRGB* _leds;
	int _NUM_LEDS;
	void update();
	void render();
	void init(CRGB leds[NUM_LEDS]);
	Paddle();
	~Paddle();
};