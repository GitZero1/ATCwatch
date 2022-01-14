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
//#include "screen_style.h"
#include <lvgl.h>

struct app_struct {
  const char* _title;
  Screen* _screen;
};

class AppScreen : public Screen
{
  public:
    AppScreen(int menuPosition, int maxApps, app_struct* app1, app_struct* app2, app_struct* app3, app_struct* app4)
    {
      _menuPosition = menuPosition;
      _maxApps = maxApps;
      _app1 = app1;
      _app2 = app2;
      _app3 = app3;
      _app4 = app4;
    }

    virtual void pre()
    {
      
      accl_data = get_accl_data();
      #ifdef SN80
      //#ifdef PineTime
      label = lv_label_create(lv_scr_act(), NULL);
      lv_label_set_text_fmt(label, "%i/%i", _menuPosition, _maxApps);
      lv_obj_align(label, NULL, LV_ALIGN_IN_TOP_MID, 0, 10);
      //top left button
      app1_btn = lv_btn_create(lv_scr_act(), NULL); 
      lv_obj_set_height(app1_btn,60);
      lv_obj_set_width(app1_btn,75);
      lv_obj_align(app1_btn, NULL, LV_ALIGN_CENTER, -40, -45);
      lv_obj_set_event_cb(app1_btn, lv_event_handler);
      btn_label = lv_label_create(app1_btn, NULL);
      lv_label_set_text(btn_label, _app1->_title);
      //top right button
      app2_btn = lv_btn_create(lv_scr_act(), NULL);
      lv_obj_set_height(app2_btn,60);
      lv_obj_set_width(app2_btn,75);
      lv_obj_align(app2_btn, NULL, LV_ALIGN_CENTER, 40, -45);
      lv_obj_set_event_cb(app2_btn, lv_event_handler);
      btn_label = lv_label_create(app2_btn, NULL);
      lv_label_set_text(btn_label, _app2->_title);
      // bottom left button
      app3_btn = lv_btn_create(lv_scr_act(), NULL);
      lv_obj_set_height(app3_btn,60);
      lv_obj_set_width(app3_btn,75);
      lv_obj_align(app3_btn, NULL, LV_ALIGN_CENTER, -40, 22);
      lv_obj_set_event_cb(app3_btn, lv_event_handler);
      btn_label = lv_label_create(app3_btn, NULL);
      lv_label_set_text(btn_label, _app3->_title);
      //bottom right button
      app4_btn = lv_btn_create(lv_scr_act(), NULL);
      lv_obj_set_height(app4_btn,60);
      lv_obj_set_width(app4_btn,75);
      lv_obj_align(app4_btn, NULL, LV_ALIGN_CENTER, 40, 22);
      lv_obj_set_event_cb(app4_btn, lv_event_handler);
      btn_label = lv_label_create(app4_btn, NULL);
      lv_label_set_text(btn_label, _app4->_title);

            //Heartrate -----------------------------------------------------------------------------------------------------------------------------
      
      //HEART ICON      
      img_heart = lv_img_create(lv_scr_act(), nullptr);  
      lv_img_set_src(img_heart, &IsymbolHeartIcon);
      lv_obj_align(img_heart, nullptr, LV_ALIGN_CENTER, -55, 65);
      
      //HEART TEXT
      label_heart = lv_label_create(lv_scr_act(), nullptr);
      lv_label_set_text_fmt(label_heart, "%i", get_last_heartrate());
      lv_obj_align(label_heart, img_heart, LV_ALIGN_OUT_RIGHT_MID, 2, 0);
      
      // STEPS---------------------------------------------------------------------------------------------------------------------------------
      
      //STEPS IMAGE
      img_steps = lv_img_create(lv_scr_act(), nullptr);
      lv_img_set_src(img_steps, &IsymbolFootIcon);
      lv_obj_align(img_steps, nullptr, LV_ALIGN_CENTER, 5, 65);

      //STEPS TEXT
      label_steps = lv_label_create(lv_scr_act(), nullptr);
      lv_label_set_text_fmt(label_steps, "%i", accl_data.steps);
      lv_obj_align(label_steps, img_steps, LV_ALIGN_OUT_RIGHT_MID, 2, 0);

      #else

      label = lv_label_create(lv_scr_act(), NULL);
      lv_label_set_text_fmt(label, "%i/%i", _menuPosition, _maxApps);
      lv_obj_align(label, NULL, LV_ALIGN_IN_TOP_MID, 0, 10);
      //top left button
      app1_btn = lv_btn_create(lv_scr_act(), NULL); 
      lv_obj_align(app1_btn, NULL, LV_ALIGN_CENTER, -55, -40);
      lv_obj_set_event_cb(app1_btn, lv_event_handler);
      btn_label = lv_label_create(app1_btn, NULL);
      lv_label_set_text(btn_label, _app1->_title);
      //top right button
      app2_btn = lv_btn_create(lv_scr_act(), NULL);
      lv_obj_align(app2_btn, NULL, LV_ALIGN_CENTER, 55, -40);
      lv_obj_set_event_cb(app2_btn, lv_event_handler);
      btn_label = lv_label_create(app2_btn, NULL);
      lv_label_set_text(btn_label, _app2->_title);
      // bottom left button
      app3_btn = lv_btn_create(lv_scr_act(), NULL);
      lv_obj_align(app3_btn, NULL, LV_ALIGN_CENTER, -55, 40);
      lv_obj_set_event_cb(app3_btn, lv_event_handler);
      btn_label = lv_label_create(app3_btn, NULL);
      lv_label_set_text(btn_label, _app3->_title);
      //bottom right button
      app4_btn = lv_btn_create(lv_scr_act(), NULL);
      lv_obj_align(app4_btn, NULL, LV_ALIGN_CENTER, 55, 40);
      lv_obj_set_event_cb(app4_btn, lv_event_handler);
      btn_label = lv_label_create(app4_btn, NULL);
      lv_label_set_text(btn_label, _app4->_title);

      #endif


    }

    virtual void main()
    {
      accl_data = get_accl_data();
      lv_label_set_text_fmt(label_steps, "%i", accl_data.steps);
      lv_label_set_text_fmt(label_heart, "%i", get_last_heartrate());

    }

    virtual void up()
    {
      inc_vars_menu();
    }

    virtual void down()
    {
      dec_vars_menu();
    }

    virtual void right()
    {
      display_home();
    }

    virtual void lv_event_class(lv_obj_t * object, lv_event_t event)
    {
      if (event == LV_EVENT_SHORT_CLICKED) {
        if (object == app1_btn) {
          change_screen(_app1->_screen);
        } else if (object == app2_btn) {
          change_screen(_app2->_screen);
        } else if (object == app3_btn) {
          change_screen(_app3->_screen);
        } else if (object == app4_btn) {
          change_screen(_app4->_screen);
        }
      }
    }

  private:
    app_struct* _app1;
    app_struct* _app2;
    app_struct* _app3;
    app_struct* _app4;
    lv_obj_t *app1_btn, *app2_btn, *app3_btn, *app4_btn, *btn_label, *slider, *label;
    uint32_t _menuPosition, _maxApps;

    //Steps
    accl_data_struct accl_data;
    lv_obj_t *img_steps, *label_steps;
    //HeartRate
    lv_obj_t * img_heart, *label_heart;

};