/*******************************************************************************
* File Name: Limit_Pin.h  
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

#if !defined(CY_PINS_Limit_Pin_ALIASES_H) /* Pins Limit_Pin_ALIASES_H */
#define CY_PINS_Limit_Pin_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"


/***************************************
*              Constants        
***************************************/
#define Limit_Pin_0			(Limit_Pin__0__PC)
#define Limit_Pin_0_INTR	((uint16)((uint16)0x0001u << Limit_Pin__0__SHIFT))

#define Limit_Pin_1			(Limit_Pin__1__PC)
#define Limit_Pin_1_INTR	((uint16)((uint16)0x0001u << Limit_Pin__1__SHIFT))

#define Limit_Pin_2			(Limit_Pin__2__PC)
#define Limit_Pin_2_INTR	((uint16)((uint16)0x0001u << Limit_Pin__2__SHIFT))

#define Limit_Pin_INTR_ALL	 ((uint16)(Limit_Pin_0_INTR| Limit_Pin_1_INTR| Limit_Pin_2_INTR))

#endif /* End Pins Limit_Pin_ALIASES_H */


/* [] END OF FILE */
