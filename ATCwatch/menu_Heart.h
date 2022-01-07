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
#include "inputoutput.h"
#include "heartrate.h"


class HeartScreen : public Screen
{
  public:
    virtual void pre()
    {
      start_hrs3300();

      label = lv_label_create(lv_scr_act(), NULL);
      lv_label_set_text(label, "Heartrate");
      lv_obj_align(label, NULL, LV_ALIGN_CENTER, 0, -30);

      set_gray_screen_style();
      
      label_hr = lv_label_create(lv_scr_act(), NULL);
      lv_label_set_text(label_hr, "HR:");
      lv_obj_align(label_hr, NULL, LV_ALIGN_CENTER, 0, 0);

      label_hr_last = lv_label_create(lv_scr_act(), NULL);
      lv_label_set_text(label_hr_last, "Last HR:");
      lv_obj_align(label_hr_last, NULL, LV_ALIGN_CENTER, 0, 30);

    }

    virtual void main()
    {
      byte hr = get_heartrate();
      switch (hr) {
        case 0:
        case 255:
          break;
        case 254:
          lv_label_set_text_fmt(label_hr, "HR: No Touch");
          break;
        case 253:
          lv_label_set_text_fmt(label_hr, "HR: Please Wait");
          break;
        default:
          lv_label_set_text_fmt(label_hr, "HR: %i", hr);
          break;
      }
      lv_label_set_text_fmt(label_hr_last, "Last HR: %i", get_last_heartrate());
      lv_obj_realign(label_hr);
      lv_obj_realign(label_hr_last);
    }

    virtual void post()
    {
      end_hrs3300();
    }

    virtual uint32_t sleepTime()
    {
      return 50000;
    }

    virtual void right()
    {
      set_last_menu();
    }

  private:
    lv_obj_t *label, *label_hr, *label_hr_last;

};

HeartScreen heartScreen;
