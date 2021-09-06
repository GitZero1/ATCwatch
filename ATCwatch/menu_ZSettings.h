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
#include <lvgl.h>

class ZeroSettingsScreen : public Screen
{
  public:
    virtual void pre()
    {
    //set_swipe_enabled(true);

    // CREATE TABVIEW
    tabview = lv_tabview_create(lv_scr_act(), NULL);
    //Add 2 tabs (the tabs are page (lv_page) and can be scrolled
    tab1 = lv_tabview_add_tab(tabview, "Main");
    initMainColorTab();
    tab2 = lv_tabview_add_tab(tabview, "Grad");
    initGradColorTab();
    //tab3 = lv_tabview_add_tab(tabview, "Font");
    //initFontColorTab();
    }


    virtual void main()
    {


    }


    void initMainColorTab(void)
    {
        // Main color White btn
        mWhiteBtn = lv_btn_create(tab1, NULL);
        lv_obj_align(mWhiteBtn, NULL, LV_ALIGN_IN_TOP_LEFT, 0,0);
        lv_obj_set_event_cb(mWhiteBtn, lv_event_handler);
        lv_btn_set_fit2(mWhiteBtn, LV_FIT_TIGHT, LV_FIT_TIGHT);
        cBtnLabel = lv_label_create(mWhiteBtn, NULL);
        lv_label_set_text(cBtnLabel, "White");
        // Black
        mBlackBtn = lv_btn_create(tab1, NULL);
        lv_obj_align(mBlackBtn, NULL, LV_ALIGN_IN_TOP_LEFT, 0,50);
        lv_obj_set_event_cb(mBlackBtn, lv_event_handler);
        lv_btn_set_fit2(mBlackBtn, LV_FIT_TIGHT, LV_FIT_TIGHT);
        cBtnLabel = lv_label_create(mBlackBtn, NULL);
        lv_label_set_text(cBtnLabel, "Black");
        //Gray
        mGrayBtn = lv_btn_create(tab1, NULL);
        lv_obj_align(mGrayBtn, NULL, LV_ALIGN_IN_TOP_LEFT, 0,100);
        lv_obj_set_event_cb(mGrayBtn, lv_event_handler);
        lv_btn_set_fit2(mGrayBtn, LV_FIT_TIGHT, LV_FIT_TIGHT);
        cBtnLabel = lv_label_create(mGrayBtn, NULL);
        lv_label_set_text(cBtnLabel, "Gray");
        //Red
        mRedBtn = lv_btn_create(tab1, NULL);
        lv_obj_align(mRedBtn, mWhiteBtn, LV_ALIGN_OUT_RIGHT_MID, 5,0);
        lv_obj_set_event_cb(mRedBtn, lv_event_handler);
        lv_btn_set_fit2(mRedBtn, LV_FIT_TIGHT, LV_FIT_TIGHT);
        cBtnLabel = lv_label_create(mRedBtn, NULL);
        lv_label_set_text(cBtnLabel, "Red");
        //Green
        mGreenBtn = lv_btn_create(tab1, NULL);
        lv_obj_align(mGreenBtn, mBlackBtn, LV_ALIGN_OUT_RIGHT_MID, 5,0);
        lv_obj_set_event_cb(mGreenBtn, lv_event_handler);
        lv_btn_set_fit2(mGreenBtn, LV_FIT_TIGHT, LV_FIT_TIGHT);
        cBtnLabel = lv_label_create(mGreenBtn, NULL);
        lv_label_set_text(cBtnLabel, "Green");
        //Blue
        mBlueBtn = lv_btn_create(tab1, NULL);
        lv_obj_align(mBlueBtn, mGrayBtn, LV_ALIGN_OUT_RIGHT_MID, 5,0);
        lv_obj_set_event_cb(mBlueBtn, lv_event_handler);
        lv_btn_set_fit2(mBlueBtn, LV_FIT_TIGHT, LV_FIT_TIGHT);
        cBtnLabel = lv_label_create(mBlueBtn, NULL);
        lv_label_set_text(cBtnLabel, "Blue");      
    }

    void initGradColorTab(void)
    {
        // Main color White btn
        gWhiteBtn = lv_btn_create(tab2, NULL);
        lv_obj_align(gWhiteBtn, NULL, LV_ALIGN_IN_TOP_LEFT, 0,0);
        lv_obj_set_event_cb(gWhiteBtn, lv_event_handler);
        lv_btn_set_fit2(gWhiteBtn, LV_FIT_TIGHT, LV_FIT_TIGHT);
        cBtnLabel = lv_label_create(gWhiteBtn, NULL);
        lv_label_set_text(cBtnLabel, "White");
        // Black
        gBlackBtn = lv_btn_create(tab2, NULL);
        lv_obj_align(gBlackBtn, NULL, LV_ALIGN_IN_TOP_LEFT, 0,50);
        lv_obj_set_event_cb(gBlackBtn, lv_event_handler);
        lv_btn_set_fit2(gBlackBtn, LV_FIT_TIGHT, LV_FIT_TIGHT);
        cBtnLabel = lv_label_create(gBlackBtn, NULL);
        lv_label_set_text(cBtnLabel, "Black");
        //Gray
        gGrayBtn = lv_btn_create(tab2, NULL);
        lv_obj_align(gGrayBtn, NULL, LV_ALIGN_IN_TOP_LEFT, 0,100);
        lv_obj_set_event_cb(gGrayBtn, lv_event_handler);
        lv_btn_set_fit2(gGrayBtn, LV_FIT_TIGHT, LV_FIT_TIGHT);
        cBtnLabel = lv_label_create(gGrayBtn, NULL);
        lv_label_set_text(cBtnLabel, "Gray");
        //Red
        gRedBtn = lv_btn_create(tab2, NULL);
        lv_obj_align(gRedBtn, gWhiteBtn, LV_ALIGN_OUT_RIGHT_MID, 5,0);
        lv_obj_set_event_cb(gRedBtn, lv_event_handler);
        lv_btn_set_fit2(gRedBtn, LV_FIT_TIGHT, LV_FIT_TIGHT);
        cBtnLabel = lv_label_create(gRedBtn, NULL);
        lv_label_set_text(cBtnLabel, "Red");
        //Green
        gGreenBtn = lv_btn_create(tab2, NULL);
        lv_obj_align(gGreenBtn, gBlackBtn, LV_ALIGN_OUT_RIGHT_MID, 5,0);
        lv_obj_set_event_cb(gGreenBtn, lv_event_handler);
        lv_btn_set_fit2(gGreenBtn, LV_FIT_TIGHT, LV_FIT_TIGHT);
        cBtnLabel = lv_label_create(gGreenBtn, NULL);
        lv_label_set_text(cBtnLabel, "Green");
        //Blue
        gBlueBtn = lv_btn_create(tab2, NULL);
        lv_obj_align(gBlueBtn, gGrayBtn, LV_ALIGN_OUT_RIGHT_MID, 5,0);
        lv_obj_set_event_cb(gBlueBtn, lv_event_handler);
        lv_btn_set_fit2(gBlueBtn, LV_FIT_TIGHT, LV_FIT_TIGHT);
        cBtnLabel = lv_label_create(gBlueBtn, NULL);
        lv_label_set_text(cBtnLabel, "Blue");      
    }

    void initFontColorTab(void)
    {
        // Main color White btn
        tWhiteBtn = lv_btn_create(tab3, NULL);
        lv_obj_align(tWhiteBtn, NULL, LV_ALIGN_IN_TOP_LEFT, 0,0);
        lv_obj_set_event_cb(tWhiteBtn, lv_event_handler);
        lv_btn_set_fit2(tWhiteBtn, LV_FIT_TIGHT, LV_FIT_TIGHT);
        cBtnLabel = lv_label_create(tWhiteBtn, NULL);
        lv_label_set_text(cBtnLabel, "White");
        // Black
        tBlackBtn = lv_btn_create(tab3, NULL);
        lv_obj_align(tBlackBtn, NULL, LV_ALIGN_IN_TOP_LEFT, 0,50);
        lv_obj_set_event_cb(tBlackBtn, lv_event_handler);
        lv_btn_set_fit2(tBlackBtn, LV_FIT_TIGHT, LV_FIT_TIGHT);
        cBtnLabel = lv_label_create(tBlackBtn, NULL);
        lv_label_set_text(cBtnLabel, "Black");
        //Gray
        tGrayBtn = lv_btn_create(tab3, NULL);
        lv_obj_align(tGrayBtn, NULL, LV_ALIGN_IN_TOP_LEFT, 0,100);
        lv_obj_set_event_cb(tGrayBtn, lv_event_handler);
        lv_btn_set_fit2(tGrayBtn, LV_FIT_TIGHT, LV_FIT_TIGHT);
        cBtnLabel = lv_label_create(tGrayBtn, NULL);
        lv_label_set_text(cBtnLabel, "Gray");
        //Red
        tRedBtn = lv_btn_create(tab3, NULL);
        lv_obj_align(tRedBtn, tWhiteBtn, LV_ALIGN_OUT_RIGHT_MID, 5,0);
        lv_obj_set_event_cb(tRedBtn, lv_event_handler);
        lv_btn_set_fit2(tRedBtn, LV_FIT_TIGHT, LV_FIT_TIGHT);
        cBtnLabel = lv_label_create(tRedBtn, NULL);
        lv_label_set_text(cBtnLabel, "Red");
        //Green
        tGreenBtn = lv_btn_create(tab3, NULL);
        lv_obj_align(tGreenBtn, tBlackBtn, LV_ALIGN_OUT_RIGHT_MID, 5,0);
        lv_obj_set_event_cb(tGreenBtn, lv_event_handler);
        lv_btn_set_fit2(tGreenBtn, LV_FIT_TIGHT, LV_FIT_TIGHT);
        cBtnLabel = lv_label_create(tGreenBtn, NULL);
        lv_label_set_text(cBtnLabel, "Green");
        //Blue
        tBlueBtn = lv_btn_create(tab3, NULL);
        lv_obj_align(tBlueBtn, tGrayBtn, LV_ALIGN_OUT_RIGHT_MID, 5,0);
        lv_obj_set_event_cb(tBlueBtn, lv_event_handler);
        lv_btn_set_fit2(tBlueBtn, LV_FIT_TIGHT, LV_FIT_TIGHT);
        cBtnLabel = lv_label_create(tBlueBtn, NULL);
        lv_label_set_text(cBtnLabel, "Blue");      
    }

    virtual void lv_event_class(lv_obj_t * object, lv_event_t event)
    {

      if(event == LV_EVENT_SHORT_CLICKED){
        if (object == mWhiteBtn){ //main color
          set_main_color(0);
          set_gray_screen_style();
        } else if (object == mGrayBtn){
          set_main_color(1);
          set_gray_screen_style();
        } else if (object == mBlackBtn){
          set_main_color(2);
          set_gray_screen_style();
        } else if (object == mRedBtn){
          set_main_color(3);
          set_gray_screen_style();
        } else if (object == mGreenBtn){
          set_main_color(4);
          set_gray_screen_style();
        } else if (object == mBlueBtn){
          set_main_color(5);
          set_gray_screen_style();
        } else if (object == gWhiteBtn){ //grad color
          set_grad_color(0);
          set_gray_screen_style();
        } else if (object == gGrayBtn){
          set_grad_color(1);
          set_gray_screen_style();
        } else if (object == gBlackBtn){
          set_grad_color(2);
          set_gray_screen_style();
        } else if (object == gRedBtn){
          set_grad_color(3);
          set_gray_screen_style();
        } else if (object == gGreenBtn){
          set_grad_color(4);
          set_gray_screen_style();
        } else if (object == gBlueBtn){
          set_grad_color(5);
          set_gray_screen_style();
        } else if (object == tWhiteBtn){ //textcolor
          set_font_color(0);
          set_gray_screen_style();
        } else if (object == tGrayBtn){
          set_font_color(1);
          set_gray_screen_style();
        } else if (object == tBlackBtn){
          set_font_color(2);
          set_gray_screen_style();
        } else if (object == tRedBtn){
          set_font_color(3);
          set_gray_screen_style();
        } else if (object == tGreenBtn){
          set_font_color(4);
          set_gray_screen_style();
        } else if (object == tBlueBtn){
          set_font_color(5);
          set_gray_screen_style();
        }

      }
    }

    /*    
    0 = white
    1 = gray
    2 = black
    3 = red
    4 = green
    5 = blue
    6 = green?  
    */


    virtual void up()
    {
    }

    virtual void down()
    {
    }

    virtual void right()
    {
    }

 

  private: 
  lv_style_t st;
  lv_obj_t  *cBtnLabel, *tabview;
  

  //MainColor tab
  lv_obj_t *tab1, *mWhiteBtn, *mGrayBtn, *mBlackBtn, *mRedBtn, *mGreenBtn, *mBlueBtn;

  //MainColor tab
  lv_obj_t  *tab2, *gWhiteBtn, *gGrayBtn, *gBlackBtn, *gRedBtn, *gGreenBtn, *gBlueBtn;

  //TextColor tab
  lv_obj_t  *tab3, *tWhiteBtn, *tGrayBtn, *tBlackBtn, *tRedBtn, *tGreenBtn, *tBlueBtn;
};

ZeroSettingsScreen zeroSettingsScreen;
