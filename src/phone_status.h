#pragma once

#include "pebble.h"

#define PHONE_STATUS_WHITE 0
#define PHONE_STATUS_BLACK 1

BitmapLayer* create_status_layer(int x_coord, int y_coord, int colour);