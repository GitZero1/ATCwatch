

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


class HttpScreen : public Screen
{
  public:
    virtual void pre()
    {
      set_swipe_enabled(true);
      
      label = lv_label_create(lv_scr_act(), NULL);
      lv_label_set_text(label, "Test");
      lv_obj_align(label, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 0);

      
      /*Create a list*/
      lv_obj_t * list1 = lv_list_create(lv_scr_act(), NULL);
      lv_obj_set_size(list1, 240, 200);
      lv_obj_align(list1, NULL, LV_ALIGN_IN_BOTTOM_LEFT, 0, 0);

      /*Add buttons to the list*/
      lv_obj_t * list_btn;

      list_btn = lv_list_add_btn(list1, NULL, "block");
      lv_obj_set_event_cb(list_btn, lv_event_handler);

      //list_btn = lv_list_add_btn(list1, NULLDIRECTORY, "Open");
      //lv_obj_set_event_cb(list_btn, lv_event_handler);

      list_btn = lv_list_add_btn(list1, NULL, "mario");
      lv_obj_set_event_cb(list_btn, lv_event_handler);

      list_btn = lv_list_add_btn(list1, NULL, "qbert");
      lv_obj_set_event_cb(list_btn, lv_event_handler);

      list_btn = lv_list_add_btn(list1, NULL, "digdug");
      lv_obj_set_event_cb(list_btn, lv_event_handler);

      list_btn = lv_list_add_btn(list1, NULL, "bombjack");
      lv_obj_set_event_cb(list_btn, lv_event_handler);

      list_btn = lv_list_add_btn(list1, LV_SYMBOL_BATTERY_FULL, "off");
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
    }

    
    virtual void lv_event_class(lv_obj_t * object, lv_event_t event)
    {
      if (event == LV_EVENT_SHORT_CLICKED) {
        lv_label_set_text_fmt(label,"C: %s\n", lv_list_get_btn_text(object));
        //temp = lv_list_get_btn_text(object)
        String bletxt = lv_list_get_btn_text(object);
        ble_write("AT+HTTP:"+bletxt);//string2char
        }
      
    }

    lv_obj_t *label;

  private:
};
HttpScreen httpScreen;
