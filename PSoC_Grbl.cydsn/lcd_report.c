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
#include <project.h>
#include "grbl.h"


int8 fro;
int8 lcd_screen = MAIN_SCREEN;
int8 menu_item_selected = false;
int8 lcd_cursor = 4;
int8 lcd_cursor_max = 6;
int8 switch_clicked = false;
int8 lcd_units = LCD_UNIT_MM;
int16 lcd_FRO = 100; 
int16 lcd_SRO = 100;
// TO DO store these in EEPROM 
float lcd_probe_thickness = 15.0;
int16 lcd_probe_rate = 100;
int16 lcd_probe_dist = 120;

void lcd_init()
{
    LCD_Start();
    LCD_LoadCustomFonts(LCD_customFonts); 
    LCD_WriteControl(LCD_CLEAR_DISPLAY);
    QuadDec_Start();
    isr_Enc_Sw_StartEx(enc_sw_isr_handler);
    exec_lcd_status = false;
}

void enc_sw_isr_handler()
{
  switch_clicked = true;
}

void lcd_report_init_message()
{
    LCD_WriteControl(LCD_CLEAR_DISPLAY);
    LCD_Position(0u, 3u);
    
    /* Output demo start message */
    LCD_PrintString(GRBL_PORT " " GRBL_VERSION);
    delay_ms(1000);
    LCD_WriteControl(LCD_CLEAR_DISPLAY);
    
    lcd_report_realtime();
    
}

CY_ISR(ISR_lcd)
{
  exec_lcd_status = true;
}

void lcd_report_realtime()
{
  uint8_t switches = false;  // currently used for hardware checking.
   uint8_t idx;
  char stat[12];    
  char fstr[20];
  char line[20];
  char num_format[] = "%+8.2f";
  int32_t current_position[N_AXIS]; // Copy current state of the system position variable
  memcpy(current_position,sys_position,sizeof(sys_position));
  float print_position[N_AXIS];
  
  
    
  switch (lcd_screen)
  {
    case MAIN_SCREEN:   // ====================================================
      // Current machine state
      lcd_cursor_max = 7;
      get_state(stat);
      LCD_Position(0u, 0u);
      LCD_PrintString(stat);
      
      if (switch_clicked) {
        switch_clicked = false;
        switch (lcd_cursor)
        {
          case MENU_ITEM_MAIN_STATUS:
            if (sys.state == STATE_ALARM) {  // Ignore if already in alarm state. 
              system_execute_line("$X");
            }
          break;
          case MENU_ITEM_MAIN_X_DRO:
           lcd_menu_execute("G10L20P0X0");
          break;
          case MENU_ITEM_MAIN_Y_DRO:
           lcd_menu_execute("G10L20P0Y0");
          break;
          case MENU_ITEM_MAIN_Z_DRO:
           lcd_menu_execute("G10L20P0Z0");
          break;
          
          case MENU_ITEM_MAIN_UNIT:
            if (lcd_units == LCD_UNIT_MM)
              lcd_units = LCD_UNIT_IN;
            else
              lcd_units = LCD_UNIT_MM;
          break;
          case MENU_ITEM_MAIN_FRO:
              menu_item_selected = !menu_item_selected;
              if (menu_item_selected)
                QuadDec_SetCounter(lcd_FRO);
              else
                QuadDec_SetCounter(MENU_ITEM_MAIN_FRO);
          break;  
          case MENU_ITEM_MAIN_SRO:
              menu_item_selected = !menu_item_selected;
              if (menu_item_selected)
                QuadDec_SetCounter(lcd_SRO);
              else
                QuadDec_SetCounter(MENU_ITEM_MAIN_SRO);
          break;     
          case MENU_ITEM_MAIN_MORE:
            lcd_screen = CMD_SCREEN; 
            lcd_cursor = 0;
            QuadDec_SetCounter(lcd_cursor);
            LCD_WriteControl(LCD_CLEAR_DISPLAY);
          break;
            
        }
        if (lcd_screen != MAIN_SCREEN) break;       
      }
      
    if (switches)
    {
      LCD_Position(1u, 0u);
      LCD_PrintString("Limit:");
      lcd_unsigned_int8(Status_Limit_Read(), 2, 3);      
      
      LCD_Position(2u, 0u);
      LCD_PrintString("Ctl:");    
      lcd_unsigned_int8(Status_Control_Read(), 2, 4);
      
      LCD_Position(3u, 0u);
      LCD_PrintString("Probe:");
      lcd_unsigned_int8(Status_Probe_Read(), 2, 1);
      break;
    }
    
      system_convert_array_steps_to_mpos(print_position,current_position); // get the position in MCS
      
      // convert it to WCS      
      for (idx=0; idx< N_AXIS; idx++) {
      print_position[idx] -= gc_state.coord_system[idx]+gc_state.coord_offset[idx];
        if (idx == TOOL_LENGTH_OFFSET_AXIS) { print_position[idx] -= gc_state.tool_length_offset; }
      }
      
      // determine the units, set the number of decimals and convert to inches if req'd
      LCD_Position(0u, 11u);
      LCD_PrintString(" Unit:");
      if (lcd_units == LCD_UNIT_MM) {
        LCD_PrintString(" mm");
        strcpy(num_format, "%+8.2f");
      }
      else { 
          for (idx=0; idx< N_AXIS; idx++) {   // convert to inches
            print_position[idx] /= MM_PER_INCH;  
          }
          LCD_PrintString(" in"); 
          strcpy(num_format, "%+8.3f");
      }
      
      // Do the DROs
      LCD_Position(1u, 0u);
      LCD_PrintString(" X");
      sprintf(fstr, num_format, print_position[X_AXIS] ); 
      LCD_PrintString(fstr);    
    
      LCD_Position(2u, 0u);
      LCD_PrintString(" Y");
      sprintf(fstr, num_format, print_position[Y_AXIS] ); 
      LCD_PrintString(fstr);      
      
      LCD_Position(3u, 0u);
      LCD_PrintString(" Z");
      sprintf(fstr, num_format, print_position[Z_AXIS] ); 
      LCD_PrintString(fstr);      
      
      LCD_Position(1u, 11u);
      LCD_PrintString(" FRO:");
      sprintf(fstr, "%3d", lcd_FRO ); 
      LCD_PrintString(fstr);
      LCD_PrintString("%");
      
      LCD_Position(2u, 11u);
      LCD_PrintString(" SRO:");
      sprintf(fstr, "%3d", lcd_SRO ); 
      LCD_PrintString(fstr);
      LCD_PrintString("%");
      
      LCD_Position(3u, 11u);
      LCD_PrintString(" More ");
      LCD_PutChar(LCD_CUSTOM_2);
      
      
      if (menu_item_selected) {
        switch (lcd_cursor) {
         case MENU_ITEM_MAIN_FRO:
          lcd_FRO = QuadDec_GetCounter();
          if (lcd_FRO > LCD_FRO_MAX) lcd_FRO = LCD_FRO_MAX;
          if (lcd_FRO < LCD_FRO_MIN) lcd_FRO = LCD_FRO_MIN;
         break; 
          case MENU_ITEM_MAIN_SRO:
          lcd_SRO = QuadDec_GetCounter();
          if (lcd_SRO > LCD_SRO_MAX) lcd_FRO = LCD_SRO_MAX;
          if (lcd_SRO < LCD_SRO_MIN) lcd_FRO = LCD_SRO_MIN;
          break;
        }
      }
      else {
        lcd_cursor = QuadDec_GetCounter();
        if  (lcd_cursor > lcd_cursor_max) lcd_cursor = lcd_cursor_max;
        if  (lcd_cursor < 0) lcd_cursor = 0;
        
        QuadDec_SetCounter(lcd_cursor);
        
      }
      
       
      
      LCD_WriteControl(LCD_DISPLAY_ON_CURSOR_OFF);
      switch (lcd_cursor)
      {
       case MENU_ITEM_MAIN_STATUS:
        LCD_Position(0u, 0u);
        LCD_PutChar(LCD_CUSTOM_0);
       break;
       case MENU_ITEM_MAIN_X_DRO:
        LCD_Position(1u, 0u);
        LCD_PutChar(LCD_CUSTOM_0);
       break;
       case MENU_ITEM_MAIN_Y_DRO:
        LCD_Position(2u, 0u);
        LCD_PutChar(LCD_CUSTOM_0);
       break; 
       case MENU_ITEM_MAIN_Z_DRO:
        LCD_Position(3u, 0u);
        LCD_PutChar(LCD_CUSTOM_0);
       break;
       case MENU_ITEM_MAIN_UNIT:
        LCD_Position(0u, 11u);
        LCD_PutChar(LCD_CUSTOM_0);
       break;
       case MENU_ITEM_MAIN_FRO:
        LCD_Position(1u, 11u);
        LCD_PutChar(LCD_CUSTOM_0);
        if (menu_item_selected) {
          LCD_Position(1u, 11u);
          LCD_WriteControl(LCD_CURSOR_WINK);
        }
        else {
          
        }
       break;
       case MENU_ITEM_MAIN_SRO:
        LCD_Position(2u, 11u);
        LCD_PutChar(LCD_CUSTOM_0);
        if (menu_item_selected) {
          LCD_Position(2u, 11u);
          LCD_WriteControl(LCD_CURSOR_WINK);
        }
        else {
          
        }
        
       break;
       case MENU_ITEM_MAIN_MORE:
        LCD_Position(3u, 11u);
        LCD_PutChar(LCD_CUSTOM_0);
       break;       
      }
      
    
      
    break; // main screen
      
    case CMD_SCREEN:  // ============================================================
      lcd_cursor_max = 7;
      
      if (switch_clicked) {
        switch_clicked = false;
        switch (lcd_cursor)
        {
          case 0: // return to main
            lcd_screen = MAIN_SCREEN; 
            lcd_cursor = 0;        
            LCD_WriteControl(LCD_CLEAR_DISPLAY);
          break;
            
          case 1: // home axes
            if (bit_istrue(settings.flags,BITFLAG_HOMING_ENABLE)) { 
            // Block if safety door is ajar.
            if (system_check_safety_door_ajar()) { lcd_beep(); }
            sys.state = STATE_HOMING; // Set system state variable
            mc_homing_cycle(HOMING_CYCLE_ALL);
            if (!sys.abort) {  // Execute startup scripts after successful homing.
              sys.state = STATE_IDLE; // Set to IDLE when complete.
              st_go_idle(); // Set steppers to the settings idle state before returning.
              //system_execute_startup(line); 
            }
          } else { lcd_beep(); }
          break;
            
          case 2: // Top of Z
            lcd_menu_execute("G53G0Z-1");
          break;
            
          case 3: // go to probe screen
            lcd_screen = PROBE_SCREEN;
            lcd_cursor_max = 4;
            lcd_cursor = 0;
            QuadDec_SetCounter(lcd_cursor);
            LCD_WriteControl(LCD_CLEAR_DISPLAY);
          break;  
            
          case 4:  // goto 0,0
            lcd_menu_execute("G0X0Y0");
          break;
            
          case 5: // G28
            lcd_menu_execute("G28");
          break;
            
          case 6: // G30
            lcd_menu_execute("G30");
          break;
            
          case 7: // sd card
            lcd_screen = SD_CARD_SCREEN; 
            lcd_cursor = 0;        
            LCD_WriteControl(LCD_CLEAR_DISPLAY);
          break;  
            
        }
        
        if (lcd_screen != CMD_SCREEN) break;
      }
    
      LCD_Position(0u, 0u);
      LCD_PrintString(" Back ");
      LCD_PutChar(LCD_CUSTOM_3);
      LCD_Position(1u, 0u);
      LCD_PrintString(" Home Axes");
      LCD_Position(2u, 0u);
      LCD_PrintString(" Top of Z");
      LCD_Position(3u, 0u);
      LCD_PrintString(" Z Probe ");
      LCD_PutChar(LCD_CUSTOM_2);
      
      LCD_Position(0u, 11u);
      LCD_PrintString(" Goto 0,0");
      LCD_Position(1u, 11u);
      LCD_PrintString(" Goto G28");
      LCD_Position(2u, 11u);
      LCD_PrintString(" Goto G30");
      LCD_Position(3u, 11u);
      LCD_PrintString(" SdCard ");
      LCD_PutChar(LCD_CUSTOM_2);
        
      if (menu_item_selected) {
      }
      else {
        lcd_cursor = QuadDec_GetCounter();
        if  (lcd_cursor > lcd_cursor_max) lcd_cursor = lcd_cursor_max;
        if  (lcd_cursor < 0) lcd_cursor = 0;
        
        QuadDec_SetCounter(lcd_cursor);
        
      }
        
      switch (lcd_cursor)
      {
       case 0:
        LCD_Position(0u, 0u);
        LCD_PutChar(LCD_CUSTOM_0);
       break;
       case 1:
        LCD_Position(1u, 0u);
        LCD_PutChar(LCD_CUSTOM_0);
       break; 
       case 2:
        LCD_Position(2u, 0u);
        LCD_PutChar(LCD_CUSTOM_0);
       break;
       case 3:
        LCD_Position(3u, 0u);
        LCD_PutChar(LCD_CUSTOM_0);
       break;
       case 4:
        LCD_Position(0u, 11u);
        LCD_PutChar(LCD_CUSTOM_0);
       break;
       case 5:
        LCD_Position(1u, 11u);
        LCD_PutChar(LCD_CUSTOM_0);
       break;
       case 6:
        LCD_Position(2u, 11u);
        LCD_PutChar(LCD_CUSTOM_0);
       break;
        case 7:
        LCD_Position(3u, 11u);
        LCD_PutChar(LCD_CUSTOM_0);
       break; 
      }
        
    break;
      
    case PROBE_SCREEN: // ===============================================================
      
      if (switch_clicked) {
        switch_clicked = false;
        switch (lcd_cursor)
        {
          case MENU_ITEM_PRB_BACK: // return to main
            lcd_screen = CMD_SCREEN;            
            LCD_WriteControl(LCD_CLEAR_DISPLAY);
          break;
            
          case MENU_ITEM_PRB_PROBE:
            LCD_WriteControl(LCD_CLEAR_DISPLAY);
            lcd_screen = MAIN_SCREEN;
            strcpy(line, "G91G38.2Z-");
            sprintf(fstr, "%d", lcd_probe_dist);
            strcat(line, fstr);
            strcat(line, "F");
            sprintf(fstr, "%d", lcd_probe_rate);
            strcat(line, fstr);
            gc_execute_line(line);
            LCD_Position(3u, 0u);
            if (sys.probe_succeeded == false) {
              // TO DO Not sure if this works
              LCD_PrintString("Failure");
            }
            else {
              //LCD_Position(3u, 0u);
              LCD_PrintString("Success");
              sprintf(fstr, "%2.2f", lcd_probe_thickness);
              strcpy(line, "G10L20P0Z");
              strcat(line, fstr);
              gc_execute_line(line);
              
            }
          break;  
            
          case MENU_ITEM_PRB_THICK:
            menu_item_selected = !menu_item_selected;
            if (menu_item_selected)
                QuadDec_SetCounter(lcd_probe_thickness * LCD_PROBE_MULT);
              else
                QuadDec_SetCounter(lcd_cursor);
          break;  
                
          case MENU_ITEM_PRB_RATE:
                menu_item_selected = !menu_item_selected;
            if (menu_item_selected)
                QuadDec_SetCounter(lcd_probe_rate);
              else
                QuadDec_SetCounter(lcd_cursor);
          break;
                
          case MENU_ITEM_PRB_DIST:
                menu_item_selected = !menu_item_selected;
            if (menu_item_selected)
                QuadDec_SetCounter(lcd_probe_dist);
              else
                QuadDec_SetCounter(lcd_cursor);
          break;            
        }        
        if (lcd_screen != PROBE_SCREEN) break;
      }
      
      LCD_Position(0u, 0u);
      LCD_PrintString(" Back ");
      LCD_PutChar(LCD_CUSTOM_3);
      
      LCD_Position(0u, 8u);
      LCD_PrintString(" Begin Probe"); 
      
      LCD_Position(1u, 8u);
      LCD_PrintString(" Thick:");
      sprintf(fstr, "%2.2f", lcd_probe_thickness ); 
      LCD_PrintString(fstr);
      
      LCD_Position(2u, 8u);
      LCD_PrintString(" Rate:");
      sprintf(fstr, "%6d", lcd_probe_rate ); 
      LCD_PrintString(fstr);
      
      LCD_Position(3u, 8u);
      LCD_PrintString(" Dist:");
      sprintf(fstr, "%6d", lcd_probe_dist ); 
      LCD_PrintString(fstr);
     
      if (menu_item_selected) {
      }
      else {
        lcd_cursor = QuadDec_GetCounter();
        if  (lcd_cursor > lcd_cursor_max) lcd_cursor = lcd_cursor_max;
        if  (lcd_cursor < 0) lcd_cursor = 0;
        
        QuadDec_SetCounter(lcd_cursor);
        
      }
      
      if (menu_item_selected) {
        switch (lcd_cursor) {
         case MENU_ITEM_PRB_THICK:
          lcd_probe_thickness = (float)QuadDec_GetCounter() / LCD_PROBE_MULT;
          if (lcd_probe_thickness > LCD_PRB_THICK_MAX) lcd_probe_thickness = LCD_PRB_THICK_MAX;
          if (lcd_probe_thickness < LCD_PRB_THICK_MIN) lcd_probe_thickness = LCD_PRB_THICK_MIN;
          QuadDec_SetCounter(lcd_probe_thickness * LCD_PROBE_MULT);
         break;
         case MENU_ITEM_PRB_RATE:
          lcd_probe_rate = QuadDec_GetCounter();
          if (lcd_probe_rate > LCD_PRB_RATE_MAX) lcd_probe_rate = LCD_PRB_RATE_MAX;
          if (lcd_probe_rate < LCD_PRB_RATE_MIN) lcd_probe_rate = LCD_PRB_RATE_MIN;
          QuadDec_SetCounter(lcd_probe_rate);
         break;
         case MENU_ITEM_PRB_DIST:
          lcd_probe_dist = QuadDec_GetCounter();
          if (lcd_probe_dist > LCD_PRB_DIST_MAX) lcd_probe_dist = LCD_PRB_DIST_MAX;
          if (lcd_probe_dist < LCD_PRB_DIST_MIN) lcd_probe_dist = LCD_PRB_DIST_MIN;
          QuadDec_SetCounter(lcd_probe_dist);
         break; 
          
        }
      }
      else {
        lcd_cursor = QuadDec_GetCounter();
        if  (lcd_cursor > lcd_cursor_max) lcd_cursor = lcd_cursor_max;
        if  (lcd_cursor < 0) lcd_cursor = 0;
        
        QuadDec_SetCounter(lcd_cursor);        
      }
      
      switch (lcd_cursor)
      {
       case 0:
        LCD_Position(0u, 0u);
        LCD_PutChar(LCD_CUSTOM_0);
       break;
       case 1:
        LCD_Position(0u, 8u);
        LCD_PutChar(LCD_CUSTOM_0);
       break; 
       case 2:
        LCD_Position(1u, 8u);
        LCD_PutChar(LCD_CUSTOM_0);
       break;
       case 3:
        LCD_Position(2u, 8u);
        LCD_PutChar(LCD_CUSTOM_0);
       break;
       case 4:
        LCD_Position(3u, 8u);
        LCD_PutChar(LCD_CUSTOM_0);
       break;       
      }
      
    break;  
      
    case SD_CARD_SCREEN:
      LCD_Position(0u, 0u);
      LCD_PrintString(" Back ");
      LCD_PutChar(LCD_CUSTOM_3);
      
      LCD_Position(2u, 0u);
      LCD_PrintString("Feature not ready"); 
      
      if (switch_clicked) {
        
        lcd_screen = CMD_SCREEN; 
        lcd_cursor = 0;
        QuadDec_SetCounter(lcd_cursor);
        LCD_WriteControl(LCD_CLEAR_DISPLAY);
        switch_clicked = false;
      }
      
    break;  
      
      
    default:
      LCD_Position(0u, 0u);
      sprintf(fstr, "Scn:%-5d", lcd_screen );
      LCD_PrintString(fstr);
    break;
  }  // switch lcd_screen

    
}

// Prints an uint8 variable with base and number of desired digits.
void lcd_unsigned_int8(uint8_t n, uint8_t base, uint8_t digits)
{ 
  unsigned char buf[digits];
  uint8_t i = 0;

  for (; i < digits; i++) {
      buf[i] = n % base ;
      n /= base;
  }

  for (; i > 0; i--)
      LCD_PutChar('0' + buf[i - 1]);
}

void lcd_menu_execute(char *line)
{
    if ( sys.state == STATE_IDLE)
      gc_execute_line(line);
    else
      lcd_beep();
      
}

void lcd_beep()
{
}


