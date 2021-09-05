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

class TorchScreen : public Screen 
//TODO disable sleep in this app and change icon to torch or no icon, also maybe automagically increase brightness?

{
  public:
  
    virtual void pre()
    {
      mainColor = get_main_color();
      gradColor = get_grad_color();
      backlight_brightness = get_backlight();
      set_backlight(7);
      white_screen();
      set_gray_screen_style(&lv_font_roboto_16);
    }
    /*colors are
    0 milk
    1 gray
    2 black
    3 red
    4 green
    5 blue
    */
    virtual void white_screen(){
      set_main_color(0);
      set_grad_color(0);
    }

    void reset_theme(){
      set_main_color(mainColor);
      set_grad_color(gradColor);
      set_backlight(backlight_brightness);
    }

    virtual void main()
    {
      
    }

    virtual uint32_t sleepTime()
    {
      return 3000000;
    }

    virtual void long_click()
    {
      reset_theme();
      display_home();
    }

    virtual void left()
    {
      reset_theme();
      display_home();
    }

    virtual void right()
    {
      reset_theme();
      display_home();
    }

    virtual void up()
    {
      reset_theme();
      display_home();
    }
    virtual void down()
    {
      reset_theme();
      display_home();
    }

    virtual void click(touch_data_struct touch_data)
    {
      reset_theme();
      display_home();
    }

  private:
    int mainColor;
    int gradColor;
    int backlight_brightness;

};

TorchScreen torchScreen;
