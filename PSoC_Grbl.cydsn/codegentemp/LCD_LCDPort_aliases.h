/*******************************************************************************
* File Name: LCD_LCDPort.h  
* Version 2.20
*
* Description:
*  This file contains the Alias definitions for Per-Pin APIs in cypins.h. 
*  Information on using these APIs can be found in the System Reference Guide.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_LCD_LCDPort_ALIASES_H) /* Pins LCD_LCDPort_ALIASES_H */
#define CY_PINS_LCD_LCDPort_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"


/***************************************
*              Constants        
***************************************/
#define LCD_LCDPort_0			(LCD_LCDPort__0__PC)
#define LCD_LCDPort_0_INTR	((uint16)((uint16)0x0001u << LCD_LCDPort__0__SHIFT))

#define LCD_LCDPort_1			(LCD_LCDPort__1__PC)
#define LCD_LCDPort_1_INTR	((uint16)((uint16)0x0001u << LCD_LCDPort__1__SHIFT))

#define LCD_LCDPort_2			(LCD_LCDPort__2__PC)
#define LCD_LCDPort_2_INTR	((uint16)((uint16)0x0001u << LCD_LCDPort__2__SHIFT))

#define LCD_LCDPort_3			(LCD_LCDPort__3__PC)
#define LCD_LCDPort_3_INTR	((uint16)((uint16)0x0001u << LCD_LCDPort__3__SHIFT))

#define LCD_LCDPort_4			(LCD_LCDPort__4__PC)
#define LCD_LCDPort_4_INTR	((uint16)((uint16)0x0001u << LCD_LCDPort__4__SHIFT))

#define LCD_LCDPort_5			(LCD_LCDPort__5__PC)
#define LCD_LCDPort_5_INTR	((uint16)((uint16)0x0001u << LCD_LCDPort__5__SHIFT))

#define LCD_LCDPort_6			(LCD_LCDPort__6__PC)
#define LCD_LCDPort_6_INTR	((uint16)((uint16)0x0001u << LCD_LCDPort__6__SHIFT))

#define LCD_LCDPort_INTR_ALL	 ((uint16)(LCD_LCDPort_0_INTR| LCD_LCDPort_1_INTR| LCD_LCDPort_2_INTR| LCD_LCDPort_3_INTR| LCD_LCDPort_4_INTR| LCD_LCDPort_5_INTR| LCD_LCDPort_6_INTR))

#endif /* End Pins LCD_LCDPort_ALIASES_H */


/* [] END OF FILE */
