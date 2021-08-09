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

class TorchScreen : public Screen 
//TODO disable sleep in this app and change icon to torch or no icon, also maybe automagically increase brightness?

{
  public:
    virtual void pre()
    {
      white_screen();
      set_gray_screen_style(&sans_regular);
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

    virtual void black_screen(){
      set_main_color(2);
      set_grad_color(2);
    }

    virtual void main()
    {
      
    }

    virtual void long_click()
    {
      black_screen();
      display_home();
    }

    virtual void left()
    {
      black_screen();
      display_home();
    }

    virtual void right()
    {
      black_screen();
      display_home();
    }

    virtual void up()
    {
      black_screen();
      display_home();
    }
    virtual void down()
    {
      black_screen();
      display_home();
    }

    virtual void click(touch_data_struct touch_data)
    {
      black_screen();
      display_home();
    }

};

TorchScreen torchScreen;
