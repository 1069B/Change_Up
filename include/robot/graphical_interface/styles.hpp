#include "main.h"

#ifndef STYLES_H
#define STYLES_H

namespace GUI_STYLES{
  extern lv_style_t red_button_released;
  extern lv_style_t red_button_pressed;
  extern lv_style_t blue_button_released;
  extern lv_style_t blue_button_pressed;
  extern lv_style_t green_button_released;
  extern lv_style_t green_button_pressed;
  extern lv_style_t default_button_released;
  extern lv_style_t default_button_pressed;

  extern lv_style_t red_text;
  extern lv_style_t blue_text;
  extern lv_style_t green_text;
  extern lv_style_t black_text;
  extern lv_style_t white_text;

  extern lv_style_t default_background;
  extern lv_style_t popup_background;

  extern lv_style_t default_meter;

  extern lv_style_t switch_background;
  extern lv_style_t switch_inactive;
  extern lv_style_t switch_on;
  extern lv_style_t switch_off;

  extern lv_style_t roller_background;
  extern lv_style_t roller_selected;
}

void defineStyles(void);

#endif // STYLES_H
