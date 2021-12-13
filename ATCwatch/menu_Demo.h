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
      lv_style_copy(&st, &lv_style_plain);
      st.body.radius = 180;
      st.body.border.width = 1;
      st.body.border.color = LV_COLOR_WHITE;

      cont = lv_cont_create(lv_scr_act(),nullptr);
      //lv_cont_set_style(cont,LV_CONT_STYLE_MAIN,&st);
      lv_obj_set_style(cont, &st);
      lv_obj_set_height(cont,240);
      lv_obj_set_width(cont,240);
      lv_obj_align(cont,nullptr,LV_ALIGN_CENTER,0,0);


     test_btn = lv_btn_create(lv_scr_act(), nullptr);
     label = lv_label_create(test_btn, nullptr);
     lv_label_set_text(label,"screen1");
     lv_obj_align(test_btn, cont, LV_ALIGN_CENTER, 0,-50);
     lv_obj_set_event_cb(test_btn, lv_event_handler); //set event handler
     
     test_btn2 = lv_btn_create(lv_scr_act(), nullptr);
     label = lv_label_create(test_btn2, nullptr);
     lv_label_set_text(label,"screen2");
     lv_obj_align(test_btn2, cont, LV_ALIGN_CENTER, 0,50);
     lv_obj_set_event_cb(test_btn2, lv_event_handler); //set event handler
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
         if(object == test_btn){
           set_motor_ms();
           //lv_label_set_text(label, "pressed");
           set_watchface(1);
         } else if (object == test_btn2){
           set_watchface(2);
         }
         
       }
    }

  private:
  lv_obj_t  *label, *test_btn, *test_btn2, *cont;
  lv_style_t st;
};

DemoScreen demoScreen;
