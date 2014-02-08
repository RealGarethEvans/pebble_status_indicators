#include <pebble.h>
#include "phone_status.h"
#include "battery_bar.h"
	
Window *my_window;
TextLayer *text_layer;
BitmapLayer *status_layer;
InverterLayer *battery_layer;

static void my_click_handler(void *context) {
	window_single_click_subscribe(BUTTON_ID_DOWN, move_it_down);
}

void handle_init(void) {
	  //This is just some "Hello, World" stuff:
	  static char* hello_text;
	  //hello_text = "Hello, 22";
	  int percentage = battery_state_service_peek().charge_percent;
	  snprintf (hello_text, 10, "Hello. %d", percentage);
	  my_window = window_create();
	  Layer *window_layer = window_get_root_layer(my_window);
	  GRect window_frame = layer_get_bounds(window_layer);
	  text_layer = text_layer_create(GRect(0, 0, 144, 20));
	  text_layer_set_text(text_layer, hello_text);
	  layer_add_child(window_layer, text_layer_get_layer(text_layer));
	
      //This is the layer with the bluetooth connection status:
	  int status_x = window_frame.size.w - 12;
	  int status_y = 0;
	  //status_layer = create_status_layer(window_frame);
	  status_layer = create_status_layer(status_x, status_y, PHONE_STATUS_BLACK);
	  layer_add_child(window_layer, bitmap_layer_get_layer(status_layer));
	
	  //This is the layer with the battery status:
	  GRect battery_bar_rect = GRect(0,0,10,100);
	  int battery_bar_shape = BATTERY_BAR_VERTICAL;
	  battery_layer = create_battery_layer(battery_bar_rect, battery_bar_shape);
	  layer_add_child(window_layer, inverter_layer_get_layer(battery_layer));
	
	  //This is some testing on how to move and resize things:
	  window_set_click_config_provider(my_window, my_click_handler);
	
	  //Finally, display the window:
	  window_stack_push(my_window, true);
}

void handle_deinit(void) {
	  text_layer_destroy(text_layer);
	  bitmap_layer_destroy(status_layer);
	  window_destroy(my_window);
}

int main(void) {
	  handle_init();
	  app_event_loop();
	  handle_deinit();
}
