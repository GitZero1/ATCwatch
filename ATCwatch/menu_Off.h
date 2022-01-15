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


class OffScreen : public Screen
{
  public:
    virtual void pre()
    {
      static const char * btns[] = {"Yes", "No", ""};
      lv_obj_t * msgbox1 = lv_msgbox_create(lv_scr_act(), NULL);
      lv_msgbox_set_text(msgbox1, "Power Off?");
      lv_msgbox_add_btns(msgbox1, btns);
      lv_obj_set_width(msgbox1, 200);
      lv_obj_set_event_cb(msgbox1, event_handler);
      lv_obj_align(msgbox1, NULL, LV_ALIGN_CENTER, 0, 0);
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

    private:

    static void event_handler(lv_obj_t * obj, lv_event_t event)
    {
      if (event == LV_EVENT_VALUE_CHANGED) {
        if ("Yes" == lv_msgbox_get_active_btn_text(obj))
          system_off();
        else if ("No" == lv_msgbox_get_active_btn_text(obj))
          set_last_menu();
      }
    }
};

OffScreen offScreen;
