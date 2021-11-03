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
      //createStyle();
      //lv_ex_calendar_1();

      initCalTest();

    
    /*
    label = lv_label_create(lv_scr_act(), NULL);
    lv_label_set_text(label, "DEMO SCREEN");
    lv_obj_align(label, NULL, LV_ALIGN_IN_BOTTOM_LEFT, 0, 0);

    tContainer();

    btn1 = lv_btn_create(lv_scr_act(),nullptr);
    lv_obj_align(btn1, nullptr, LV_ALIGN_IN_BOTTOM_RIGHT, 0 , 0);
    label = lv_label_create(btn1, nullptr);
    lv_label_set_text(label,"FF");
    */
    

    }


    virtual void main(){

    }

    virtual void createStyle(){
      lv_style_copy( &st, &lv_style_plain );
      st.text.color = lv_color_make(0x00, 0x00, 0x00);
      st.body.main_color = lv_color_make(0xFF, 0xFF, 0xFF);
      st.body.grad_color = lv_color_make(0xFF, 0xFF, 0xFF);
      //st.body.
    }

    void lv_ex_calendar_1(void)
    {
        lv_obj_t  * calendar = lv_calendar_create(lv_scr_act(), NULL);
        lv_obj_set_size(calendar, 235, 235);
        lv_obj_align(calendar, NULL, LV_ALIGN_CENTER, 0, 0);
        lv_obj_set_event_cb(calendar, lv_event_handler);

        lv_obj_set_style(calendar, &st);

        /*Make the date number smaller to be sure they fit into their area*/
        //lv_obj_set_style_local_text_font(calendar, LV_CALENDAR_PART_DATE, LV_STATE_DEFAULT, lv_theme_get_font_small());

        /*Set today's date*/
        lv_calendar_date_t today;
        today.year = 2018;
        today.month = 10;
        today.day = 23;

        lv_calendar_set_today_date(calendar, &today);
        lv_calendar_set_showed_date(calendar, &today);

        /*Highlight a few days*/
        static lv_calendar_date_t highlighted_days[3];       /*Only its pointer will be saved so should be static*/
        highlighted_days[0].year = 2018;
        highlighted_days[0].month = 10;
        highlighted_days[0].day = 6;

        highlighted_days[1].year = 2018;
        highlighted_days[1].month = 10;
        highlighted_days[1].day = 11;

        highlighted_days[2].year = 2018;
        highlighted_days[2].month = 11;
        highlighted_days[2].day = 22;

        lv_calendar_set_highlighted_dates(calendar, highlighted_days, 3);
    }


    
    //test container
    virtual void tContainer(){
      lv_style_copy( &st, &lv_style_plain );
      st.text.color = LV_COLOR_MAKE(0xFF, 0xFF, 0xFF);
      st.body.main_color = lv_color_make(0x00, 0xFF, 0x00);
      st.body.grad_color = lv_color_make(0x00, 0x00, 0x00);
      //st1.text.color = lv_color_hsv_to_rgb(0, 0, 0);
      st.text.font = &lv_font_roboto_28;


      lv_obj_t * cont;

      cont = lv_cont_create(lv_scr_act(), NULL);
      lv_obj_align(cont, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 0);  /*This parametrs will be sued when realigned*/
      //lv_obj_set_pos(cont, 0, 50);
      lv_obj_set_size(cont, LV_HOR_RES, 100);
      lv_cont_set_layout(cont, LV_LAYOUT_COL_M);
      //lv_cont_set_style(cont, LV_CONT_STYLE_MAIN, st);
      lv_obj_set_style(cont, &st);

      label = lv_label_create(cont, NULL);
      lv_label_set_text(label, "Short text");


      //lv_obj_set_style_local_text_color(calendar, LV_CALENDAR_, LV_STATE_DEFAULT, lv_color_hex(0xFFFFFF));


  

      /*Refresh and pause here for a while to see how `fit` works
      uint32_t t;
      lv_refr_now(NULL);
      t = lv_tick_get();
      while(lv_tick_elaps(t) < 500);

      label = lv_label_create(cont, NULL);
      lv_label_set_text(label, "It is a long text");

      //Wait here too
      lv_refr_now(NULL);
      t = lv_tick_get();
      while(lv_tick_elaps(t) < 500);

      label = lv_label_create(cont, NULL);
      lv_label_set_text(label, "Here is an even longer text");
      */

    }







    virtual void initCalTest(){
      static lv_style_t style_bg;
      lv_style_copy(&style_bg, &lv_style_plain);
      style_bg.body.main_color = LV_COLOR_WHITE;
      style_bg.body.grad_color = LV_COLOR_WHITE;
      style_bg.text.color = LV_COLOR_BLACK;
      lv_obj_set_style(lv_scr_act(), &style_bg);

      static lv_style_t style_header;
      lv_style_copy(&style_header, &lv_style_plain);
      style_header.body.main_color = LV_COLOR_MAKE(0xFF, 0x4D, 0x4D);
      style_header.body.grad_color = LV_COLOR_MAKE(0xFF, 0x4D, 0x4D);
      style_header.text.color = LV_COLOR_BLACK;
      lv_obj_set_style(lv_scr_act(), &style_header);

      static lv_style_t style_dayNames;
      lv_style_copy(&style_dayNames, &lv_style_plain);
      style_dayNames.body.main_color = LV_COLOR_WHITE;
      style_dayNames.body.grad_color = LV_COLOR_WHITE;
      style_dayNames.text.color = LV_COLOR_BLUE;
      lv_obj_set_style(lv_scr_act(), &style_dayNames);

      static lv_style_t style_weekBox;
      lv_style_copy(&style_weekBox, &lv_style_plain);
      style_weekBox.body.main_color = LV_COLOR_MAKE(0xB3, 0xB3, 0xB3);
      style_weekBox.body.grad_color = LV_COLOR_MAKE(0xB3, 0xB3, 0xB3);
      style_weekBox.text.color = LV_COLOR_BLACK;
      style_weekBox.body.radius=6;
      lv_obj_set_style(lv_scr_act(), &style_weekBox);

      static lv_style_t style_todayBox;
      lv_style_copy(&style_todayBox, &lv_style_plain);
      style_todayBox.body.main_color = LV_COLOR_MAKE(0x80, 0xCC, 0xFF);
      style_todayBox.body.grad_color = LV_COLOR_MAKE(0x80, 0xCC, 0xFF);
      style_todayBox.text.color = LV_COLOR_BLACK;
      style_todayBox.body.radius=6;
      lv_obj_set_style(lv_scr_act(), &style_todayBox);

      static lv_style_t style_inactiveDays;
      lv_style_copy(&style_inactiveDays, &lv_style_plain);
      style_inactiveDays.body.main_color = LV_COLOR_WHITE;
      style_inactiveDays.body.grad_color = LV_COLOR_WHITE;
      style_inactiveDays.text.color = LV_COLOR_MAKE(0xD9, 0xD9, 0xD9);
      lv_obj_set_style(lv_scr_act(), &style_inactiveDays);


      time_data = get_time();

      lv_obj_t  * calendar = lv_calendar_create(lv_scr_act(), NULL);
      lv_obj_set_size(calendar, 238, 238);
      lv_obj_align(calendar, NULL, LV_ALIGN_CENTER, 0, 0);
      lv_calendar_set_style(calendar, LV_CALENDAR_STYLE_BG, &style_bg);
      lv_calendar_set_style(calendar, LV_CALENDAR_STYLE_HEADER, &style_header);
      lv_calendar_set_style(calendar, LV_CALENDAR_STYLE_HEADER_PR, &style_header);


      lv_calendar_set_style(calendar, LV_CALENDAR_STYLE_DAY_NAMES, &style_dayNames);
      lv_calendar_set_style(calendar, LV_CALENDAR_STYLE_WEEK_BOX, &style_weekBox);
      lv_calendar_set_style(calendar, LV_CALENDAR_STYLE_TODAY_BOX, &style_todayBox);
      lv_calendar_set_style(calendar, LV_CALENDAR_STYLE_INACTIVE_DAYS, &style_inactiveDays);


      lv_calendar_date_t today;

      today.day = time_data.day;
      today.month = time_data.month;
      today.year = time_data.year;


      lv_calendar_set_today_date(calendar, &today);
      lv_calendar_set_showed_date(calendar, &today);
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
