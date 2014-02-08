#include "battery_bar.h"
	
static InverterLayer *battery_layer;
static int battery_percent;
static GRect battery_bar_container;
static int bar_shape;

void resize_bar() {
	GRect new_bar = battery_bar_container;
	if(bar_shape == BATTERY_BAR_VERTICAL) {
		//float proportion = (0.72365);
		float new_size = battery_bar_container.size.h * (float)battery_percent / 100;
		//new_bar.size.h = (int)(battery_bar_container.size.h * (proportion));
		new_bar.size.h = (int)(new_size);
		//new_bar.size.h = 100;
	}
	layer_set_frame(inverter_layer_get_layer(battery_layer), new_bar);
}

void update_battery_layer(BatteryChargeState state) {
	battery_percent = state.charge_percent;
	resize_bar();
}

InverterLayer* create_battery_layer(GRect initial_box, int shape)
{
	battery_bar_container = initial_box;
	bar_shape = shape;
	battery_layer = inverter_layer_create(initial_box);
	//layer_set_frame(inverter_layer_get_layer(battery_layer), GRect(30,30,30,30));
	update_battery_layer(battery_state_service_peek());
	return battery_layer;
}

//This should probably go away when I've finished testing:
void move_it_down(ClickRecognizerRef recognizer, void *context) {
	GRect new_rect = GRect(40,40,40,40);
	layer_set_frame(inverter_layer_get_layer(battery_layer), new_rect);
}