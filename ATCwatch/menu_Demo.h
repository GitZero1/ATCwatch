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
    //FONT AND STYLE FOR ROLLER
    lv_style_copy( &st, &lv_style_plain );
    //st.text.color = lv_color_hsv_to_rgb(10, 5, 95);
    st.text.font = &lv_font_roboto_28;
    
    
    set_swipe_enabled(true);
    lv_obj_t *roller1 = lv_roller_create(lv_scr_act(), NULL);
    lv_obj_set_style( roller1, &st );
    lv_roller_set_options(roller1,
                        "January\n"
                        "February\n"
                        "March\n"
                        "April\n"
                        "May\n"
                        "June\n"
                        "July\n"
                        "August\n"
                        "September\n"
                        "October\n"
                        "November\n"
                        "December",
                        LV_ROLLER_MODE_NORMAL);

    lv_roller_set_visible_row_count(roller1, 3);
    lv_obj_align(roller1, NULL, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_event_cb(roller1, event_handler);
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

    static void event_handler(lv_obj_t * obj, lv_event_t event)
    {
    if(event == LV_EVENT_VALUE_CHANGED) {
        char buf[32];
        lv_roller_get_selected_str(obj, buf, sizeof(buf));
       // printf("Selected month: %s\n", buf);
      }
    }

  private: 
  lv_style_t st;
};

DemoScreen demoScreen;
