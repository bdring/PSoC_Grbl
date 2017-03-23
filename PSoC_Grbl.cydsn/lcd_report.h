/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#ifndef lcd_report_h
#define lcd_report_h

#include "grbl.h"
  
uint8_t exec_lcd_status; // flag to show lcd_status

#define LCD_UNIT_MM 0
#define LCD_UNIT_IN 1  
  
#define MAIN_SCREEN 0
#define CMD_SCREEN 1
#define PROBE_SCREEN 2
#define SD_CARD_SCREEN 3  
  
#define MENU_ITEM_MAIN_STATUS 0
#define MENU_ITEM_MAIN_X_DRO  1
#define MENU_ITEM_MAIN_Y_DRO 2
#define MENU_ITEM_MAIN_Z_DRO 3
#define MENU_ITEM_MAIN_UNIT  4
#define MENU_ITEM_MAIN_FRO   5
#define MENU_ITEM_MAIN_SRO  6
#define MENU_ITEM_MAIN_MORE 7
  
#define MENU_ITEM_PRB_BACK 0
#define MENU_ITEM_PRB_PROBE 1
#define MENU_ITEM_PRB_THICK 2
#define MENU_ITEM_PRB_RATE 3
#define MENU_ITEM_PRB_DIST 4
  
  
#define LCD_FRO_MIN 10
#define LCD_FRO_MAX 250 
#define LCD_SRO_MIN 50
#define LCD_SRO_MAX 250
  
  
#define LCD_PRB_THICK_MIN 3.0
#define LCD_PRB_THICK_MAX 30.0
#define LCD_PRB_THICK_INC 0.05 
#define LCD_PROBE_MULT 100  
  
#define LCD_PRB_RATE_MIN 20
#define LCD_PRB_RATE_MAX 200
  
#define LCD_PRB_DIST_MIN 20
#define LCD_PRB_DIST_MAX 200
  
void enc_sw_isr_handler();
void lcd_init();
//void ISR_lcd();
CY_ISR_PROTO(ISR_lcd);
void lcd_report_init_message();
void lcd_report_realtime();
void lcd_unsigned_int8(uint8_t n, uint8_t base, uint8_t digits);
void lcd_menu_execute(char *line);
void lcd_beep();

#endif
