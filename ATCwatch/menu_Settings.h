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
#include "menu_Settings_Brightness.h"

//&lv_font_roboto_28

class SettingsScreen : public Screen
{
  public:
    virtual void pre()
    {
      //set_swipe_enabled(true);

      //Create bg style
      static lv_style_t style_bg;
      lv_style_copy( &style_bg, &lv_style_plain );
      style_bg.body.main_color = LV_COLOR_MAKE(0x00, 0x8E, 0xFF);
      style_bg.body.grad_color = LV_COLOR_MAKE(0x00, 0x8E, 0xFF);
      lv_obj_set_style(lv_scr_act(), &style_bg);

      // Button Style
      static lv_style_t style_btn;
      lv_style_copy(&style_btn, &lv_style_plain);
      style_btn.body.main_color = LV_COLOR_WHITE;
      style_btn.body.grad_color = LV_COLOR_WHITE;
      style_btn.body.border.width = 4;
      style_btn.body.border.color = LV_COLOR_BLACK;
      style_btn.text.color = LV_COLOR_BLACK;
      style_btn.body.radius = 10;
      style_btn.text.font = &lv_font_roboto_28;
      
      static lv_style_t style_btn_sel;
      lv_style_copy(&style_btn_sel, &lv_style_plain);
      style_btn_sel.body.main_color = LV_COLOR_BLACK;
      style_btn_sel.body.grad_color = LV_COLOR_BLACK;
      style_btn_sel.body.border.width = 4;
      style_btn_sel.body.border.color = LV_COLOR_GRAY;
      style_btn_sel.text.color = LV_COLOR_WHITE;
      style_btn_sel.body.radius = 10;
      style_btn_sel.text.font = &lv_font_roboto_28;

      


      // CREATE TABVIEW
      lv_obj_t *tabview;
      tabview = lv_tabview_create(lv_scr_act(), NULL);
      lv_obj_align(tabview, nullptr, LV_ALIGN_CENTER, 0, 0);
      lv_tabview_set_style(tabview, LV_TABVIEW_STYLE_BG, &style_bg);
      lv_tabview_set_style(tabview,LV_TABVIEW_STYLE_BTN_TGL_PR, &style_btn_sel);
      lv_tabview_set_style(tabview,LV_TABVIEW_STYLE_BTN_TGL_REL, &style_btn_sel);
      lv_tabview_set_style(tabview,LV_TABVIEW_STYLE_BTN_PR, &style_btn);
      lv_tabview_set_style(tabview,LV_TABVIEW_STYLE_BTN_REL, &style_btn);

      //Add 2 tabs (the tabs are page (lv_page) and can be scrolled
      lv_obj_t *tab1 = lv_tabview_add_tab(tabview, "Power");
      lv_obj_t *tab2 = lv_tabview_add_tab(tabview, "Style");
      lv_obj_set_style(tab1, &style_btn);
      lv_obj_set_style(tab2, &style_btn);

      //TAB ONE ###########################################################
      

      //power button
      pwr_btn = lv_btn_create(tab1, nullptr); //create button
      lv_obj_set_height(pwr_btn,45); //set button height
      lv_btn_set_fit2(pwr_btn,LV_FIT_FILL, LV_FIT_NONE); //set button width
      lv_obj_align(pwr_btn, tab1, LV_ALIGN_CENTER, 0, -50); //set button location
      pwr_btn_label = lv_label_create(pwr_btn, nullptr); //create button label
      lv_label_set_text(pwr_btn_label,"Power"); //set button label text
      set_btn_style(pwr_btn); //set button style
      lv_obj_set_event_cb(pwr_btn, lv_event_handler); //set event handler


      //Reboot Button
      reboot_btn = lv_btn_create(tab1, nullptr);  //create button
      lv_obj_set_height(reboot_btn,45); //set button height
      lv_btn_set_fit2(reboot_btn,LV_FIT_FILL, LV_FIT_NONE); //set button width
      lv_obj_align(reboot_btn, tab1, LV_ALIGN_CENTER, 0, 0); //set button location
      reboot_btn_label = lv_label_create(reboot_btn, nullptr); //create button label
      lv_label_set_text(reboot_btn_label,"Reboot"); //set button label text
      set_btn_style(reboot_btn);  //set button style
      lv_obj_set_event_cb(reboot_btn, lv_event_handler); //set event handler

      // BootLoader Button
      bootload_btn = lv_btn_create(tab1, nullptr);  //create button
      lv_obj_set_height(bootload_btn,45); //set button height
      lv_btn_set_fit2(bootload_btn,LV_FIT_FILL, LV_FIT_NONE); //set button width
      lv_obj_align(bootload_btn, tab1, LV_ALIGN_CENTER, 0, 50); //set button location
      bootload_btn_label = lv_label_create(bootload_btn, nullptr); //create button label
      lv_label_set_text(bootload_btn_label,"Bootloader"); //set button label text
      set_btn_style(bootload_btn);  //set button style
      lv_obj_set_event_cb(bootload_btn, lv_event_handler); //set event handler


      // TAB TWO #########################################################

      

      //sample button
      sample_btn = lv_btn_create(tab2, nullptr); //create button
      lv_obj_set_height(sample_btn,45); //set button height
      lv_btn_set_fit2(sample_btn,LV_FIT_FILL, LV_FIT_NONE); //set button width
      lv_obj_align(sample_btn, tab2, LV_ALIGN_CENTER, 0, -50); //set button location
      sample_btn_label = lv_label_create(sample_btn, nullptr); //create button label
      lv_label_set_text(sample_btn_label,"Sample"); //set button label text
      set_btn_style(sample_btn); //set button style
      lv_obj_set_event_cb(sample_btn, lv_event_handler); //set event handler

      //TODO add buttons to select color options and brightness
      // with apply and cancel as well. 
      
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
      display_home();
    }
    
    virtual void lv_event_class(lv_obj_t * object, lv_event_t event)
    {
      if (event == LV_EVENT_SHORT_CLICKED) {
        if(object == reboot_btn){change_screen((Screen*)&rebootScreen);}
        else if(object == pwr_btn){change_screen((Screen*)&offScreen);}
        else if(object == bootload_btn){change_screen((Screen*)&updateScreen);}
        //else if(object == "Style"){change_screen((Screen*)&settingsColorScreen);}
        //else if(object == "Brightness"){change_screen((Screen*)&settingsBrightnessScreen);}
        
      }
    }

  private:
  //tab1 btns
  lv_obj_t *reboot_btn, *pwr_btn, *bootload_btn;
  //tab1 labels
  lv_obj_t *pwr_btn_label, *reboot_btn_label, *bootload_btn_label;

  //tab2 btns
  lv_obj_t *sample_btn, *left_btn, *right_btn;
  //tab2 labels
  lv_obj_t *sample_btn_label;
};

SettingsScreen settingsScreen;
