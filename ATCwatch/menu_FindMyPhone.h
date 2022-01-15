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
//#include "screen_style.h"
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
class FindMyScreen : public Screen
{
  public:
    virtual void pre()
    {

     find_phone_btn = lv_btn_create(lv_scr_act(), nullptr);
     label = lv_label_create(find_phone_btn, nullptr);
     lv_label_set_text(label,"Find Phone");
     lv_obj_align(find_phone_btn, nullptr, LV_ALIGN_CENTER, 0, 0);
     lv_obj_set_event_cb(find_phone_btn, lv_event_handler); //set event handler
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
         if(object == find_phone_btn){
           set_motor_ms();
           ble_write("AT+BEEP");
         }
         
       }
    }

  private:
  lv_obj_t  *label, *find_phone_btn;
};

FindMyScreen findMyScreen;