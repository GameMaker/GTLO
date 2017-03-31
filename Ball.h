#pragma once
#include <stdio.h>
#include<FastLED.h>
#include "Constants.h"

class Ball
{
private:
	int i;

public:
	int _loc; // 0 to GAME_FIELD_UPPER_LIMIT, which translates to 0.00  to 100.00%
	int _width;
	int _height;
	CRGB _color;
	CRGB* _leds;
	int _NUM_LEDS;
	void update();
	void render();
	int _speedVert;
	int _speedHoriz;
	void init(CRGB leds[NUM_LEDS]);
	Ball();
	~Ball();
};

