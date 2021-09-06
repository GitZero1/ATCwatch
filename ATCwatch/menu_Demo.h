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

class DemoScreen : public Screen
{
  public:
    virtual void pre()
    {
    //set_swipe_enabled(true);

    label = lv_label_create(lv_scr_act(), NULL);
    lv_label_set_text(label, "DEMO SCREEN");
    lv_obj_align(label, NULL, LV_ALIGN_CENTER, 0, 0);

    }


    virtual void main()
    {


    }

    virtual void lv_event_class(lv_obj_t * object, lv_event_t event)
    {

      if(event == LV_EVENT_SHORT_CLICKED){
       //do stuff

      }
    }

    /*    
    0 = white
    1 = gray
    2 = black
    3 = red
    4 = green
    5 = blue
    6 = green?  
    */


    virtual void up()
    {
    }

    virtual void down()
    {
    }

    virtual void right()
    {
    }

 

  private: 
  lv_style_t st;
  lv_obj_t  *label;
  
};

DemoScreen demoScreen;
