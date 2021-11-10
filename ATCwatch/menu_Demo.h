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
class DemoScreen : public Screen
{
  public:
    virtual void pre()
    {
      //set_swipe_enabled(true);
          //BUTTON 
      create_btns();
      
      

    }


    void create_btns(){
      sample_btn = lv_btn_create(lv_scr_act(), NULL);
      lv_obj_set_event_cb(sample_btn, lv_event_handler);
      lv_obj_align(sample_btn, NULL, LV_ALIGN_IN_TOP_MID, 0, 0);
      set_btn_style(sample_btn, &lv_font_roboto_28);
      label = lv_label_create(sample_btn, NULL);
      lv_label_set_text(label, "Test");
      lv_btn_set_fit2(sample_btn,LV_FIT_NONE,LV_FIT_TIGHT);

      //left
      left_btn = lv_btn_create(lv_scr_act(), NULL);
      lv_obj_set_event_cb(left_btn, lv_event_handler);
      lv_obj_align(left_btn, NULL, LV_ALIGN_CENTER, -55, 0);
      set_btn_style(left_btn, &lv_font_roboto_28);
      label = lv_label_create(left_btn, NULL);
      lv_label_set_text(label, "<");
      lv_btn_set_fit2(left_btn,LV_FIT_NONE,LV_FIT_TIGHT);
      //right
      right_btn = lv_btn_create(lv_scr_act(), NULL);
      lv_obj_set_event_cb(right_btn, lv_event_handler);
      lv_obj_align(right_btn, NULL, LV_ALIGN_CENTER, 55, 0);
      set_btn_style(right_btn, &lv_font_roboto_28);
      label = lv_label_create(right_btn, NULL);
      lv_label_set_text(label, ">");
      lv_btn_set_fit2(right_btn,LV_FIT_NONE,LV_FIT_TIGHT);
      
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
      if (object == sample_btn && event == LV_EVENT_SHORT_CLICKED) {
        ble_write("AT+BEEP");
      } 
    }

  private:
  time_data_struct time_data;
  lv_style_t st;
  lv_obj_t  *label, *sample_btn, *left_btn, *right_btn;
  
};

DemoScreen demoScreen;
