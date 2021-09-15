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
      set_swipe_enabled(true);
      createStyle();

      label = lv_label_create(lv_scr_act(), NULL);
      lv_label_set_text(label, "DEMO SCREEN");
      lv_obj_align(label, NULL, LV_ALIGN_IN_BOTTOM_LEFT, 0, 0);

      btn1 = lv_btn_create(lv_scr_act(),nullptr);
      lv_obj_align(btn1, nullptr, LV_ALIGN_IN_BOTTOM_RIGHT, 0 , 0);
      label = lv_label_create(btn1, nullptr);
      lv_label_set_text(label,"FF");


      tContainer();

    }


    virtual void main(){

    }

    virtual void createStyle(){
      lv_style_copy( &st, &lv_style_plain );
      st.text.color = LV_COLOR_MAKE(0xFF, 0xFF, 0xFF);
      st.body.main_color = lv_color_make(0x00, 0x00, 0x00);
      st.body.grad_color = lv_color_make(0x00, 0x00, 0x00);
      //st1.text.color = lv_color_hsv_to_rgb(0, 0, 0);
      //st.text.font = &lv_font_roboto_28;
    }

    //test container
    virtual void tContainer(){
      lv_obj_t * cont;

      cont = lv_cont_create(lv_scr_act(), NULL);
      lv_obj_align(cont, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 0);
      lv_obj_set_size(cont, LV_HOR_RES, 35);
      lv_cont_set_layout(cont, LV_LAYOUT_COL_M);
      lv_obj_set_style(cont, &st);

      label = lv_label_create(cont, NULL);
      lv_label_set_text(label, "Short text");
  

      //Refresh and pause here for a while to see how `fit` works
      uint32_t t;
      lv_refr_now(NULL);
      t = lv_tick_get();
      while(lv_tick_elaps(t) < 2000);
      lv_label_set_text(label, "It is a long text");

      //Wait here too
      lv_refr_now(NULL);
      t = lv_tick_get();
      while(lv_tick_elaps(t) < 1000);
      lv_label_set_text(label, "Here is an even longer text");
      

    }







    // event handler
    virtual void lv_event_class(lv_obj_t * object, lv_event_t event)
    {

      if(event == LV_EVENT_SHORT_CLICKED){
       if(object == btn1){
          ble_write("AT+BEEP");
       }

      }
    }

    /*    
    0 = white
    1 = gray
    2 = black
    3 = red
    4 = green
    5 = blue
    6 = green?  
    */


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
  time_data_struct time_data;
  lv_style_t st;
  lv_obj_t  *label, *btn1;
  
};

DemoScreen demoScreen;
