#pragma once
#define LED_DATA_PIN 3
#define PIN_JOY_BUTTON 0
#define PIN_JOY_X 1
#define PIN_JOY_Y 2

#define NUM_LEDS 50
#define FRAME_TIME 20 // 20/1000 = 50fps

#define JOY_HALF_DEAD_ZONE 32
#define JOY_X_SCALE_FACTOR 500.0

extern char debugString[512];

extern int i;