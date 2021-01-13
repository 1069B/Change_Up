#include "robot/graphical_interface/styles.hpp"

int GUI_STYLES::color_red;// TODO: How is this used
int GUI_STYLES::color_blue;
int GUI_STYLES::color_green;
int GUI_STYLES::color_defualt;

lv_style_t GUI_STYLES::red_button_released;
lv_style_t GUI_STYLES::red_button_pressed;
lv_style_t GUI_STYLES::blue_button_released;
lv_style_t GUI_STYLES::blue_button_pressed;
lv_style_t GUI_STYLES::green_button_released;
lv_style_t GUI_STYLES::green_button_pressed;
lv_style_t GUI_STYLES::default_button_released;
lv_style_t GUI_STYLES::default_button_pressed;

lv_style_t GUI_STYLES::red_text;
lv_style_t GUI_STYLES::blue_text;
lv_style_t GUI_STYLES::green_text;
lv_style_t GUI_STYLES::black_text;
lv_style_t GUI_STYLES::white_text;

lv_style_t GUI_STYLES::default_background;
lv_style_t GUI_STYLES::popup_background;

lv_style_t GUI_STYLES::default_meter;

lv_style_t GUI_STYLES::switch_background;
lv_style_t GUI_STYLES::switch_inactive;
lv_style_t GUI_STYLES::switch_on;
lv_style_t GUI_STYLES::switch_off;

void defineStyles(){
  using namespace GUI_STYLES;
  //Default relesed style
  lv_style_copy(&default_button_released, &lv_style_plain);
  default_button_released.body.radius = 8;
  default_button_released.body.main_color = LV_COLOR_WHITE;
  default_button_released.body.grad_color = LV_COLOR_WHITE;
  default_button_released.text.color = LV_COLOR_RED;

  //Default relesed style
  lv_style_copy(&default_button_pressed, &default_button_released);
  default_button_pressed.body.main_color = LV_COLOR_SILVER;
  default_button_pressed.body.grad_color = LV_COLOR_SILVER;

  //Red Rel style
  lv_style_copy(&red_button_released, &default_button_released);
  red_button_released.body.main_color = LV_COLOR_RED;
  red_button_released.body.grad_color = LV_COLOR_RED;
  red_button_released.text.color = LV_COLOR_MAKE(255, 255, 255);

  //Red pressed style
  lv_style_copy(&red_button_pressed, &red_button_released);
  red_button_pressed.body.main_color = LV_COLOR_MAROON;
  red_button_pressed.body.grad_color = LV_COLOR_MAROON;

  //Blue Rel style
  lv_style_copy(&blue_button_released, &default_button_released);
  blue_button_released.body.main_color = LV_COLOR_BLUE;
  blue_button_released.body.grad_color = LV_COLOR_BLUE;
  blue_button_released.text.color = LV_COLOR_MAKE(255, 255, 255);

  //Blue pressed style
  lv_style_copy(&blue_button_pressed, &blue_button_released);
  blue_button_pressed.body.main_color = LV_COLOR_NAVY;
  blue_button_pressed.body.grad_color = LV_COLOR_NAVY;

  //Green Rel style
  lv_style_copy(&green_button_released, &default_button_released);
  green_button_released.body.radius = 8;
  green_button_released.body.main_color = LV_COLOR_GREEN;
  green_button_released.body.grad_color = LV_COLOR_GREEN;
  green_button_released.text.color = LV_COLOR_MAKE(255, 255, 255);

  //Green Pressed style
  lv_style_copy(&green_button_pressed, &green_button_released);
  green_button_pressed.body.main_color = LV_COLOR_HEX(0x10690C);
  green_button_pressed.body.grad_color = LV_COLOR_HEX(0x10690C);

  lv_style_copy(&red_text, &lv_style_plain);
  red_text.text.color = LV_COLOR_RED;
  red_text.line.color = LV_COLOR_RED;
  red_text.line.width = 3;
  lv_style_copy(&blue_text, &lv_style_plain);
  blue_text.text.color = LV_COLOR_BLUE;
  blue_text.line.color = LV_COLOR_BLUE;
  blue_text.line.width = 3;
  lv_style_copy(&green_text, &lv_style_plain);
  green_text.text.color = LV_COLOR_GREEN;
  green_text.line.color = LV_COLOR_GREEN;
  green_text.line.width = 3;
  lv_style_copy(&black_text, &lv_style_plain);
  black_text.text.color = LV_COLOR_BLACK;
  black_text.line.color = LV_COLOR_BLACK;
  black_text.line.width = 3;
  lv_style_copy(&white_text, &lv_style_plain);
  white_text.text.color = LV_COLOR_WHITE;
  white_text.line.color = LV_COLOR_WHITE;
  white_text.line.width = 3;

  lv_style_copy(&default_background, &lv_style_plain);
  default_background.body.main_color = LV_COLOR_MAKE(0, 0, 0);
  default_background.body.grad_color = LV_COLOR_MAKE(0, 0, 0);

  lv_style_copy(&popup_background, &lv_style_plain);
  popup_background.body.main_color = LV_COLOR_MAKE(126, 126, 126);
  popup_background.body.grad_color = LV_COLOR_MAKE(126, 126, 126);
  popup_background.body.radius = 8;
  popup_background.body.border.color = LV_COLOR_MAROON;
  popup_background.body.border.width = 2;


  lv_style_copy(&default_meter, &lv_style_pretty_color);
  default_meter.line.width = 2;
  default_meter.line.color = LV_COLOR_WHITE;
  default_meter.body.padding.hor = 16;            /*Line length*/
  default_meter.body.main_color = LV_COLOR_LIME;
  default_meter.body.grad_color = LV_COLOR_RED;

  /* Toggle Styles*/
  lv_style_copy(&switch_background, &lv_style_pretty);
  switch_background.body.radius = LV_RADIUS_CIRCLE;
  switch_background.body.padding.hor = 5;
  switch_background.body.padding.ver = 5;

  lv_style_copy(&switch_inactive, &lv_style_pretty_color);
  switch_inactive.body.radius = LV_RADIUS_CIRCLE;
  switch_inactive.body.main_color = LV_COLOR_HEX(0x9fc8ef);
  switch_inactive.body.grad_color = LV_COLOR_HEX(0x9fc8ef);
  switch_inactive.body.padding.hor = 0;
  switch_inactive.body.padding.ver = 0;

  lv_style_copy(&switch_off, &lv_style_pretty);
  switch_off.body.radius = LV_RADIUS_CIRCLE;
  switch_off.body.shadow.width = 4;
  switch_off.body.shadow.type = LV_SHADOW_BOTTOM;

  lv_style_copy(&switch_on, &lv_style_pretty_color);
  switch_on.body.radius = LV_RADIUS_CIRCLE;
  switch_on.body.shadow.width = 4;
  switch_on.body.shadow.type = LV_SHADOW_BOTTOM;
}
