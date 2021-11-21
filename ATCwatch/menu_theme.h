/*
 * Copyright (c) 2020 Aaron Christophel
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#pragma once
#include "Arduino.h"
#include "class.h"
#include "images.h"
#include "menu.h"
#include "display.h"
#include "ble.h"
#include "time.h"
#include "battery.h"
#include "accl.h"
#include "push.h"
#include "heartrate.h"
#include "screen_style.h"
#include <lvgl.h>
 /*    
    0 = white
    1 = gray
    2 = black
    3 = red
    4 = green
    5 = blue
    6 = green?  
    */
class ThemeScreen : public Screen
{
  public:
    virtual void pre()
    {
      create_btns();
      
    }

    void create_btns(){
      screen_color_save = get_main_color();
      tscreen_color_save = screen_color_save;
      main_color_save = get_main_btn_color();
      tmain_color_save = main_color_save;
      bg_color_save = get_bg_btn_color();
      tbg_color_save = bg_color_save;

      //create style for button labels
      static lv_style_t label_style;
      lv_style_copy(&label_style, &lv_style_plain);
      label_style.text.font = &lv_font_roboto_28;
      

      //sample button
      sample_btn = lv_btn_create(lv_scr_act(), nullptr); //create button
      lv_obj_set_height(sample_btn,45); //set button height
      //lv_btn_set_fit2(sample_btn,LV_FIT_TIGHT, LV_FIT_NONE); //set button width
      lv_obj_align(sample_btn, lv_scr_act(), LV_ALIGN_IN_TOP_MID, 0, 10); //set button location
      label = lv_label_create(sample_btn, nullptr); //create button label
      lv_label_set_text(label,"Sample"); //set button label text
      set_custom_style(sample_btn); //set button style
      lv_obj_set_event_cb(sample_btn, lv_event_handler); //set event handler

      //Main Color Row
      //left btn
      main_color_left_btn = lv_btn_create(lv_scr_act(), NULL);
      lv_obj_set_event_cb(main_color_left_btn, lv_event_handler);
      lv_obj_align(main_color_left_btn, NULL, LV_ALIGN_CENTER, -55, -25);
      set_btn_style(main_color_left_btn);
      label = lv_label_create(main_color_left_btn, NULL);
      lv_label_set_text(label, "<");
      lv_obj_set_style(label, &label_style);
      lv_btn_set_fit2(main_color_left_btn,LV_FIT_NONE,LV_FIT_TIGHT);
      //right btn
      main_color_right_btn = lv_btn_create(lv_scr_act(), NULL);
      lv_obj_set_event_cb(main_color_right_btn, lv_event_handler);
      lv_obj_align(main_color_right_btn, NULL, LV_ALIGN_CENTER, 50, -25);
      set_btn_style(main_color_right_btn);
      label = lv_label_create(main_color_right_btn, NULL);
      lv_label_set_text(label, ">");
      lv_obj_set_style(label, &label_style);
      lv_btn_set_fit2(main_color_right_btn,LV_FIT_NONE,LV_FIT_TIGHT);
      //main color label
      mcolor_label = lv_label_create(lv_scr_act(), nullptr);
      lv_label_set_text(mcolor_label, "Main Color");
      lv_obj_align(mcolor_label,main_color_left_btn, LV_ALIGN_OUT_TOP_MID, 0, 0);
      
      //Alt Color Row
      //left btn
      alt_color_left_btn = lv_btn_create(lv_scr_act(), NULL);
      lv_obj_set_event_cb(alt_color_left_btn, lv_event_handler);
      lv_obj_align(alt_color_left_btn, NULL, LV_ALIGN_CENTER, -55, 35);
      set_btn_style(alt_color_left_btn);
      label = lv_label_create(alt_color_left_btn, NULL);
      lv_label_set_text(label, "<");
      lv_obj_set_style(label, &label_style);
      lv_btn_set_fit2(alt_color_left_btn,LV_FIT_NONE,LV_FIT_TIGHT);
      //right btn
      alt_color_right_btn = lv_btn_create(lv_scr_act(), NULL);
      lv_obj_set_event_cb(alt_color_right_btn, lv_event_handler);
      lv_obj_align(alt_color_right_btn, NULL, LV_ALIGN_CENTER, 50, 35);
      set_btn_style(alt_color_right_btn);
      label = lv_label_create(alt_color_right_btn, NULL);
      lv_label_set_text(label, ">");
      lv_obj_set_style(label, &label_style);
      lv_btn_set_fit2(alt_color_right_btn,LV_FIT_NONE,LV_FIT_TIGHT);
      //alt color label
      alt_color_label = lv_label_create(lv_scr_act(), nullptr);
      lv_label_set_text(alt_color_label, "Alt Color");
      lv_obj_align(alt_color_label,alt_color_left_btn, LV_ALIGN_OUT_TOP_MID, 0, 0);

      //background Color Row
      //left btn
      background_color_left_btn = lv_btn_create(lv_scr_act(), NULL);
      lv_obj_set_event_cb(background_color_left_btn, lv_event_handler);
      lv_obj_align(background_color_left_btn, NULL, LV_ALIGN_CENTER, -55, 95);
      label = lv_label_create(background_color_left_btn, NULL);
      lv_label_set_text(label, "<");
      lv_obj_set_style(label, &label_style);
      set_btn_style(background_color_left_btn);
      lv_btn_set_fit2(background_color_left_btn,LV_FIT_NONE,LV_FIT_TIGHT);
      //right btn
      background_color_right_btn = lv_btn_create(lv_scr_act(), NULL);
      lv_obj_set_event_cb(background_color_right_btn, lv_event_handler);
      lv_obj_align(background_color_right_btn, NULL, LV_ALIGN_CENTER, 50, 95);
      set_btn_style(background_color_right_btn);
      label = lv_label_create(background_color_right_btn, NULL);
      lv_label_set_text(label, ">");
      lv_obj_set_style(label, &label_style);
      lv_btn_set_fit2(background_color_right_btn,LV_FIT_NONE,LV_FIT_TIGHT);
      //alt color label
      background_color_label = lv_label_create(lv_scr_act(), nullptr);
      lv_label_set_text(background_color_label, "Screen Color");
      lv_obj_align(background_color_label,background_color_left_btn, LV_ALIGN_OUT_TOP_MID, 0, 0);
      


    }

    


    virtual void main()
    {
    }

    virtual void up()
    {
    }

    virtual void down()
    {
    }

    virtual void right()
    {
    }

    virtual void lv_event_class(lv_obj_t * object, lv_event_t event)
    {
       if (event == LV_EVENT_SHORT_CLICKED) {
         if(object == main_color_left_btn)
         {
           if(tmain_color_save >= 1){
            tmain_color_save = tmain_color_save -1;
            set_btn_main_color(tmain_color_save);
            set_custom_style(sample_btn);
           } else {set_motor_ms();}
         }
         else if(object == main_color_right_btn){
           if(tmain_color_save <= 5){
            tmain_color_save = tmain_color_save +1;
            set_btn_main_color(tmain_color_save);
            set_custom_style(sample_btn);
           } else {set_motor_ms();}
         }
         else if (object == alt_color_right_btn)
         {
           if(tbg_color_save <= 5)
           {
             tbg_color_save = tbg_color_save +1;
             set_btn_bg_color(tbg_color_save);
             set_custom_style(sample_btn);
             }
             else {set_motor_ms();}
         }
         else if (object == alt_color_left_btn)
         {
           if(tbg_color_save >= 1)
           {
              tbg_color_save = tbg_color_save -1;
              set_btn_bg_color(tbg_color_save);
              set_custom_style(sample_btn);
           }
           else {set_motor_ms();}
         }
         else if (object == background_color_left_btn)
         {
           if(tscreen_color_save >= 1)
           {
              tscreen_color_save = tscreen_color_save -1;
              set_main_color(tscreen_color_save);
              set_gray_screen_style();
           }
           else {set_motor_ms();}
         }
         else if (object == background_color_right_btn)
         {
           if(tscreen_color_save <= 5)
           {
              tscreen_color_save = tscreen_color_save +1;
              set_main_color(tscreen_color_save);
              set_gray_screen_style();
           }
           else {set_motor_ms();}
         }
         
       }
    }

  private:
  lv_obj_t  *label, *sample_btn,
           *main_color_left_btn, *main_color_right_btn, *mcolor_label,
           *alt_color_right_btn, *alt_color_left_btn, *alt_color_label,
           *background_color_left_btn, *background_color_right_btn, *background_color_label;
  int main_color_save, bg_color_save, tmain_color_save, tbg_color_save, screen_color_save, tscreen_color_save;
  
};

ThemeScreen themeScreen;
