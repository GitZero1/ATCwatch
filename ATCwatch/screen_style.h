/*
 * Copyright (c) 2020 Aaron Christophel
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#pragma once

#include "Arduino.h"
#include <lvgl.h>

lv_color_t color_list[] = {
  LV_COLOR_WHITE,
  LV_COLOR_MAKE(0xFF, 0x57, 0x33),
  LV_COLOR_BLACK,
  LV_COLOR_RED,
  LV_COLOR_BLUE,
  LV_COLOR_GREEN,
  LV_COLOR_MAKE(0x39, 0xFF, 0x14), //neon green?
  LV_COLOR_MAKE(0xFF,0x66,0xCC), //Rose Pink
  LV_COLOR_MAKE(0x00, 0x8E, 0xFF)}; //sky blue

/*
0 = white
1 = gray
2 = black
3 = red
4 = blue
5 = green
6 = Neon green
7 = Rose Pink
8 = Sky Blue
*/

int main_color_save = 2;
int grad_color_save = 2;
int font_color_save = 0;
int btn_bg_color_save = 2; 
int btn_outline_color_save = 0;


void set_gray_screen_style() {
  static lv_style_t style_screen;
  lv_style_copy(&style_screen, &lv_style_plain);
  style_screen.body.main_color = color_list[main_color_save];
  style_screen.body.grad_color = color_list[main_color_save];
  style_screen.text.color = color_list[btn_outline_color_save];
  lv_obj_set_style(lv_scr_act(), &style_screen);
}

void set_btn_style(lv_obj_t *obj){
  //Create btn style
  static lv_style_t style_btn;
  lv_style_copy(&style_btn, &lv_style_plain);
  style_btn.body.main_color = color_list[btn_bg_color_save];
  style_btn.body.grad_color = color_list[btn_bg_color_save];
  style_btn.body.border.width = 4;
  style_btn.body.border.color = color_list[btn_outline_color_save];
  style_btn.text.color = color_list[btn_outline_color_save];
  style_btn.body.radius = 10;
  //style_btn.text.font = font;
  //Create btn_pressed style
  static lv_style_t style_btn_sel;
  lv_style_copy(&style_btn_sel, &lv_style_plain);
  style_btn_sel.body.main_color = color_list[btn_outline_color_save];
  style_btn_sel.body.grad_color = color_list[btn_outline_color_save];
  style_btn_sel.body.border.width = 4;
  style_btn_sel.body.border.color = color_list[btn_bg_color_save];
  style_btn_sel.text.color = color_list[btn_bg_color_save];
  style_btn_sel.body.radius = 10;
  //style_btn_sel.text.font = font;
  // Set Styles to obj
  //lv_obj_set_style(obj, &style_btn);
  lv_btn_set_style(obj, LV_BTN_STYLE_PR, &style_btn_sel);
  lv_btn_set_style(obj, LV_BTN_STYLE_REL, &style_btn);
}

void set_custom_style(lv_obj_t *obj){
  //Create custom style
  static lv_style_t style_custom;
  lv_style_copy(&style_custom, &lv_style_plain);
  style_custom.body.main_color = color_list[btn_bg_color_save];
  style_custom.body.grad_color = color_list[btn_bg_color_save];
  style_custom.body.border.width = 4;
  style_custom.body.border.color = color_list[btn_outline_color_save];
  style_custom.text.color = color_list[btn_outline_color_save];
  style_custom.body.radius = 10;
  lv_obj_set_style(obj, &style_custom);
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
  btn_outline_color_save = new_color;
}

void set_btn_bg_color(int new_color){
  btn_bg_color_save = new_color;
}

int get_main_btn_color(){
  return btn_outline_color_save;
}

int get_bg_btn_color(){
  return btn_bg_color_save;
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
