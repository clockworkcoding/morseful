#include "pebble_os.h"
#include "pebble_app.h"
#include "pebble_fonts.h"
#include "morse.h"

// 99757F7D519345DBA168168FBB6F2C65
#define MY_UUID { 0x99, 0x75, 0x7F, 0x7D, 0x51, 0x93, 0x45, 0xDB, 0xA1, 0x68, 0x16, 0x8F, 0xBB, 0x6F, 0x2C, 0x65 }
PBL_APP_INFO(MY_UUID, "Morseful", "kourge", 0x1, 0x0, INVALID_RESOURCE, APP_INFO_WATCH_FACE);


Window window;
TextLayer timeLayer;
uint32_t sequence[40];

void handle_second_tick(AppContextRef ctx, PebbleTickEvent *t);
void morse_pulse_time(char *time_string);
void morse_format_time(char *time_string, uint32_t *durations);
void handle_init_app(AppContextRef app_ctx);
void pbl_main(void *params);

void handle_second_tick(AppContextRef ctx, PebbleTickEvent *t) {
  (void)t;
  (void)ctx;

  static char timeText[] = "00:00:00";
  PblTm currentTime;

  get_time(&currentTime);
  string_format_time(timeText, sizeof(timeText), "%T", &currentTime);
  text_layer_set_text(&timeLayer, timeText);

  if (currentTime.tm_sec == 0 && currentTime.tm_min % 5 == 0) {
    vibes_double_pulse();
  }
}

void morse_pulse_time(char *time_string) {
  morse_format_time(time_string, sequence);
  VibePattern pattern = { .num_segments = 39, .durations = sequence };
  vibes_enqueue_custom_pattern(pattern);
}

void morse_format_time(char *time_string, uint32_t *durations) {
  int i = 0;

  static int positions[] = { 0, 1, 3, 4 };
  for (int j = 0; j < 4; j++) {
    int position = positions[j];
    char digit = time_string[position];

    switch (digit) {
    case '0':
      break;
    }
  }
}

void handle_init_app(AppContextRef app_ctx) {
  window_init(&window, "Morseful");
  window_stack_push(&window, true);
  window_set_background_color(&window, GColorBlack);

  text_layer_init(&timeLayer, GRect(29, 54, 144-40 /* width */, 168-54 /* height */));
  text_layer_set_text_color(&timeLayer, GColorWhite);
  text_layer_set_background_color(&timeLayer, GColorClear);
  text_layer_set_font(&timeLayer, fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD));

  // Ensures time is displayed immediately (will break if NULL tick event accessed).
  // (This is why it's a good idea to have a separate routine to do the update itself.)
  handle_second_tick(app_ctx, NULL);

  layer_add_child(&window.layer, &timeLayer.layer);
}


void pbl_main(void *params) {
  PebbleAppHandlers handlers = {
    .init_handler = &handle_init_app,
    .tick_info = {
      .tick_handler = &handle_second_tick,
      .tick_units = SECOND_UNIT
    }
  };
  app_event_loop(params, &handlers);
}
