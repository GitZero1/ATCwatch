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
#include "fonts.h"


class NotifyScreen : public Screen
{
  public:
    virtual void pre()
    {
      set_gray_screen_style(&lv_font_roboto_16);

      //FONT AND STYLE FOR BAR
      static lv_style_t stBar;
      lv_style_copy( &stBar, &lv_style_plain );
      stBar.text.color = LV_COLOR_MAKE(0x00, 0xFF, 0x00);
      stBar.body.main_color = lv_color_make(0x00, 0x00, 0x00);
      stBar.body.grad_color = lv_color_make(0x00, 0x00, 0x00);
      stBar.body.border.color = lv_color_make(0x00, 0xFF, 0x00);
      stBar.body.border.width = 2;

      titleCont = lv_cont_create(lv_scr_act(),NULL);
      lv_obj_align(titleCont, nullptr, LV_ALIGN_IN_TOP_LEFT, 0, 0); 
      lv_obj_set_size(titleCont, LV_HOR_RES, 50);
      //lv_cont_set_layout(cont, LV_LAYOUT_COL_M);
      lv_obj_set_style(titleCont, &stBar);

      lv_obj_set_style(lv_scr_act(), &stBar);


      label_msg_name = lv_label_create(titleCont, NULL);
      //lv_label_set_long_mode(label_msg_name, LV_LABEL_LONG_BREAK);
      lv_obj_set_width(label_msg_name,240);
      lv_label_set_text(label_msg_name, "");
      lv_label_set_text(label_msg_name, string2char(get_name_msg()));
      lv_obj_align(label_msg_name, NULL, LV_ALIGN_IN_TOP_LEFT, 5, 0);

      label_msg_title = lv_label_create(titleCont, NULL);
      //lv_label_set_long_mode(label_msg_title, LV_LABEL_LONG_BREAK);
      lv_obj_set_width(label_msg_title,240);
      lv_label_set_text(label_msg_title, "");
      lv_label_set_text(label_msg_title, string2char(get_titl_msg()));
      lv_obj_align(label_msg_title, NULL, LV_ALIGN_IN_TOP_LEFT, 5, 25);

      label_msg_body = lv_label_create(lv_scr_act(), NULL);
      lv_label_set_long_mode(label_msg_body, LV_LABEL_LONG_BREAK);
      lv_obj_set_width(label_msg_body,240);
      lv_label_set_text(label_msg_body, "");
      lv_label_set_text(label_msg_body, string2char(get_body_msg()));
      lv_obj_align(label_msg_body, NULL, LV_ALIGN_IN_TOP_LEFT, 5, 55);


    }

    virtual void main()
    {
      lv_label_set_text(label_msg_name, string2char(get_name_msg()));
      lv_label_set_text(label_msg_title, string2char(get_titl_msg()));
      lv_label_set_text(label_msg_body, string2char(get_body_msg()));
    }

    virtual void long_click()
    {
      display_home();
    }

    virtual void left()
    {
      display_home();
    }

    virtual void right()
    {
      display_home();
    }

    virtual void up()
    {
      display_home();
    }
    virtual void down()
    {
      display_home();
    }

    virtual void click(touch_data_struct touch_data)
    {
      display_home();
    }

  private:
    lv_obj_t *label, *label_msg_body, *label_msg_name, *label_msg_title, *label_msg, 
    *titleCont;
  

    char* string2char(String command) {
      if (command.length() != 0) {
        char *p = const_cast<char*>(command.c_str());
        return p;
      }
    }
};

NotifyScreen notifyScreen;
