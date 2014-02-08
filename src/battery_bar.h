#pragma once

#include "pebble.h"

//#define BATTERY_STATUS_WHITE 0
//#define BATTERY_STATUS_BLACK 1

//#define BATTERY_POSITION_LEFT 0
//#define BATTERY_POSITION_RIGHT 1
//#define BATTERY_POSITION_TOP 2
//#define BATTERY_POSITION_BOTTOM 3
#define BATTERY_BAR_HORIZONTAL 0
#define BATTERY_BAR_VERTICAL 1
	
InverterLayer* create_battery_layer(GRect initial_box, int shape);

//This should probably go away when I've finished testing:
void move_it_down(ClickRecognizerRef recognizer, void *context);