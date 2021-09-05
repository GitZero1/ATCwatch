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



class SettingsScreen : public Screen
{
  public:
    virtual void pre()
    {
      set_swipe_enabled(true);

      // CREATE TABVIEW
      lv_obj_t *tabview;
      tabview = lv_tabview_create(lv_scr_act(), NULL);

      //Add 2 tabs (the tabs are page (lv_page) and can be scrolled
      lv_obj_t *tab1 = lv_tabview_add_tab(tabview, "Power");
      lv_obj_t *tab2 = lv_tabview_add_tab(tabview, "Style");

      //TAB ONE ###########################################################
      //Create a list in tab 1
      lv_obj_t * list1 = lv_list_create(tab1, NULL);
      lv_obj_set_size(list1, 200, 154);
      lv_obj_align(list1, NULL, LV_ALIGN_CENTER, 0, 0);

      //Add buttons to the list
      lv_obj_t * list_btn;

      //button1
      list_btn = lv_list_add_btn(list1, LV_SYMBOL_REFRESH, "Reboot");
      lv_obj_set_event_cb(list_btn, lv_event_handler);

      //button2
      list_btn = lv_list_add_btn(list1, LV_SYMBOL_POWER, "Off");
      lv_obj_set_event_cb(list_btn, lv_event_handler);

      //button3
      list_btn = lv_list_add_btn(list1, LV_SYMBOL_DOWNLOAD, "Bootloader");
      lv_obj_set_event_cb(list_btn, lv_event_handler);


      // TAB TWO #########################################################
      //Create a list in tab 2
      lv_obj_t * list2 = lv_list_create(tab2, NULL);
      lv_obj_set_size(list2, 200, 154);
      lv_obj_align(list2, NULL, LV_ALIGN_CENTER, 0, 0);

       //button1
      list_btn = lv_list_add_btn(list2, LV_SYMBOL_IMAGE, "Style");
      lv_obj_set_event_cb(list_btn, lv_event_handler);
      
      //button2
      list_btn = lv_list_add_btn(list2, LV_SYMBOL_EYE_OPEN, "Brightness");
      lv_obj_set_event_cb(list_btn, lv_event_handler);

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
        String btnName = lv_list_get_btn_text(object);
        
        if(btnName == "Reboot"){change_screen((Screen*)&rebootScreen);}
        else if(btnName == "Off"){change_screen((Screen*)&offScreen);}
        else if(btnName == "Bootloader"){change_screen((Screen*)&updateScreen);}
        else if(btnName == "Style"){change_screen((Screen*)&settingsColorScreen);}
        else if(btnName == "Brightness"){change_screen((Screen*)&settingsBrightnessScreen);}
        
      }
    }

  private:
  
};

SettingsScreen settingsScreen;
