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
      
      time_data = get_time();
      demo_img = lv_img_create(lv_scr_act(),nullptr);
      lv_img_set_src(demo_img, &ItestImg2);
      lv_img_set_pivot(demo_img, 32, 118);
      lv_obj_align(demo_img, nullptr, LV_ALIGN_CENTER, 0, -90);
      
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
