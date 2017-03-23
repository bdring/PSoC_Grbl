/*******************************************************************************
* File Name: Control_Pin.h  
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

#if !defined(CY_PINS_Control_Pin_ALIASES_H) /* Pins Control_Pin_ALIASES_H */
#define CY_PINS_Control_Pin_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"


/***************************************
*              Constants        
***************************************/
#define Control_Pin_0			(Control_Pin__0__PC)
#define Control_Pin_0_INTR	((uint16)((uint16)0x0001u << Control_Pin__0__SHIFT))

#define Control_Pin_1			(Control_Pin__1__PC)
#define Control_Pin_1_INTR	((uint16)((uint16)0x0001u << Control_Pin__1__SHIFT))

#define Control_Pin_2			(Control_Pin__2__PC)
#define Control_Pin_2_INTR	((uint16)((uint16)0x0001u << Control_Pin__2__SHIFT))

#define Control_Pin_3			(Control_Pin__3__PC)
#define Control_Pin_3_INTR	((uint16)((uint16)0x0001u << Control_Pin__3__SHIFT))

#define Control_Pin_INTR_ALL	 ((uint16)(Control_Pin_0_INTR| Control_Pin_1_INTR| Control_Pin_2_INTR| Control_Pin_3_INTR))

#endif /* End Pins Control_Pin_ALIASES_H */


/* [] END OF FILE */
