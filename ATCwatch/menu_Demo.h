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
      set_swipe_enabled(true);
          //BUTTON 
      btn1 = lv_btn_create(lv_scr_act(), NULL);
      lv_obj_set_event_cb(btn1, lv_event_handler);
      lv_obj_align(btn1, NULL, LV_ALIGN_CENTER, 0, 0);
      lv_btn_set_fit2(btn1, LV_FIT_NONE, LV_FIT_TIGHT);
      label = lv_label_create(btn1, NULL);
      lv_label_set_text(label, "Test");
      

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
      if (object == btn1 && event == LV_EVENT_SHORT_CLICKED) {
        ble_write("AT+BEEP");
      } 
    }

  private:
  time_data_struct time_data;
  lv_style_t st;
  lv_obj_t  *label, *btn1;
  
};

DemoScreen demoScreen;
