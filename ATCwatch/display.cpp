/*
 * Copyright (c) 2020 Aaron Christophel
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "display.h"

#include <lvgl.h>
#include "fast_spi.h"
#include "images.h"
#include "battery.h"
#include "touch.h"
#include "accl.h"
#include "menu.h"
#include "ble.h"
#include "heartrate.h"
#include "backlight.h"
#include "inputoutput.h"
#include "bootloader.h"
#include "time.h"
#include "push.h"

#define buffer_lcd_size LV_HOR_RES_MAX * 30
static lv_disp_buf_t disp_buf;
static lv_color_t buf[buffer_lcd_size];

void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p)
{
  uint32_t w = (area->x2 - area->x1 + 1);
  uint32_t h = (area->y2 - area->y1 + 1);
  startWrite_display();
  setAddrWindowDisplay(area->x1, area->y1, w, h);
  write_fast_spi(reinterpret_cast<const uint8_t *>(color_p), (w * h * 2));
  endWrite_display();
  lv_disp_flush_ready(disp);
}

bool my_touchpad_read(lv_indev_drv_t * indev_driver, lv_indev_data_t * data)
{
  bool touched = false;
  touch_data_struct touch_data;
  if (swipe_enabled()) {
    get_read_touch();
    touch_data = get_touch();
    touched = (touch_data.event == 2) ? LV_INDEV_STATE_PR : LV_INDEV_STATE_REL;
    get_new_touch_interrupt();
  } else {
    if (get_new_touch_interrupt()) {
      touch_data = get_touch();
      touched = (touch_data.gesture == TOUCH_SINGLE_CLICK) ? LV_INDEV_STATE_PR : LV_INDEV_STATE_REL;
    } else {
      touched = LV_INDEV_STATE_REL;
    }
  }
  data->state = touched;
  data->point.x = touch_data.xpos;
  data->point.y = touch_data.ypos;
  return false;
}

void inc_tick() {
  lv_tick_inc(40);
}

void init_display() {
  initDisplay();

  lv_init();
  lv_disp_buf_init(&disp_buf, buf, NULL, buffer_lcd_size);

  lv_disp_drv_t disp_drv;
  lv_disp_drv_init(&disp_drv);
  disp_drv.hor_res = 240;
  disp_drv.ver_res = 240;
  disp_drv.flush_cb = my_disp_flush;
  disp_drv.buffer = &disp_buf;
  lv_disp_drv_register(&disp_drv);

  lv_indev_drv_t indev_drv;
  lv_indev_drv_init(&indev_drv);
  indev_drv.type = LV_INDEV_TYPE_POINTER;
  indev_drv.read_cb = my_touchpad_read;

  lv_indev_drv_register(&indev_drv);

  lv_theme_t *th = lv_theme_night_init(10, NULL);
  lv_theme_set_current(th);
}

void display_enable(bool state) {
  uint8_t temp[2];
  startWrite_display();
  if (state) {
    spiCommand(ST77XX_DISPON);
    spiCommand(ST77XX_SLPOUT);
  } else {
    spiCommand(ST77XX_SLPIN);
    spiCommand(ST77XX_DISPOFF);
  }
  endWrite_display();
}

void setAddrWindowDisplay(uint32_t x, uint32_t y, uint32_t w, uint32_t h)
{
  uint8_t temp[4];
  //y += 80; // when rotated screen
  spiCommand(0x2A);
  temp[0] = (x >> 8);
  temp[1] = x;
  temp[2] = ((x + w - 1) >> 8);
  temp[3] = (x + w - 1);
  write_fast_spi(temp, 4);
  spiCommand(0x2B);
  temp[0] = (y >> 8 );
  temp[1] = y;
  temp[2] = ((y + h - 1) >> 8);
  temp[3] = ((y + h - 1) & 0xFF);
  write_fast_spi(temp, 4);
  spiCommand(0x2C);
}


#ifdef SN80 //SN80 Display Init
void initDisplay() {
  uint8_t temp[25];
  pinMode(LCD_CS, OUTPUT);
  pinMode(LCD_RS, OUTPUT);
  pinMode(LCD_RESET, OUTPUT);
  pinMode(LCD_DET, OUTPUT);

  digitalWrite(LCD_CS , HIGH);
  digitalWrite(LCD_RS , HIGH);

  digitalWrite(LCD_RESET, HIGH);
  delay(20);
  digitalWrite(LCD_RESET, LOW);
  delay(100);
  digitalWrite(LCD_RESET, HIGH);
  delay(100);
  startWrite_display();

/** begin **/

  spiCommand(-2);
  spiCommand(-17);
  spiCommand(-21);
  temp[0] = 2;
  write_fast_spi(temp, 1);
  spiCommand(-124);
  temp[0] = 64;
  write_fast_spi(temp, 1);
  spiCommand(-123);
  temp[0] = -15;
  write_fast_spi(temp, 1);
  spiCommand(-122);
  temp[0] = -104;
  write_fast_spi(temp, 1);
  spiCommand(-121);
  temp[0] = 40;
  write_fast_spi(temp, 1);
  spiCommand(-120);
  temp[0] = 10;
  write_fast_spi(temp, 1);
  spiCommand(-118);
  temp[0] = 0;
  write_fast_spi(temp, 1);
  spiCommand(-117);
  temp[0] = -128;
  write_fast_spi(temp, 1);
  spiCommand(-116);
  temp[0] = 1;
  write_fast_spi(temp, 1);
  spiCommand(-115);
  temp[0] = 0;
  write_fast_spi(temp, 1);
  spiCommand(-114);
  temp[0] = -33;
  write_fast_spi(temp, 1);
  spiCommand(-113);
  temp[0] = 82;
  write_fast_spi(temp, 1);
  spiCommand(-74);
  temp[0] = 32;
  write_fast_spi(temp, 1);
  spiCommand(54);
  temp[0] = 72;
  write_fast_spi(temp, 1);
  spiCommand(58);
  temp[0] = 5;
  write_fast_spi(temp, 1);
  spiCommand(-112);
  temp[0] = 8;
  temp[1] = 8;
  temp[2] = 8;
  temp[3] = 8;
  write_fast_spi(temp, 4);
  spiCommand(-67);
  temp[0] = 6;
  write_fast_spi(temp, 1);
  spiCommand(-90);
  temp[0] = 116;
  write_fast_spi(temp, 1);
  spiCommand(-65);
  temp[0] = 28;
  write_fast_spi(temp, 1);
  spiCommand(-89);
  temp[0] = 69;
  write_fast_spi(temp, 1);
  spiCommand(-87);
  temp[0] = -69;
  write_fast_spi(temp, 1);
  spiCommand(-72);
  temp[0] = 99;
  write_fast_spi(temp, 1);
  spiCommand(-68);
  temp[0] = 0;
  write_fast_spi(temp, 1);
  spiCommand(-1);
  temp[0] = 96;
  temp[1] = 1;
  temp[2] = 4;
  write_fast_spi(temp, 3);
  spiCommand(-61);
  temp[0] = 23;
  write_fast_spi(temp, 1);
  spiCommand(-60);
  temp[0] = 23;
  write_fast_spi(temp, 1);
  spiCommand(-55);
  temp[0] = 37;
  write_fast_spi(temp, 1);
  spiCommand(-66);
  temp[0] = 17;
  write_fast_spi(temp, 1);
  spiCommand(-31);
  temp[0] = 16;
  temp[1] = 14;
  write_fast_spi(temp, 2);
  spiCommand(-33);
  temp[0] = 33;
  temp[1] = 16;
  temp[2] = 2;
  write_fast_spi(temp, 3);
  spiCommand(-16);
  temp[3] = 8;
  temp[4] = 38;
  temp[0] = 69;
  temp[1] = 9;
  temp[5] = 42;
  temp[2] = 8;
  write_fast_spi(temp, 6);
  spiCommand(-15);
  temp[0] = 67;
  temp[1] = 112;
  temp[2] = 114;
  temp[3] = 54;
  temp[4] = 55;
  temp[5] = 111;
  write_fast_spi(temp, 6);
  spiCommand(-14);
  temp[3] = 8;
  temp[4] = 38;
  temp[0] = 69;
  temp[1] = 9;
  temp[5] = 42;
  temp[2] = 8;
  write_fast_spi(temp, 6);
  spiCommand(-13);
  temp[0] = 67;
  temp[1] = 112;
  temp[2] = 114;
  temp[3] = 54;
  temp[4] = 55;
  temp[5] = 111;
  write_fast_spi(temp, 6);
  spiCommand(-19);
  temp[0] = 27;
  temp[1] = 11;
  write_fast_spi(temp, 2);
  spiCommand(-84);
  temp[0] = 71;
  write_fast_spi(temp, 1);
  spiCommand(-82);
  temp[0] = 119;
  write_fast_spi(temp, 1);
  spiCommand(-53);
  temp[0] = 2;
  write_fast_spi(temp, 1);
  spiCommand(-51);
  temp[0] = 99;
  write_fast_spi(temp, 1);
  spiCommand(112);
  temp[0] = 7;
  temp[1] = 9;
  temp[2] = 4;
  temp[3] = 14;
  temp[4] = 15;
  temp[5] = 9;
  temp[6] = 7;
  temp[7] = 8;
  temp[8] = 3;
  write_fast_spi(temp, 9);
  spiCommand(-24);
  temp[0] = 52;
  write_fast_spi(temp, 1);
  spiCommand(98);
  temp[0] = 24;
  temp[1] = 13;
  temp[3] = -19;
  temp[7] = 15;
  temp[8] = 113;
  temp[4] = 112;
  temp[9] = -17;
  temp[5] = 112;
  temp[2] = 113;
  temp[6] = 24;
  temp[10] = 112;
  temp[11] = 112;
  write_fast_spi(temp, 12);
  spiCommand(99);
  temp[0] = 24;
  temp[1] = 17;
  temp[7] = 19;
  temp[3] = -15;
  temp[8] = 113;
  temp[4] = 112;
  temp[9] = -13;
  temp[5] = 112;
  temp[2] = 113;
  temp[6] = 24;
  temp[10] = 112;
  temp[11] = 112;
  write_fast_spi(temp, 12);
  spiCommand(100);
  temp[0] = 40;
  temp[1] = 41;
  temp[3] = 1;
  temp[4] = -15;
  temp[5] = 0;
  temp[6] = 7;
  temp[2] = -15;
  write_fast_spi(temp, 7);
  spiCommand(102);
  temp[0] = 60;
  temp[1] = 0;
  temp[2] = -51;
  temp[3] = 103;
  temp[4] = 69;
  temp[7] = 0;
  temp[5] = 69;
  temp[8] = 0;
  temp[6] = 16;
  temp[9] = 0;
  write_fast_spi(temp, 10);
  spiCommand(103);
  temp[0] = 0;
  temp[1] = 60;
  temp[3] = 0;
  temp[4] = 0;
  temp[5] = 1;
  temp[6] = 84;
  temp[7] = 16;
  temp[8] = 50;
  temp[9] = -104;
  temp[2] = 0;
  write_fast_spi(temp, 10);
  spiCommand(116);
  temp[0] = 16;
  temp[1] = -128;
  temp[2] = -128;
  temp[3] = 0;
  temp[4] = 0;
  temp[5] = 78;
  temp[6] = 0;
  write_fast_spi(temp, 7);
  spiCommand(53);
  temp[0] = 0;
  write_fast_spi(temp, 1);
  spiCommand(33);
  delay(120);
  spiCommand(17);
  delay(120);
  spiCommand(41);
  delay(120);
  spiCommand(42);
  temp[0] = 0;
  temp[1] = 0;
  temp[3] = -17;
  temp[2] = 0;
  write_fast_spi(temp, 4);
  spiCommand(43);
  temp[0] = 0;
  temp[1] = 0;
  temp[3] = -17;
  temp[2] = 0;
  write_fast_spi(temp, 4);
  spiCommand(44);
/** end **/
  endWrite_display();
}
#else //Standard Square display
void initDisplay() {
  uint8_t temp[25];
  pinMode(LCD_CS, OUTPUT);
  pinMode(LCD_RS, OUTPUT);
  pinMode(LCD_RESET, OUTPUT);
  pinMode(LCD_DET, OUTPUT);

  digitalWrite(LCD_CS , HIGH);
  digitalWrite(LCD_RS , HIGH);

  digitalWrite(LCD_RESET, HIGH);
  delay(20);
  digitalWrite(LCD_RESET, LOW);
  delay(100);
  digitalWrite(LCD_RESET, HIGH);
  delay(100);
  startWrite_display();
  spiCommand(54);
  temp[0] = 0x00;//0xC0 when rotated screen
  write_fast_spi(temp, 1);
  spiCommand(58);
  temp[0] = 5;
  write_fast_spi(temp, 1);
  spiCommand(178);
  temp[0] = 12;
  temp[1] = 12;
  temp[2] = 0;
  temp[3] = 51;
  temp[4] = 51;
  write_fast_spi(temp, 5);
  spiCommand(183);
  temp[0] = 53;
  write_fast_spi(temp, 1);
  spiCommand(187);
  temp[0] = 25;
  write_fast_spi(temp, 1);
  spiCommand(192);
  temp[0] = 44;
  write_fast_spi(temp, 1);
  spiCommand(194);
  temp[0] = 1;
  write_fast_spi(temp, 1);
  spiCommand(195);
  temp[0] = 18;
  write_fast_spi(temp, 1);
  spiCommand(196);
  temp[0] = 32;
  write_fast_spi(temp, 1);
  spiCommand(198);
  temp[0] = 15;
  write_fast_spi(temp, 1);
  spiCommand(208);
  temp[0] = 164;
  temp[1] = 161;
  write_fast_spi(temp, 2);
  spiCommand(224);
  temp[0] = 208;
  temp[1] = 4;
  temp[2] = 13;
  temp[3] = 17;
  temp[4] = 19;
  temp[5] = 43;
  temp[6] = 63;
  temp[7] = 84;
  temp[8] = 76;
  temp[9] = 24;
  temp[10] = 13;
  temp[11] = 11;
  temp[12] = 31;
  temp[13] = 35;
  write_fast_spi(temp, 14);
  spiCommand(225);
  temp[0] = 208;
  temp[1] = 4;
  temp[2] = 12;
  temp[3] = 17;
  temp[4] = 19;
  temp[5] = 44;
  temp[6] = 63;
  temp[7] = 68;
  temp[8] = 81;
  temp[9] = 47;
  temp[10] = 31;
  temp[11] = 31;
  temp[12] = 32;
  temp[13] = 35;
  write_fast_spi(temp, 14);
  spiCommand(33);
  spiCommand(17);
  delay(120);
  spiCommand(41);
  spiCommand(0x11);
  spiCommand(0x29);
  endWrite_display();
}
#endif //SN80/Standard Display Init

void spiCommand(uint8_t d) {
  digitalWrite(LCD_RS , LOW);
  write_fast_spi(&d, 1);
  digitalWrite(LCD_RS , HIGH);
}

void startWrite_display(void) {
  enable_spi(true);
  digitalWrite(LCD_CS , LOW);
}

void endWrite_display(void) {
  digitalWrite(LCD_CS , HIGH);
  enable_spi(false);
}