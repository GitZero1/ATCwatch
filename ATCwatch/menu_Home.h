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
#include "screen_style.h"
#include <lvgl.h>


class HomeScreen : public Screen
{
  public:
    virtual void pre()
    {
      getHomeScreenData();
      init_objects();
    }
   
    virtual void main(){
        getHomeScreenData();
        updateFace();
    }
    
    virtual void init_objects(){
      //#ifdef PineTime //round display layout
      #ifdef SN80
      //style ----------------------------------------------------------------------------------------------------------------------------------
      set_gray_screen_style();
      // STYLE FOR BATTERY TEXT
      lv_style_copy( &style_battery_text, &lv_style_plain );
      style_battery_text.text.color = LV_COLOR_WHITE;
      style_battery_text.text.font = &lv_font_roboto_12;

      //FONT AND STYLE FOR TIME
      lv_style_copy( &style_time, &lv_style_plain );
      style_time.text.font = &dsDigiBold_72;
      if(get_main_color() == 2){
        style_time.text.color = LV_COLOR_WHITE; 
      } else {style_time.text.color = LV_COLOR_BLACK;}

      //FONT AND STYLE FOR DATE
      lv_style_copy( &style_date, &lv_style_plain );
      style_date.text.color = LV_COLOR_BLACK;
      if(get_main_color() == 2){
        style_date.text.color = LV_COLOR_WHITE;
      } else {style_date.text.color = LV_COLOR_BLACK;}

      //BACKGROUND IMAGE -------------------------------------------------------------------------------------------------------------------
      //img1 = lv_img_create(lv_scr_act(), nullptr);
      //lv_img_set_src(img1, &Ixmas2); 
      //lv_obj_align(img1, nullptr, LV_ALIGN_IN_BOTTOM_MID, 0, 0);


      // BATTERY ------------------------------------------------------------------------------------------------------------------------------
      label_battery_icon = lv_label_create(lv_scr_act(), nullptr);
      lv_label_set_text(label_battery_icon, LV_SYMBOL_BATTERY_FULL);
      lv_obj_align(label_battery_icon, nullptr, LV_ALIGN_IN_TOP_MID, 10, 20);
      
      // BATTERY TEXT
      label_battery = lv_label_create(lv_scr_act(), nullptr);
      lv_obj_align(label_battery, label_battery_icon, LV_ALIGN_OUT_RIGHT_MID, 3, 2);
      lv_label_set_text_fmt(label_battery, "%i%%", get_battery_percent());
      lv_obj_set_style( label_battery, &style_battery_text );
      
      // BATTERY COLOR
      lv_style_copy(&style_battery, lv_label_get_style(label_battery_icon, LV_LABEL_STYLE_MAIN));
      style_battery.text.color = LV_COLOR_WHITE;
      lv_obj_set_style(label_battery_icon, &style_battery);
      
      // Bluetooth ---------------------------------------------------------------------------------------------------------------------------
      label_ble = lv_label_create(lv_scr_act(), nullptr);
      lv_label_set_text(label_ble, LV_SYMBOL_BLUETOOTH);
      lv_obj_align(label_ble, nullptr, LV_ALIGN_IN_TOP_MID, -20, 20);

      //BLUETOOTH COLOR
      lv_style_copy(&style_ble, lv_label_get_style(label_ble, LV_LABEL_STYLE_MAIN));
      style_ble.text.color = LV_COLOR_RED;
      style_ble.text.font = LV_FONT_DEFAULT;
      lv_obj_set_style(label_ble, &style_ble);

      /*Heartrate -----------------------------------------------------------------------------------------------------------------------------
      
      //HEART ICON      
      img_heart = lv_img_create(lv_scr_act(), nullptr);  
      lv_img_set_src(img_heart, &IsymbolHeartIcon);
      lv_obj_align(img_heart, nullptr, LV_ALIGN_IN_TOP_MID, -45, 40);
      
      //HEART TEXT
      label_heart = lv_label_create(lv_scr_act(), nullptr);
      lv_label_set_text_fmt(label_heart, "%i", get_last_heartrate());
      lv_obj_align(label_heart, img_heart, LV_ALIGN_OUT_RIGHT_MID, 2, 0);
      
      // STEPS---------------------------------------------------------------------------------------------------------------------------------
      
      //STEPS IMAGE
      img_steps = lv_img_create(lv_scr_act(), nullptr);
      lv_img_set_src(img_steps, &IsymbolFootIcon);
      lv_obj_align(img_steps, nullptr, LV_ALIGN_IN_TOP_MID, 10, 40);

      //STEPS TEXT
      label_steps = lv_label_create(lv_scr_act(), nullptr);
      lv_label_set_text_fmt(label_steps, "%i", accl_data.steps);
      lv_obj_align(label_steps, img_steps, LV_ALIGN_OUT_RIGHT_MID, 2, 0);
      */
      //DATE TIME ##############################################################################################################
      //TIME TEXT
      label_time = lv_label_create(lv_scr_act(), nullptr);
      lv_label_set_text_fmt(label_time,  "%02i:%02i", ztime, time_data.min);
      lv_obj_set_style( label_time, &style_time );
      //lv_obj_align(label_time, nullptr, LV_ALIGN_IN_TOP_RIGHT, -5, 25); //top right time
      lv_obj_align(label_time, nullptr, LV_ALIGN_CENTER, 0, 0); //center time

      //DATE TEXT
      label_date = lv_label_create(lv_scr_act(), nullptr);
      lv_label_set_text_fmt(label_date, "%s, %s %02i", string2char(weekday), string2char(month), time_data.day);
      lv_obj_align(label_date, label_time, LV_ALIGN_OUT_BOTTOM_MID, 0, -7);


      #else // Round Display//Square Display P8/PineTime
      //style ----------------------------------------------------------------------------------------------------------------------------------
      set_gray_screen_style();
      // STYLE FOR BATTERY TEXT
      lv_style_copy( &style_battery_text, &lv_style_plain );
      style_battery_text.text.color = LV_COLOR_WHITE;
      style_battery_text.text.font = &lv_font_roboto_12;

      //FONT AND STYLE FOR TIME
      lv_style_copy( &style_time, &lv_style_plain );
      style_time.text.font = &mksd50;
      style_time.text.color = LV_COLOR_BLACK;
      //if(get_main_color() == 2){
      //  style_time.text.color = LV_COLOR_WHITE; //usually make this white
      //} else {style_time.text.color = LV_COLOR_BLACK;}

      //FONT AND STYLE FOR DATE
      lv_style_copy( &style_date, &lv_style_plain );
      style_date.text.color = LV_COLOR_BLACK;
      //if(get_main_color() == 2){
      //  style_time.text.color = LV_COLOR_WHITE; //usually make this white
      //} else {style_time.text.color = LV_COLOR_BLACK;}
      

      //FONT AND STYLE FOR BAR
      lv_style_copy( &stBar, &lv_style_plain );
      stBar.text.color = LV_COLOR_MAKE(0xFF, 0xFF, 0xFF);
      stBar.body.main_color = lv_color_make(0x00, 0x00, 0x00);
      stBar.body.grad_color = lv_color_make(0x00, 0x00, 0x00);

      //BACKGROUND IMAGE -------------------------------------------------------------------------------------------------------------------
      //img1 = lv_img_create(lv_scr_act(), nullptr);
      //lv_img_set_src(img1, &Ixmas2); 
      //lv_obj_align(img1, nullptr, LV_ALIGN_IN_BOTTOM_MID, 0, 0);

      //BAR ---------------------------------------------------------------------------------------------------------------------------------
      
      cont = lv_cont_create(lv_scr_act(), nullptr);
      lv_obj_align(cont, nullptr, LV_ALIGN_IN_TOP_LEFT, 0, 0); 
      lv_obj_set_size(cont, LV_HOR_RES, 20);
      lv_obj_set_style(cont, &stBar);

      // BATTERY ------------------------------------------------------------------------------------------------------------------------------
      label_battery_icon = lv_label_create(cont, nullptr);
      lv_label_set_text(label_battery_icon, LV_SYMBOL_BATTERY_FULL);
      lv_obj_align(label_battery_icon, nullptr, LV_ALIGN_IN_TOP_LEFT, 2, 1);
      
      // BATTERY TEXT
      label_battery = lv_label_create(cont, nullptr);
      lv_obj_align(label_battery, label_battery_icon, LV_ALIGN_OUT_RIGHT_MID, 3, 2);
      lv_label_set_text_fmt(label_battery, "%i%%", get_battery_percent());
      lv_obj_set_style( label_battery, &style_battery_text );
      
      // BATTERY COLOR
      lv_style_copy(&style_battery, lv_label_get_style(label_battery_icon, LV_LABEL_STYLE_MAIN));
      style_battery.text.color = lv_color_hsv_to_rgb(10, 5, 95);
      lv_obj_set_style(label_battery_icon, &style_battery);
      
      // Bluetooth ---------------------------------------------------------------------------------------------------------------------------
      label_ble = lv_label_create(cont, nullptr);
      lv_label_set_text(label_ble, LV_SYMBOL_BLUETOOTH);
      lv_obj_align(label_ble, nullptr, LV_ALIGN_IN_TOP_RIGHT, -5, 0);

      //BLUETOOTH COLOR
      lv_style_copy(&style_ble, lv_label_get_style(label_ble, LV_LABEL_STYLE_MAIN));
      style_ble.text.color = LV_COLOR_RED;
      style_ble.text.font = LV_FONT_DEFAULT;
      lv_obj_set_style(label_ble, &style_ble);

      //Heartrate -----------------------------------------------------------------------------------------------------------------------------
      //HEART ICON      
      img_heart = lv_img_create(cont, nullptr);  
      lv_img_set_src(img_heart, &IsymbolHeartIcon);
      lv_obj_align(img_heart, nullptr, LV_ALIGN_IN_TOP_MID, -50, 2);
      
      //HEART TEXT
      label_heart = lv_label_create(cont, nullptr);
      lv_label_set_text_fmt(label_heart, "%i", get_last_heartrate());
      lv_obj_align(label_heart, img_heart, LV_ALIGN_OUT_RIGHT_MID, 2, 0);

      // STEPS---------------------------------------------------------------------------------------------------------------------------------
      
      //STEPS IMAGE
      img_steps = lv_img_create(cont, nullptr);
      lv_img_set_src(img_steps, &IsymbolFootIcon);
      lv_obj_align(img_steps, nullptr, LV_ALIGN_IN_TOP_MID, 20, 0);

      //STEPS TEXT
      label_steps = lv_label_create(cont, nullptr);
      lv_label_set_text_fmt(label_steps, "%i", accl_data.steps);
      lv_obj_align(label_steps, img_steps, LV_ALIGN_OUT_RIGHT_MID, 2, 0);

      //DATE TIME ##############################################################################################################
      //TIME TEXT
      label_time = lv_label_create(lv_scr_act(), nullptr);
      lv_label_set_text_fmt(label_time,  "%02i:%02i", ztime, time_data.min);
      lv_obj_set_style( label_time, &style_time );
      lv_obj_align(label_time, nullptr, LV_ALIGN_IN_TOP_RIGHT, -5, 25); //top right time
      //lv_obj_align(label_time, nullptr, LV_ALIGN_CENTER, 0, 0);

      //DATE TEXT
      label_date = lv_label_create(lv_scr_act(), nullptr);
      lv_label_set_text_fmt(label_date, "%s, %s %02i", string2char(weekday), string2char(month), time_data.day);
      lv_obj_align(label_date, label_time, LV_ALIGN_OUT_BOTTOM_MID, 0, -13);

      #endif
    }
    
  
 
    //get+update datetime data
    virtual void getHomeScreenData(){
        accl_data = get_accl_data();
        time_data = get_time();
        weekday = getDayString();
        month = getMonthString();
        ztime = get12hrTime();
    }

    //----------------------------------------------------------------------------------------------------------------------------------------
  

    virtual void updateFace(){
        //UPDATE TIME
        lv_label_set_text_fmt(label_time,  "%02i:%02i", ztime, time_data.min);
        lv_obj_realign(label_time);

        //UPDATE DATE
        lv_label_set_text_fmt(label_date, "%s, %s %02i", string2char(weekday), string2char(month), time_data.day);
        lv_obj_realign(label_date);

        //UPDATE BATTERY TEXT
        lv_label_set_text_fmt(label_battery, "%i%%", get_battery_percent());
      
        //UPDATE BATTERY ICON
        if (get_battery_percent() < 15) lv_label_set_text(label_battery_icon, LV_SYMBOL_BATTERY_EMPTY);
        else if (get_battery_percent() > 75) lv_label_set_text(label_battery_icon, LV_SYMBOL_BATTERY_FULL);
        else lv_label_set_text(label_battery_icon, LV_SYMBOL_BATTERY_2);
  
        // COLOR AND CHANGE BATTERY ICON
        if (get_battery_percent() < 15) style_battery.text.color = LV_COLOR_RED;
        else
          style_battery.text.color = LV_COLOR_MAKE(0x05, 0xF9, 0x25);
        lv_obj_set_style(label_battery_icon, &style_battery);
        
        //UPDATE HEARTREATE TEXT
        //lv_label_set_text_fmt(label_heart, "%i", get_last_heartrate());

        // UPDATE STEPS
        //lv_label_set_text_fmt(label_steps, "%i", accl_data.steps);
     
        //UPDATE BLUETOOTH CONNECTION ICON
        if (get_vars_ble_connected())
          style_ble.text.color = LV_COLOR_MAKE(0x27, 0xA6, 0xFF);
        else
          style_ble.text.color = LV_COLOR_RED;
        lv_obj_set_style(label_ble, &style_ble);

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

    //Time
    int ztime;
    time_data_struct time_data;
    lv_obj_t *label_time;
    //Date
    String weekday;
    String month;
    lv_obj_t *label_date;
    //Steps
    accl_data_struct accl_data;
    lv_obj_t *img_steps, *label_steps;
    //HeartRate
    lv_obj_t * img_heart, *label_heart;
    //Battery
    lv_obj_t  *label_battery, *label_battery_icon;
    //Other    
    lv_obj_t *label_ble, *cont, *img1;
    //Styles
    lv_style_t style_ble, style_battery,
    style_time, style_battery_text, 
    stBar, style_date;

    char* string2char(String command) {
      if (command.length() != 0) {
        char *p = const_cast<char*>(command.c_str());
        return p;
      }
    }
};

HomeScreen homeScreen;
