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
      
      time_data = get_time();
      demo_img = lv_img_create(lv_scr_act(),nullptr);
      lv_img_set_src(demo_img, &ItestImg);
      lv_img_set_pivot(demo_img, 9, 120);
      //lv_img_set_zoom(demo_img,1024);
      lv_obj_align(demo_img, nullptr, LV_ALIGN_CENTER, 0, -111);
    }


    virtual void main()
    {
      time_data = get_time();
      lv_img_set_angle(demo_img, time_data.sec*6*10);
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

    private:
    lv_obj_t *demo_img;
    time_data_struct time_data;

};

DemoScreen demoScreen;
