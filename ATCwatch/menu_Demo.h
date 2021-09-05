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
    String req;
    int sri;
    virtual void pre()
    {
    //set_swipe_enabled(true);
    initStyle();

   
    

    
    initPrimaryColorRow();
    lv_ex_win_1();
    
    }

    void initStyle(void)
    {
     //FONT AND STYLE FOR ROLLER
    lv_style_copy( &st, &lv_style_plain ); 
    st.text.color = lv_color_hsv_to_rgb(10, 5, 95);
    st.text.font = &lv_font_roboto_28;
    }


    virtual void main()
    {

    }


    void initPrimaryColorRow(void)
    {
      //BUTTON right
    pColorButtonR = lv_btn_create(lv_scr_act(), NULL);
    lv_obj_set_event_cb(pColorButtonR, lv_event_handler);
    lv_obj_align(pColorButtonR, NULL , LV_ALIGN_IN_TOP_RIGHT, 0, 0);
    lv_btn_set_fit2(pColorButtonR, LV_FIT_TIGHT, LV_FIT_TIGHT);
    pColorButtonR_label = lv_label_create(pColorButtonR, NULL);
    lv_label_set_text(pColorButtonR_label, ">");

    
      //BUTTON left
    pColorButtonL = lv_btn_create(lv_scr_act(), NULL);
    lv_obj_set_event_cb(pColorButtonL, lv_event_handler);
    lv_obj_align(pColorButtonL, NULL , LV_ALIGN_IN_TOP_LEFT, 0, 0);
    lv_btn_set_fit2(pColorButtonL, LV_FIT_TIGHT, LV_FIT_TIGHT);
    pColorButtonL_label = lv_label_create(pColorButtonL, NULL);
    lv_label_set_text(pColorButtonL_label, "<");



    //Roller
    roller1 = lv_roller_create(lv_scr_act(), NULL);
    lv_obj_set_style( roller1, &st );
    lv_roller_set_options(roller1,
                        "Milk\n"
                        "Gray\n"
                        "Black\n"
                        "Red\n"
                        "Green\n"
                        "Blue",
                        LV_ROLLER_MODE_NORMAL);

    lv_roller_set_visible_row_count(roller1, 1);
    lv_obj_align(roller1, NULL, LV_ALIGN_IN_TOP_MID, 0, 20);
    lv_obj_set_event_cb(roller1, event_handler);
    //lv_obj_set_height(roller1, 40);
    //lv_obj_set_width(th_roller, LV_HOR_RES);
    //lv_roller_set_align(roller1, LV_LABEL_ALIGN_LEFT);
    
    }
void lv_ex_win_1(void)
{
    /*Create a window*/
    lv_obj_t * win = lv_win_create(lv_scr_act(), NULL);
    lv_win_set_title(win, "Window title");                        /*Set the title*/


    /*Add control button to the header*/
    lv_obj_t * close_btn = lv_win_add_btn(win, LV_SYMBOL_CLOSE);           /*Add close button and use built-in close action*/
    lv_obj_set_event_cb(close_btn, lv_win_close_event_cb);
    lv_win_add_btn(win, LV_SYMBOL_SETTINGS);        /*Add a setup button*/

    /*Add some dummy content*/
    lv_obj_t * txt = lv_label_create(win, NULL);
    lv_label_set_text(txt, "This is the content of the window\n\n"
                           "You can add control buttons to\n"
                           "the window header\n\n"
                           "The content area becomes\n"
                           "automatically scrollable is it's \n"
                           "large enough.\n\n"
                           " You can scroll the content\n"
                           "See the scroll bar on the right!");
}
    static void event_handler(lv_obj_t * obj, lv_event_t event)
    {
    if(event == LV_EVENT_VALUE_CHANGED) {
        char buf[32];
        lv_roller_get_selected_str(obj, buf, sizeof(buf));
       // printf("Selected month: %s\n", buf);
      }
    }

    virtual void lv_event_class(lv_obj_t * object, lv_event_t event)
    {
      if (object == pColorButtonR && event == LV_EVENT_SHORT_CLICKED) {
        sri = lv_roller_get_selected(roller1);
        lv_roller_set_selected(roller1, sri +1, LV_ANIM_ON);
      } else if (object == pColorButtonL && event == LV_EVENT_SHORT_CLICKED) {
        sri = lv_roller_get_selected(roller1);
        lv_roller_set_selected(roller1, sri -1, LV_ANIM_ON);
      } 
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
  lv_style_t st;
  lv_obj_t *label, *pColorButtonL, *pColorButtonL_label,*pColorButtonR, *pColorButtonR_label, *roller1;
};

DemoScreen demoScreen;
