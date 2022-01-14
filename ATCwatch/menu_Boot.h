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
#include "fonts.h"


/*
#define LV_FONT_ROBOTO_12    1
#define LV_FONT_ROBOTO_16    1
#define LV_FONT_ROBOTO_22    1
#define LV_FONT_ROBOTO_28    1
 */

class BootScreen : public Screen
{
  public:
    virtual void pre()
    {
      lv_obj_t *label = lv_label_create(lv_scr_act(), NULL);
      lv_label_set_text(label, "Booting\n01OS");
      lv_obj_set_style_local_text_font(label,LV_OBJ_PART_MAIN,LV_STATE_DEFAULT,&dsDigiBold_72);
      lv_label_set_align(label, LV_LABEL_ALIGN_CENTER);
      lv_obj_align(label, NULL, LV_ALIGN_CENTER, 0, 0);
      
    }

    virtual void main()
    {

    }

  private:
};

BootScreen bootScreen;
