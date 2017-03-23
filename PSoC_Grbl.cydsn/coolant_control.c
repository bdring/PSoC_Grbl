/*
  coolant_control.c - coolant control methods
  Part of Grbl

  Copyright (c) 2012-2015 Sungeun K. Jeon

  Grbl is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  Grbl is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with Grbl.  If not, see <http://www.gnu.org/licenses/>.
*/  

#include "grbl.h"


void coolant_init()
{ 
  coolant_set_state(COOLANT_DISABLE);
}

// Returns current coolant output state. Overrides may alter it from programmed state.
uint8_t coolant_get_state()
{
  uint8_t cl_state = COOLANT_STATE_DISABLE;
  
  if (Flood_Coolant_Pin_Read()) 
  {  
  cl_state |= COOLANT_STATE_FLOOD;
  }

  if (Mist_Coolant_Pin_Read()) 
  {  
  cl_state |= COOLANT_STATE_MIST;
  }
  
  return(cl_state);
}


void coolant_stop()
{
  Flood_Coolant_Pin_Write(0);
  Mist_Coolant_Pin_Write(0);
}


void coolant_set_state(uint8_t mode)
{
  if (sys.abort) { return; } // Block during abort.
  
  if (mode == COOLANT_DISABLE) 
  {  
    coolant_stop();
  }
  else
  {
    if (mode & COOLANT_FLOOD_ENABLE)
    {
      Flood_Coolant_Pin_Write(1);
    }
    if (mode & COOLANT_MIST_ENABLE)
    {
       Mist_Coolant_Pin_Write(1);
    }    
  }
  sys.report_ovr_counter = 0; // Set to report change immediately
 
}


// G-code parser entry-point for setting coolant state. Forces a planner buffer sync and bails 
// if an abort or check-mode is active.
void coolant_sync(uint8_t mode)
{
  if (sys.state == STATE_CHECK_MODE) { return; }
  protocol_buffer_synchronize(); // Ensure coolant turns on when specified in program.
  coolant_set_state(mode);
}
