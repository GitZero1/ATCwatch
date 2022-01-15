#pragma once
#include "Arduino.h"
#include "class.h"
#include "images.h"
#include "menu.h"
#include "inputoutput.h"
#include "display.h"
#include "ble.h"
#include "time.h"
#include "battery.h"
#include "accl.h"
#include "push.h"
#include "heartrate.h"
#include "fonts.h"
#include "sleep.h"
#include <lvgl.h>


class HomeScreen : public Screen
{
  public:
    virtual void pre()
    {
      //bg color
      lv_obj_set_style_local_bg_color(lv_scr_act(),LV_OBJ_PART_MAIN,LV_STATE_DEFAULT, LV_COLOR_BLACK);
      // BATTERY ------------------------------------------------------------------------------------------------------------------------------
      label_battery_icon = lv_label_create(lv_scr_act(), nullptr);
      lv_label_set_text(label_battery_icon, LV_SYMBOL_BATTERY_FULL);
      lv_obj_align(label_battery_icon, nullptr, LV_ALIGN_IN_TOP_MID, 10, 20);
      
      // BATTERY TEXT
      label_battery = lv_label_create(lv_scr_act(), nullptr);
      lv_obj_align(label_battery, label_battery_icon, LV_ALIGN_OUT_RIGHT_MID, 3, 2);
      lv_label_set_text_fmt(label_battery, "%i%%", get_battery_percent());
      lv_obj_set_style_local_text_color(label_battery,LV_OBJ_PART_MAIN,LV_STATE_DEFAULT,LV_COLOR_WHITE);
      
      // BATTERY COLOR
      lv_obj_set_style_local_text_color(label_battery_icon,LV_OBJ_PART_MAIN,LV_STATE_DEFAULT,lv_color_hsv_to_rgb(10, 5, 95));
      
      // Bluetooth ---------------------------------------------------------------------------------------------------------------------------
      label_ble = lv_label_create(lv_scr_act(), nullptr);
      lv_label_set_text(label_ble, LV_SYMBOL_BLUETOOTH);
      lv_obj_align(label_ble, nullptr, LV_ALIGN_IN_TOP_MID, -20, 20);

      //BLUETOOTH COLOR
      lv_obj_set_style_local_text_color(label_ble,LV_OBJ_PART_MAIN,LV_STATE_DEFAULT,LV_COLOR_RED);

      //TIME TEXT
      label_time = lv_label_create(lv_scr_act(), nullptr);
      lv_label_set_text_fmt(label_time,  "%02i:%02i", ztime, time_data.min);
      lv_obj_set_style_local_text_font(label_time,LV_OBJ_PART_MAIN,LV_STATE_DEFAULT,&dsDigiBold_72);
      lv_obj_set_style_local_text_color(label_time,LV_OBJ_PART_MAIN,LV_STATE_DEFAULT,LV_COLOR_WHITE);
      //lv_obj_align(label_time, nullptr, LV_ALIGN_IN_TOP_RIGHT, -5, 25); //top right time
      lv_obj_align(label_time, nullptr, LV_ALIGN_CENTER, 0, 0); //center time

      //DATE TEXT
      label_date = lv_label_create(lv_scr_act(), nullptr);
      lv_label_set_text_fmt(label_date, "%s, %s %02i", string2char(weekday), string2char(month), time_data.day);
      lv_obj_set_style_local_text_color(label_date,LV_OBJ_PART_MAIN,LV_STATE_DEFAULT,LV_COLOR_WHITE);
      lv_obj_align(label_date, label_time, LV_ALIGN_OUT_BOTTOM_MID, 0, -7);

      //UPTIME STRING
      label_uptime = lv_label_create(lv_scr_act(), NULL);
      lv_label_set_text(label_uptime, "Uptime:");
      lv_obj_align(label_uptime, NULL, LV_ALIGN_CENTER, -40, -35);

      /*
      //ANALOG HANDS ###########################################################################################################
      img_secs = lv_img_create(lv_scr_act(), nullptr);
      lv_img_set_src(img_secs, &ItestImg2);
      lv_img_set_pivot(img_secs, 32, 118);
      lv_obj_align(img_secs, nullptr, LV_ALIGN_CENTER, 0, -90);
      lv_obj_set_style_local_image_recolor_opa(img_secs, LV_IMG_PART_MAIN, LV_STATE_DEFAULT, 255);
      lv_obj_set_style_local_image_recolor(img_secs,LV_IMG_PART_MAIN,LV_STATE_DEFAULT, LV_COLOR_WHITE);
      
      //lv_img_set_zoom(img_secs,1024);
      //lv_obj_align(img_secs, nullptr, LV_ALIGN_CENTER, 0, -60);
      
      img_mins = lv_img_create(lv_scr_act(), nullptr);
      lv_img_set_src(img_mins, &IsymbolHeartIcon);
      lv_img_set_pivot(img_mins, 9,90);
      //lv_img_set_zoom(img_mins,1024);
      lv_obj_align(img_mins, nullptr, LV_ALIGN_CENTER, 0, -81);

      img_hrs = lv_img_create(lv_scr_act(), nullptr);
      lv_img_set_src(img_hrs, &IsymbolHeartIcon);
      lv_img_set_pivot(img_hrs, 9, 60);
      //lv_img_set_zoom(img3,512);
      lv_obj_align(img_hrs, nullptr, LV_ALIGN_CENTER, 0, -51);
      */
    }

    virtual void main(){
      time_data = get_time();
      weekday = getDayString();
      month = getMonthString();
      ztime = get12hrTime();
      home_uptime();
      //UPDATE BATTERY ICON
      if (get_battery_percent() < 15){
        lv_label_set_text(label_battery_icon, LV_SYMBOL_BATTERY_EMPTY);
        lv_obj_set_style_local_text_color(label_battery_icon,LV_OBJ_PART_MAIN,LV_STATE_DEFAULT,LV_COLOR_RED);
      } else if (get_battery_percent() > 75){
        lv_label_set_text(label_battery_icon, LV_SYMBOL_BATTERY_FULL);
        lv_obj_set_style_local_text_color(label_battery_icon,LV_OBJ_PART_MAIN,LV_STATE_DEFAULT,LV_COLOR_MAKE(0x05, 0xF9, 0x25));
        } else {
          lv_label_set_text(label_battery_icon, LV_SYMBOL_BATTERY_2);
          lv_obj_set_style_local_text_color(label_battery_icon,LV_OBJ_PART_MAIN,LV_STATE_DEFAULT,LV_COLOR_MAKE(0x05, 0xF9, 0x25));
        } 
      
      //UPDATE BATTERY TEXT
      lv_label_set_text_fmt(label_battery, "%i%%", get_battery_percent());
      //UPDATE BLUETOOTH CONNECTION ICON
      if (get_vars_ble_connected())
        lv_obj_set_style_local_text_color(label_ble,LV_OBJ_PART_MAIN,LV_STATE_DEFAULT,LV_COLOR_MAKE(0x27, 0xA6, 0xFF));
      else
        lv_obj_set_style_local_text_color(label_ble,LV_OBJ_PART_MAIN,LV_STATE_DEFAULT,LV_COLOR_RED);
      //UPDATE TIME
      lv_label_set_text_fmt(label_time,  "%02i:%02i", ztime, time_data.min);
      lv_obj_realign(label_time);
      //UPDATE DATE
      lv_label_set_text_fmt(label_date, "%s, %s %02i", string2char(weekday), string2char(month), time_data.day);
      lv_obj_realign(label_date);
      //Point Min hand //testing with sec
      //lv_img_set_angle(img_secs, time_data.sec*6*10);
      //lv_obj_move_foreground(img_secs);
      //lv_img_set_angle(img_mins, time_data.min*6*10);
      //lv_img_set_angle(img_hrs, time_data.hr*30*10);
    }
    
 

    virtual void home_uptime(){
      long days = 0;
      long hours = 0;
      long mins = 0;
      long secs = 0;
      secs = millis() / 1000;
      mins = secs / 60;
      hours = mins / 60;
      days = hours / 24;
      secs = secs - (mins * 60);
      mins = mins - (hours * 60);
      hours = hours - (days * 24);

      char time_string[14];
      sprintf(time_string, "%i %02i:%02i:%02i", days, hours, mins, secs);
      lv_label_set_text_fmt(label_uptime, "Uptime: %s", time_string);
    }

    //Swipes
    //-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    virtual void up()
    {
      inc_vars_menu();
    }

    virtual void down()
    {
      dec_vars_menu();
    }

    virtual void left()
    {
    }

    virtual void right()
    {
    }

    virtual void button_push(int length)
    {
      sleep_down();
    }

    //-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

  private:
    String weekday;
    String month;
    int ztime;
    time_data_struct time_data;
    lv_obj_t *label_time, *label_date, *label_millis, *label_uptime;
    lv_obj_t *label_ble, *label_battery, *label_battery_icon;
    lv_style_t style_ble, style_battery;
    lv_obj_t  *img_secs, *img_mins, *img_hrs;

    char* string2char(String command) {
      if (command.length() != 0) {
        char *p = const_cast<char*>(command.c_str());
        return p;
      }
    }
};

HomeScreen homeScreen;
