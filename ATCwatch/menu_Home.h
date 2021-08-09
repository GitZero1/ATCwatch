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
      time_data = get_time();
      int ztime = time_data.hr;
      if(ztime == 0)
        ztime = 12;
      else if (ztime > 12)
        ztime = ztime - 12;
      
      accl_data = get_accl_data();


      
      // STYLE FOR BATTERY TEXT
      lv_style_copy( &st1, &lv_style_plain );
      st1.text.color = lv_color_hsv_to_rgb(10, 5, 95);
      st1.text.font = &lv_font_roboto_12;

      
      //BACKGROUND IMAGE
      lv_obj_t * img1 = lv_img_create(lv_scr_act(), NULL);
      lv_img_set_src(img1, &IsZeroneLarge); //TODO remove or change this// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
      lv_obj_align(img1, NULL, LV_ALIGN_CENTER, 0, 24);
     


      //DATE TIME ##############################################################################################################

      //FONT AND STYLE FOR TIME
      lv_style_copy( &st, &lv_style_plain );
      st.text.color = lv_color_hsv_to_rgb(10, 5, 95);
      st.text.font = &mksd50;



    
      //TIME TEXT
      label_time = lv_label_create(lv_scr_act(), NULL);
      lv_label_set_text_fmt(label_time,  "%02i:%02i", ztime, time_data.min);
      //lv_label_set_text(label_time,  "1234");
      lv_obj_set_style( label_time, &st );
      lv_obj_align(label_time, NULL, LV_ALIGN_IN_TOP_RIGHT, -3, 3);


      //DATE TEXT
      label_date = lv_label_create(lv_scr_act(), NULL);
      lv_label_set_text_fmt(label_date, "%02i/%02i/%04i", time_data.month, time_data.day, time_data.year);
      //lv_obj_set_style( label_date, &st );
      lv_obj_align(label_date, label_time, LV_ALIGN_OUT_BOTTOM_MID, 0, -13);
      //DATE TIME ##############################################################################################################





      //BATTERY##############################################################################################################
      // BATTERY ICON
      label_battery_icon = lv_label_create(lv_scr_act(), NULL);
      lv_label_set_text(label_battery_icon, LV_SYMBOL_BATTERY_FULL);
      lv_obj_align(label_battery_icon, NULL, LV_ALIGN_IN_TOP_LEFT, 2, 1);

      
      // BATTERY TEXT
      label_battery = lv_label_create(lv_scr_act(), NULL);
      lv_obj_align(label_battery, label_battery_icon, LV_ALIGN_OUT_RIGHT_MID, 3, 2);
      lv_label_set_text_fmt(label_battery, "%i%%", get_battery_percent());
      lv_obj_set_style( label_battery, &st1 );
      
      
      // BATTERY COLOR
      lv_style_copy(&style_battery, lv_label_get_style(label_battery_icon, LV_LABEL_STYLE_MAIN));
      style_battery.text.color = lv_color_hsv_to_rgb(10, 5, 95);
      lv_obj_set_style(label_battery_icon, &style_battery);

      //BATTERY##############################################################################################################




      //BLUETOOTH ############################################################################################################

      //BLUETOOTH ICON
      label_ble = lv_label_create(lv_scr_act(), NULL);
      lv_obj_align(label_ble, NULL, LV_ALIGN_IN_TOP_LEFT, 2, 22);
      lv_label_set_text(label_ble, LV_SYMBOL_BLUETOOTH);

      //BLUETOOTH COLOR
      lv_style_copy(&style_ble, lv_label_get_style(label_ble, LV_LABEL_STYLE_MAIN));
      style_ble.text.color = LV_COLOR_RED;
      style_ble.text.font = LV_FONT_DEFAULT;
      lv_obj_set_style(label_ble, &style_ble);
      
      //BLUETOOTH ###########################################################################################################
    

      //HEART ###########################################################################################################

      //HEART ICON      
      img_heart = lv_img_create(lv_scr_act(), NULL);  
      lv_img_set_src(img_heart, &IsymbolHeartIcon);
      lv_obj_align(img_heart, NULL, LV_ALIGN_IN_BOTTOM_LEFT, 2, -25);
      
      //HEART TEXT
      label_heart = lv_label_create(lv_scr_act(), NULL);
      lv_obj_set_width(label_heart, 240);
      lv_label_set_text_fmt(label_heart, "%i", get_last_heartrate());
      lv_obj_align(label_heart, img_heart, LV_ALIGN_OUT_RIGHT_MID, 2, 0);

      //HEART ###########################################################################################################

      #ifdef COUNT_STEPS
      
      
      //STEPS IMAGE
      img_steps = lv_img_create(lv_scr_act(), NULL);
      lv_img_set_src(img_steps, &IsymbolFootIcon);
      lv_obj_align(img_steps, NULL, LV_ALIGN_IN_BOTTOM_LEFT, 2, -5);

      //STEPS TEXT
      label_steps = lv_label_create(lv_scr_act(), NULL);
      lv_obj_set_width(label_steps, 240);
      lv_label_set_text_fmt(label_steps, "%i", accl_data.steps);
      lv_obj_align(label_steps, img_steps, LV_ALIGN_OUT_RIGHT_MID, 2, 0);
      #endif


      /*
      img_msg = lv_img_create(lv_scr_act(), NULL);
      lv_img_set_src(img_msg, &IsymbolMsgSmall);
      lv_obj_align(img_msg, NULL, LV_ALIGN_IN_BOTTOM_LEFT, 0, -8);
      
      label_msg = lv_label_create(lv_scr_act(), NULL);

      lv_style_copy(&style_msg, lv_label_get_style(label_ble, LV_LABEL_STYLE_MAIN));
      style_msg.text.color = lv_color_hsv_to_rgb(10, 5, 95);
      style_msg.text.font = &sans_regular;
      lv_obj_set_style(label_msg, &style_msg);

      lv_obj_set_width(label_msg, 240);
      lv_label_set_text(label_msg, " ");
      lv_label_set_text(label_msg, string2char(get_push_msg(30)));
      lv_obj_align(label_msg, label_ble, LV_ALIGN_OUT_RIGHT_MID, 2, 0);
      */
    }

    virtual void main()
    {
      //CONVERT TIME TO 12 Hour
      time_data = get_time();
      int ztime = time_data.hr;
      if(ztime == 0)
        ztime = 12;
      else if (ztime > 12)
        ztime = ztime - 12;
      

      
      //UPDATE STEP DATA
      accl_data = get_accl_data();



      //UPDATE TIME
      //lv_label_set_text(label_time,  "zer0");
      lv_label_set_text_fmt(label_time,  "%02i:%02i", ztime, time_data.min);
      //UPDATE DATE
      lv_label_set_text_fmt(label_date, "%02i/%02i/%04i", time_data.month, time_data.day, time_data.year);


      
      //UPDATE BATTERY TEXT
      lv_label_set_text_fmt(label_battery, "%i%%", get_battery_percent());
      
      
      //UPDATE BATTERY ICON
      if (get_battery_percent() < 15) lv_label_set_text(label_battery_icon, LV_SYMBOL_BATTERY_EMPTY);
      else if (get_battery_percent() > 75) lv_label_set_text(label_battery_icon, LV_SYMBOL_BATTERY_FULL);
      else lv_label_set_text(label_battery_icon, LV_SYMBOL_BATTERY_2);
      
      //UPDATE HEARTREATE TEXT
      lv_label_set_text_fmt(label_heart, "%i", get_last_heartrate());

      // UPDATE STEPS
      #ifdef COUNT_STEPS 
      lv_label_set_text_fmt(label_steps, "%i", accl_data.steps);
      #endif


      //UPDATE BLUETOOTH CONNECTION ICON
      if (get_vars_ble_connected())
        style_ble.text.color = LV_COLOR_MAKE(0x27, 0xA6, 0xFF);
      else
        style_ble.text.color = LV_COLOR_RED;
      lv_obj_set_style(label_ble, &style_ble);



      // COLOR AND CHANGE BATTERY ICON
      if (get_battery_percent() < 15) style_battery.text.color = LV_COLOR_RED;
      else
        style_battery.text.color = LV_COLOR_MAKE(0x05, 0xF9, 0x25);
      lv_obj_set_style(label_battery_icon, &style_battery);

    }

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

  private:
    time_data_struct time_data;
    accl_data_struct accl_data;
    lv_style_t st, st1;
    lv_obj_t *label, *label_heart, *label_steps, *label_msg;
    lv_obj_t *label_time, *label_date;
    lv_obj_t *label_ble, *label_battery, *label_battery_icon;
    lv_style_t style_ble, style_battery, style_msg;
    lv_obj_t * img_heart, *img_steps, *img_msg;

    char* string2char(String command) {
      if (command.length() != 0) {
        char *p = const_cast<char*>(command.c_str());
        return p;
      }
    }
};

HomeScreen homeScreen;
