/*
 * Copyright (c) 2020 Aaron Christophel
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#pragma once

#include "Arduino.h"
#include <lvgl.h>

lv_color_t color_list[] = {
  LV_COLOR_MAKE(0xFF, 0xFF, 0xFF),
  LV_COLOR_GRAY,
  LV_COLOR_BLACK,
  LV_COLOR_RED,
  LV_COLOR_MAKE(0x3F,0xD4,0x85), //00873E // (0x39,0xFF,0x14) bat green? 3FD485
  LV_COLOR_BLUE,
  LV_COLOR_GREEN,
  LV_COLOR_MAKE(0x00, 0x8E, 0xFF)};

/*
0 = white
1 = gray
2 = black
3 = red
4 = green for battery
5 = blue
6 = xmas green
*/

int main_color_save = 6;
int grad_color_save = 6;
int font_color_save = 2;
int btn_bg_color_save = 3; //red
int btn_main_color_save = 0; //white

int watchface = 1;


void set_gray_screen_style() {
  static lv_style_t style_screen;
  lv_style_init(&style_screen);
  lv_style_set_bg_color(&style_screen,LV_STATE_DEFAULT, color_list[main_color_save]);
  lv_style_set_text_color(&style_screen,LV_STATE_DEFAULT,color_list[font_color_save]);
  lv_obj_add_style(lv_scr_act(),LV_OBJ_PART_MAIN ,&style_screen);
}


void set_custom_style(lv_obj_t *obj){
  //Create custom style
  
  static lv_style_t style_custom;
  lv_style_init(&style_custom);
  lv_style_set_bg_color(&style_custom,LV_STATE_DEFAULT,color_list[main_color_save]);
  lv_style_set_border_width(&style_custom,LV_STATE_DEFAULT,2);
  lv_style_set_border_color(&style_custom,LV_STATE_DEFAULT,color_list[btn_main_color_save]);
  lv_style_set_text_color(&style_custom,LV_STATE_DEFAULT,color_list[btn_main_color_save]);
  //lv_style_set_radius(&style_custom,LV_STATE_DEFAULT,15);
  lv_obj_add_style(obj,LV_OBJ_PART_MAIN,&style_custom);
  
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

void set_watchface(int face){
  watchface = face;
}

int get_watchface(){
  return watchface;
}

int get_main_btn_color(){
  return btn_main_color_save;
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
