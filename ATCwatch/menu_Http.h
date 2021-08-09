

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
      label_screen = lv_label_create(lv_scr_act(), NULL);
      lv_label_set_text(label_screen, "HTTP Demo");
      lv_obj_align(label_screen, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 0);

      label_http_req = lv_label_create(lv_scr_act(), NULL);
      lv_label_set_text_fmt(label_http_req, "HTTP:%s", string2char(get_http_msg()));
      lv_obj_align(label_http_req, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 10);

      btn1 = lv_btn_create(lv_scr_act(), NULL);
      lv_obj_set_event_cb(btn1, lv_event_handler);
      lv_obj_align(btn1, NULL, LV_ALIGN_CENTER, -55, -45);
      btn1_label = lv_label_create(btn1, NULL);
      lv_label_set_text(btn1_label, "Block");

      btn2 = lv_btn_create(lv_scr_act(), NULL);
      lv_obj_set_event_cb(btn2, lv_event_handler);
      lv_obj_align(btn2, NULL, LV_ALIGN_CENTER, 55, -45);
      btn2_label = lv_label_create(btn2, NULL);
      lv_label_set_text(btn2_label, "Mario");

      btn3 = lv_btn_create(lv_scr_act(), NULL);
      lv_obj_set_event_cb(btn3, lv_event_handler);
      lv_obj_align(btn3, NULL, LV_ALIGN_CENTER, -55, 45);
      btn3_label = lv_label_create(btn3, NULL);
      lv_label_set_text(btn3_label, "Link");

      btn4 = lv_btn_create(lv_scr_act(), NULL);
      lv_obj_set_event_cb(btn4, lv_event_handler);
      lv_obj_align(btn4, NULL, LV_ALIGN_CENTER, 55, 45);
      btn4_label = lv_label_create(btn4, NULL);
      lv_label_set_text(btn4_label, "OFF");

    }

    virtual void main()
    {
      lv_label_set_text_fmt(label_http_req, "%s", string2char(get_http_msg()));
      lv_obj_align(label_http_req, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 10);
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
      if (object == btn1 && event == LV_EVENT_SHORT_CLICKED) {
        ble_write("AT+HTTP:?BLOCK=ON");
        } else if (object == btn2 && event == LV_EVENT_SHORT_CLICKED) {
        ble_write("AT+HTTP:?MARIO=ON");
        } else if (object == btn3 && event == LV_EVENT_SHORT_CLICKED) {
        ble_write("AT+HTTP:?LINK=ON");
        } else if (object == btn4 && event == LV_EVENT_SHORT_CLICKED) {
        ble_write("AT+HTTP:?LED=OFF");
        }
      
    }
    

  private:
    lv_obj_t *label_screen, *label_http_req;
    lv_obj_t *btn1, *btn1_label, *btn2, *btn2_label, *btn3, *btn3_label, *btn4, *btn4_label;

    char* string2char(String command) {
      if (command.length() != 0) {
        char *p = const_cast<char*>(command.c_str());
        return p;
      }
    }
};

HttpScreen httpScreen;
