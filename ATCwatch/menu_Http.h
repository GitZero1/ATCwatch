

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
    String req;
    virtual void pre()
    {
    set_swipe_enabled(true);

    //LABEL
    label = lv_label_create(lv_scr_act(), NULL);
    lv_label_set_text(label, "Test");
    lv_obj_align(label, NULL, LV_ALIGN_CENTER, 0, 35);

    labelReply = lv_label_create(lv_scr_act(), NULL);
    lv_label_set_text_fmt(labelReply, "HTTP:%s", string2char(get_http_msg()));
    lv_obj_align(labelReply, NULL, LV_ALIGN_CENTER, 0, 55);

    //BUTTON 
    btn1 = lv_btn_create(lv_scr_act(), NULL);
    lv_obj_set_event_cb(btn1, lv_event_handler);
    lv_obj_align(btn1, NULL, LV_ALIGN_IN_BOTTOM_MID, 0, -20);
    lv_btn_set_fit2(btn1, LV_FIT_NONE, LV_FIT_TIGHT);
    btn1_label = lv_label_create(btn1, NULL);
    lv_label_set_text(btn1_label, "Send");

    //ROLLER    
    roller1 = lv_roller_create(lv_scr_act(), NULL);
    lv_roller_set_options(roller1,
                        "block\n"
                        "link\n"
                        "mario\n"
                        "qbert\n"
                        "digdug\n"
                        "bombjack\n"
                        "off\n",
                        LV_ROLLER_MODE_NORMAL);

    lv_roller_set_visible_row_count(roller1, 3);
    lv_obj_align(roller1, NULL, LV_ALIGN_CENTER, 0, -30);
    lv_obj_set_event_cb(roller1, event_handler);
    }

    virtual void main()
    {
      lv_label_set_text_fmt(labelReply, string2char(get_http_msg()));
      lv_obj_realign(labelReply);

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

    static void event_handler(lv_obj_t * obj, lv_event_t event)
    {
    if(event == LV_EVENT_VALUE_CHANGED) {
        char buf[32];
        lv_roller_get_selected_str(obj, buf, sizeof(buf));
      }
    }

    virtual void lv_event_class(lv_obj_t * object, lv_event_t event)
    {
      if (object == btn1 && event == LV_EVENT_SHORT_CLICKED) {
        char buf[32];
        lv_roller_get_selected_str(roller1, buf, sizeof(buf));
        lv_label_set_text(label, buf);
        lv_obj_realign(label);
        req = String(buf);
        ble_write("AT+HTTP:"+req);//string2char
      } 
    }

  private: 
  lv_style_t st;
  lv_obj_t *label, *btn1, *btn1_label, *labelReply, *roller1;

  char* string2char(String command) {
      if (command.length() != 0) {
        char *p = const_cast<char*>(command.c_str());
        return p;
      }
    }
};

HttpScreen httpScreen;