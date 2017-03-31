#pragma once
#define LED_DATA_PIN 3
#define PIN_JOY_BUTTON 0
#define PIN_JOY_X 1 // green wire
#define PIN_JOY_Y 0 // blue wire

#define NUM_LEDS 50
#define FRAME_TIME 20 // 20/1000 = 50fps

#define JOY_HALF_DEAD_ZONE 32
#define JOY_X_SCALE_FACTOR 25

//#define PADDLE_WIDTH_CHANGE_INCREMENT 100

#define TOTAL_GAME_FIELD_UNITS 10000
#define GAME_FIELD_UPPER_LIMIT (TOTAL_GAME_FIELD_UNITS - 1)

#define MAX_NUM_OF_BALLS 10

#define LED_WIDTH (TOTAL_GAME_FIELD_UNITS / NUM_LEDS)

extern char debugString[512];

extern int i;
extern int start;
extern int end;
extern int intensity;