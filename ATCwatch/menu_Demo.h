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
      set_swipe_enabled(true);

    }


    virtual void main(){

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
  time_data_struct time_data;
  lv_style_t st;
  lv_obj_t  *label, *btn1;
  
};

DemoScreen demoScreen;
