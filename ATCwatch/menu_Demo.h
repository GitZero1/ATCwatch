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
     // create_btns();
      
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
           //do this
         }
         
       }
    }

  private:
  lv_obj_t  *label, *test_btn;
  
};

DemoScreen demoScreen;
