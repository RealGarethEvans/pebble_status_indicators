#include "phone_status.h"

static bool connectionStatus = false;
static BitmapLayer *phone_layer;
static GBitmap *phone_bitmap;

void bluetooth_state_handler(bool connected)
//copied directly from BinaryPebble.c . Sorry
{
    if(!connected && connectionStatus)
    {
        vibes_double_pulse();
    }
    connectionStatus = connected;
    if(connected)
    {
        if(!phone_bitmap)
        {
            phone_bitmap = gbitmap_create_with_resource(RESOURCE_ID_PHONE_WHITE);
            bitmap_layer_set_bitmap(phone_layer, phone_bitmap);
        }
    }
    else
    {
        if(phone_bitmap)
        {
            bitmap_layer_set_bitmap(phone_layer, NULL);
            gbitmap_destroy(phone_bitmap);
            phone_bitmap = NULL;
        }
    }
}

//BitmapLayer* create_status_layer(GRect parent_frame){
BitmapLayer* create_status_layer(int x_coord, int y_coord, int colour){
	//phone_layer = bitmap_layer_create((GRect) { .origin= {parent_frame.size.w - 20, 5}, .size = {12, 20}});
	phone_layer = bitmap_layer_create((GRect) { .origin= {x_coord, y_coord}, .size = {12, 12}});
	bitmap_layer_set_background_color(phone_layer, GColorClear);
	if(colour == PHONE_STATUS_WHITE)
	{
		bitmap_layer_set_compositing_mode(phone_layer, GCompOpAssignInverted);
	}
	bluetooth_connection_service_subscribe(bluetooth_state_handler);
	bluetooth_state_handler(bluetooth_connection_service_peek());
	return phone_layer;
}