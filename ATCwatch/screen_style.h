/*
 * Copyright (c) 2020 Aaron Christophel
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#pragma once

#include "Arduino.h"
#include <lvgl.h>

lv_color_t color_list[] = {LV_COLOR_MAKE(0xFF, 0xFF, 0xFF), LV_COLOR_GRAY, LV_COLOR_BLACK, LV_COLOR_RED, LV_COLOR_MAKE(0x39,0xFF,0x14), LV_COLOR_BLUE, LV_COLOR_MAKE(0x00, 0x8E, 0xFF)};

/*
0 = white
1 = gray
2 = black
3 = red
4 = green for battery
5 = blue
6 = snoopyblue?
*/

int main_color_save = 6;
int grad_color_save = 6;
int font_color_save = 2;
int btn_bg_color_save = 0; //white
int btn_main_color_save = 2; //black


void set_gray_screen_style( lv_font_t * font = LV_FONT_DEFAULT) {
  static lv_style_t style_screen;
  lv_style_copy(&style_screen, &lv_style_plain);
  style_screen.body.main_color = color_list[main_color_save];// LV_COLOR_GREEN;
  style_screen.body.grad_color = color_list[grad_color_save];//LV_COLOR_BLUE;
  style_screen.text.color = color_list[font_color_save];
  style_screen.text.font = font;
  lv_obj_set_style(lv_scr_act(), &style_screen);
}


void set_btn_style(lv_obj_t *obj, lv_font_t * font = LV_FONT_DEFAULT){
  //Create btn style
  static lv_style_t style_btn;
  lv_style_copy(&style_btn, &lv_style_plain);
  style_btn.body.main_color = color_list[btn_bg_color_save];
  style_btn.body.grad_color = color_list[btn_bg_color_save];
  style_btn.body.border.width = 4;
  style_btn.body.border.color = color_list[btn_main_color_save];
  style_btn.text.color = color_list[btn_main_color_save];
  style_btn.body.radius = 10;
  style_btn.text.font = font;
  //Create btn_pressed style
  static lv_style_t style_btn_sel;
  lv_style_copy(&style_btn_sel, &lv_style_plain);
  style_btn_sel.body.main_color = color_list[btn_main_color_save];
  style_btn_sel.body.grad_color = color_list[btn_main_color_save];
  style_btn_sel.body.border.width = 4;
  style_btn_sel.body.border.color = color_list[btn_bg_color_save];
  style_btn_sel.text.color = color_list[btn_bg_color_save];
  style_btn_sel.body.radius = 10;
  style_btn_sel.text.font = font;
  // Set Styles to obj
  //lv_obj_set_style(obj, &style_btn);
  lv_btn_set_style(obj, LV_BTN_STYLE_PR, &style_btn_sel);
  lv_btn_set_style(obj, LV_BTN_STYLE_REL, &style_btn);
}

void set_main_color(int new_color) {
  main_color_save = new_color;
}

void set_grad_color(int new_color) {
  grad_color_save = new_color;
}

void set_font_color(int new_color) {
  font_color_save = new_color;
}


void set_btn_main_color(int new_color){
  btn_main_color_save = new_color;
}

void set_btn_bg_color(int new_color){
  btn_bg_color_save = new_color;
}


int get_main_color() {
  return main_color_save;
}

int get_grad_color() {
  return grad_color_save;
}

int get_font_color() {
  return font_color_save;
}
