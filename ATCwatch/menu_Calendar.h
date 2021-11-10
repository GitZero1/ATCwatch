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
/*    
    0 = white
    1 = gray
    2 = black
    3 = red
    4 = green
    5 = blue
    6 = green?  
    */
class CalendarScreen : public Screen
{
  public:
    virtual void pre()
    {
      set_swipe_enabled(true);

      initCalTest();

    }


    virtual void main(){

    }

    virtual void initCalTest(){
      static lv_style_t style_bg;
      lv_style_copy(&style_bg, &lv_style_plain);
      style_bg.body.main_color = LV_COLOR_WHITE;
      style_bg.body.grad_color = LV_COLOR_WHITE;
      style_bg.text.color = LV_COLOR_BLACK;
      //lv_obj_set_style(lv_scr_act(), &style_bg);

      static lv_style_t style_header;
      lv_style_copy(&style_header, &lv_style_plain);
      style_header.body.main_color = LV_COLOR_MAKE(0xFF, 0x4D, 0x4D);
      style_header.body.grad_color = LV_COLOR_MAKE(0xFF, 0x4D, 0x4D);
      style_header.text.color = LV_COLOR_BLACK;
      //lv_obj_set_style(lv_scr_act(), &style_header);

      static lv_style_t style_dayNames;
      lv_style_copy(&style_dayNames, &lv_style_plain);
      style_dayNames.body.main_color = LV_COLOR_WHITE;
      style_dayNames.body.grad_color = LV_COLOR_WHITE;
      style_dayNames.text.color = LV_COLOR_BLUE;
      //lv_obj_set_style(lv_scr_act(), &style_dayNames);

      static lv_style_t style_weekBox;
      lv_style_copy(&style_weekBox, &lv_style_plain);
      style_weekBox.body.main_color = LV_COLOR_MAKE(0xB3, 0xB3, 0xB3);
      style_weekBox.body.grad_color = LV_COLOR_MAKE(0xB3, 0xB3, 0xB3);
      style_weekBox.text.color = LV_COLOR_BLACK;
      style_weekBox.body.radius=6;
      //lv_obj_set_style(lv_scr_act(), &style_weekBox);

      static lv_style_t style_todayBox;
      lv_style_copy(&style_todayBox, &lv_style_plain);
      style_todayBox.body.main_color = LV_COLOR_MAKE(0x80, 0xCC, 0xFF);
      style_todayBox.body.grad_color = LV_COLOR_MAKE(0x80, 0xCC, 0xFF);
      style_todayBox.text.color = LV_COLOR_BLACK;
      style_todayBox.body.radius=6;
      //lv_obj_set_style(lv_scr_act(), &style_todayBox);

      static lv_style_t style_inactiveDays;
      lv_style_copy(&style_inactiveDays, &lv_style_plain);
      style_inactiveDays.body.main_color = LV_COLOR_WHITE;
      style_inactiveDays.body.grad_color = LV_COLOR_WHITE;
      style_inactiveDays.text.color = LV_COLOR_MAKE(0xD9, 0xD9, 0xD9);
      //lv_obj_set_style(lv_scr_act(), &style_inactiveDays);


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
  
};

CalendarScreen calendarScreen;
