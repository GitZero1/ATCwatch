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


class RebootScreen : public Screen
{
  public:
    virtual void pre()
    {
      /*
      cont = lv_cont_create(lv_scr_act(),nullptr);
      //lv_cont_set_style(cont,LV_CONT_STYLE_MAIN,&st);
      lv_obj_set_style_local_radius(cont,LV_OBJ_PART_MAIN,LV_STATE_DEFAULT,360);
      lv_obj_set_height(cont,240);
      lv_obj_set_width(cont,240);
      lv_obj_align(cont,nullptr,LV_ALIGN_CENTER,0,0);
      */
      


     left_btn = lv_btn_create(lv_scr_act(), nullptr);
     label = lv_label_create(left_btn, nullptr);
     lv_label_set_text(label,"Nvm");
     lv_obj_align(left_btn, nullptr, LV_ALIGN_CENTER, -50,0);
     lv_obj_set_event_cb(left_btn, lv_event_handler); //set event handler
     
     right_btn = lv_btn_create(lv_scr_act(), nullptr);
     label = lv_label_create(right_btn, nullptr);
     lv_label_set_text(label,"Yes");
     lv_obj_align(right_btn, nullptr, LV_ALIGN_CENTER, 50,0);
     lv_obj_set_event_cb(right_btn, lv_event_handler); //set event handler
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

    virtual void lv_event_class(lv_obj_t * object, lv_event_t event)
    {
       if (event == LV_EVENT_SHORT_CLICKED) {
         if(object == left_btn){
           set_last_menu();
         } else if (object == right_btn){
           set_reboot();
         }
       }
    }

  private:
  lv_obj_t  *label, *left_btn, *right_btn;
};

RebootScreen rebootScreen;
