/*
 * Copyright (c) 2020 Aaron Christophel
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef _PINOUT_
#define _PINOUT_

//Enable or Disable this line to set for Pinetime, P8 Watch, or SN80. more pinouts to added here

#define P8WATCH
//#define PineTime
//#define SN80


#ifdef P8WATCH
//display
#define LCD_SCK      2
#define LCD_SDI      3
#define LCD_CS       25
#define LCD_RESET    26
#define LCD_RS       18
#define LCD_DET      9

//Flash Chip
#define SPI_SCK      2
#define SPI_MOSI     3
#define SPI_MISO     4
#define SPI_CE       5

//Touchscreen
#define TP_SDA       6
#define TP_SCL       7
#define TP_RESET     13 
#define TP_INT       28

//Accl Sensor
#define BMA421_SDA       6
#define BMA421_SCL       7
#define BMA421_INT       8
//#define SWITCH_X_Y

//HeartRate Sensor
#define HRS3300_SDA       6
#define HRS3300_SCL       7
#define HRS3300_TEST      30

//Battery
#define CHARGE_INDICATION -1  
#define POWER_INDICATION  19
#define BATTERY_VOLTAGE   31
#define POWER_CONTROL     24

//InputOutput
#define STATUS_LED        27
#define VIBRATOR_OUT      16
#define PUSH_BUTTON_IN    17  
#define PUSH_BUTTON_OUT   -1  

//Backlight
#define LCD_BACKLIGHT_LOW  14
#define LCD_BACKLIGHT_MID  22
#define LCD_BACKLIGHT_HIGH 23

#endif //P8WATCH 
#ifdef SN80
// SN80########################################################################################
//display
#define LCD_SCK      2
#define LCD_SDI      3
#define LCD_CS       25
#define LCD_RESET    26
#define LCD_RS       18
#define LCD_DET      9

//Flash Chip
#define SPI_SCK      2
#define SPI_MOSI     3
#define SPI_MISO     4
#define SPI_CE       5

//Touchscreen
#define TP_SDA       6
#define TP_SCL       7
#define TP_RESET     10 
#define TP_INT       28

//Accl Sensor
#define BMA421_SDA       6
#define BMA421_SCL       7
#define BMA421_INT       8
//#define SWITCH_X_Y

//HeartRate Sensor
#define HRS3300_SDA       6
#define HRS3300_SCL       7
#define HRS3300_TEST      30

//Battery
//#define CHARGE_INDICATION 12 // Pinetime
#define CHARGE_INDICATION -1  // P8 Watch// SN80??
#define POWER_INDICATION  19
#define BATTERY_VOLTAGE   31
#define POWER_CONTROL 24

//InputOutput
#define STATUS_LED        27
#define VIBRATOR_OUT      16
#define PUSH_BUTTON_IN    9 
#define PUSH_BUTTON_OUT   17 

//Backlight
#define LCD_BACKLIGHT_LOW  14
#define LCD_BACKLIGHT_MID  22
#define LCD_BACKLIGHT_HIGH 23

#endif // SN80

#ifdef PineTime
// Pinetime########################################################################################
//display
#define LCD_SCK      2
#define LCD_SDI      3
#define LCD_CS       25
#define LCD_RESET    26
#define LCD_RS       18
#define LCD_DET      9

//Flash Chip
#define SPI_SCK      2
#define SPI_MOSI     3
#define SPI_MISO     4
#define SPI_CE       5

//Touchscreen
#define TP_SDA       6
#define TP_SCL       7
#define TP_RESET     10 
#define TP_INT       28

//Accl Sensor
#define BMA421_SDA       6
#define BMA421_SCL       7
#define BMA421_INT       8
#define SWITCH_X_Y

//HeartRate Sensor
#define HRS3300_SDA       6
#define HRS3300_SCL       7
#define HRS3300_TEST      30

//Battery
#define CHARGE_INDICATION 12 
#define POWER_INDICATION  19
#define BATTERY_VOLTAGE   31
#define POWER_CONTROL 24

//InputOutput
#define STATUS_LED        27
#define VIBRATOR_OUT      16
#define PUSH_BUTTON_IN    13 
#define PUSH_BUTTON_OUT   15 

//Backlight
#define LCD_BACKLIGHT_LOW  14
#define LCD_BACKLIGHT_MID  22
#define LCD_BACKLIGHT_HIGH 23


#endif // PineTime


#endif // _PINOUT_