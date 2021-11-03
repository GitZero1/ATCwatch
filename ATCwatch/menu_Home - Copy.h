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
      initStyles();
      getHomeScreenData();
      drawBar();



      //DATE TIME ##############################################################################################################
      //TIME TEXT
      label_time = lv_label_create(lv_scr_act(), nullptr);
      lv_label_set_text_fmt(label_time,  "%02i:%02i", ztime, time_data.min);
      lv_obj_set_style( label_time, &st );
      lv_obj_align(label_time, nullptr, LV_ALIGN_IN_TOP_RIGHT, -5, 25);


      //DATE TEXT
      label_date = lv_label_create(lv_scr_act(), nullptr);
      lv_label_set_text_fmt(label_date, "%s, %s %02i", string2char(weekday), string2char(month), time_data.day);
      lv_obj_align(label_date, label_time, LV_ALIGN_OUT_BOTTOM_MID, 0, -13);
      //DATE TIME ##############################################################################################################


      
    }

   
    virtual void main(){
        getHomeScreenData();
        updateFace();
    }

    virtual void sedCheck(){
      if(time_data.min == 00 && time_data.sec == 00){
        
      }
    }

    virtual void drawBar(){

      cont = lv_cont_create(lv_scr_act(), nullptr);
      lv_obj_align(cont, nullptr, LV_ALIGN_IN_TOP_LEFT, 0, 0); 
      lv_obj_set_size(cont, LV_HOR_RES, 20);
      //lv_cont_set_layout(cont, LV_LAYOUT_COL_M);
      lv_obj_set_style(cont, &stBar);

      // BATTERY ICON
      initBatteryIcon();
      //BLUETOOTH ICON
      initBluetoothIcon();
      #ifdef COUNT_STEPS 5 
      //Heartrate
      initHeartData();
      //StepData
      initStepData();
      #endif

    }

    virtual void updateFace(){

        
        //UPDATE TIME
        lv_label_set_text_fmt(label_time,  "%02i:%02i", ztime, time_data.min);
        //UPDATE DATE
        lv_label_set_text_fmt(label_date, "%s, %s %02i", string2char(weekday), string2char(month), time_data.day);
  
        //----------------------------------------------------------------------------------------------------------------------------------------
  
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
        
  
        //----------------------------------------------------------------------------------------------------------------------------------------
        #ifdef COUNT_STEPS 
        //UPDATE HEARTREATE TEXT
        lv_label_set_text_fmt(label_heart, "%i", get_last_heartrate());
        // UPDATE STEPS
        lv_label_set_text_fmt(label_steps, "%i", accl_data.steps);
        #endif
  
      
        //----------------------------------------------------------------------------------------------------------------------------------------
  
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

  
    
    //initializers
    //---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    virtual void initStyles(){
      // STYLE FOR BATTERY TEXT
      lv_style_copy( &st1, &lv_style_plain );
      st1.text.color = LV_COLOR_MAKE(0xFF, 0xFF, 0xFF);
      st1.text.font = &lv_font_roboto_12;

      //FONT AND STYLE FOR TIME
      lv_style_copy( &st, &lv_style_plain );
      //st.text.color = LV_COLOR_MAKE(0xFF, 0xFF, 0xFF);
      st.text.color = LV_COLOR_MAKE(0x00, 0x00, 0x00);
      st.text.font = &mksd50;

      //FONT AND STYLE FOR BAR
      lv_style_copy( &stBar, &lv_style_plain );
      stBar.text.color = LV_COLOR_MAKE(0xFF, 0xFF, 0xFF);
      stBar.body.main_color = lv_color_make(0x00, 0x00, 0x00);
      stBar.body.grad_color = lv_color_make(0x00, 0x00, 0x00);
    }

    void initBatteryIcon(){
      label_battery_icon = lv_label_create(cont, nullptr);
      lv_label_set_text(label_battery_icon, LV_SYMBOL_BATTERY_FULL);
      lv_obj_align(label_battery_icon, nullptr, LV_ALIGN_IN_TOP_LEFT, 2, 1);

      
      // BATTERY TEXT
      label_battery = lv_label_create(cont, nullptr);
      lv_obj_align(label_battery, label_battery_icon, LV_ALIGN_OUT_RIGHT_MID, 3, 2);
      lv_label_set_text_fmt(label_battery, "%i%%", get_battery_percent());
      lv_obj_set_style( label_battery, &st1 );
      
      
      // BATTERY COLOR
      lv_style_copy(&style_battery, lv_label_get_style(label_battery_icon, LV_LABEL_STYLE_MAIN));
      style_battery.text.color = lv_color_hsv_to_rgb(10, 5, 95);
      lv_obj_set_style(label_battery_icon, &style_battery);
    }

    void initBluetoothIcon(){
      label_ble = lv_label_create(cont, nullptr);
      lv_obj_align(label_ble, nullptr, LV_ALIGN_IN_TOP_RIGHT, 0, 0);
      lv_label_set_text(label_ble, LV_SYMBOL_BLUETOOTH);

      //BLUETOOTH COLOR
      lv_style_copy(&style_ble, lv_label_get_style(label_ble, LV_LABEL_STYLE_MAIN));
      style_ble.text.color = LV_COLOR_RED;
      style_ble.text.font = LV_FONT_DEFAULT;
      lv_obj_set_style(label_ble, &style_ble);
    }

    void initHeartData(){
      //HEART ICON      
      img_heart = lv_img_create(cont, nullptr);  
      lv_img_set_src(img_heart, &IsymbolHeartIcon);
      lv_obj_align(img_heart, nullptr, LV_ALIGN_IN_TOP_MID, -50, 2);
      
      //HEART TEXT
      label_heart = lv_label_create(cont, nullptr);
      lv_label_set_text_fmt(label_heart, "%i", get_last_heartrate());
      lv_obj_align(label_heart, img_heart, LV_ALIGN_OUT_RIGHT_MID, 2, 0);
    }
    
    void initStepData(){
    //STEPS IMAGE
      img_steps = lv_img_create(cont, nullptr);
      lv_img_set_src(img_steps, &IsymbolFootIcon);
      lv_obj_align(img_steps, nullptr, LV_ALIGN_IN_TOP_MID, 20, 0);

      //STEPS TEXT
      label_steps = lv_label_create(cont, nullptr);
      lv_label_set_text_fmt(label_steps, "%i", accl_data.steps);
      lv_obj_align(label_steps, img_steps, LV_ALIGN_OUT_RIGHT_MID, 2, 0);
    }
    //---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

    //get+update datetime data
    virtual void getHomeScreenData(){
        accl_data = get_accl_data();
        time_data = get_time();
        weekday = getDayString();
        month = getMonthString();
        ztime = get12hrTime();
    }


  private:
    String weekday;
    String month;
    int ztime;
    time_data_struct time_data;
    accl_data_struct accl_data;
    lv_style_t st, st1, stBar;
    lv_obj_t *label, *label_heart, *label_steps;
    lv_obj_t *label_time, *label_date;
    lv_obj_t *label_ble, *label_battery, *label_battery_icon, *cont;
    lv_style_t style_ble, style_battery;
    lv_obj_t * img_heart, *img_steps, *img1;

    char* string2char(String command) {
      if (command.length() != 0) {
        char *p = const_cast<char*>(command.c_str());
        return p;
      }
    }
};

HomeScreen homeScreen;
