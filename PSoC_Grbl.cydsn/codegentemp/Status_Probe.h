/*******************************************************************************
* File Name: Status_Probe.h  
* Version 1.90
*
* Description:
*  This file containts Status Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_STATUS_REG_Status_Probe_H) /* CY_STATUS_REG_Status_Probe_H */
#define CY_STATUS_REG_Status_Probe_H

#include "cytypes.h"
#include "CyLib.h"

    
/***************************************
*     Data Struct Definitions
***************************************/

/* Sleep Mode API Support */
typedef struct
{
    uint8 statusState;

} Status_Probe_BACKUP_STRUCT;


/***************************************
*        Function Prototypes
***************************************/

uint8 Status_Probe_Read(void) ;
void Status_Probe_InterruptEnable(void) ;
void Status_Probe_InterruptDisable(void) ;
void Status_Probe_WriteMask(uint8 mask) ;
uint8 Status_Probe_ReadMask(void) ;


/***************************************
*           API Constants
***************************************/

#define Status_Probe_STATUS_INTR_ENBL    0x10u


/***************************************
*         Parameter Constants
***************************************/

/* Status Register Inputs */
#define Status_Probe_INPUTS              1


/***************************************
*             Registers
***************************************/

/* Status Register */
#define Status_Probe_Status             (* (reg8 *) Status_Probe_sts_intr_sts_reg__STATUS_REG )
#define Status_Probe_Status_PTR         (  (reg8 *) Status_Probe_sts_intr_sts_reg__STATUS_REG )
#define Status_Probe_Status_Mask        (* (reg8 *) Status_Probe_sts_intr_sts_reg__MASK_REG )
#define Status_Probe_Status_Aux_Ctrl    (* (reg8 *) Status_Probe_sts_intr_sts_reg__STATUS_AUX_CTL_REG )

#endif /* End CY_STATUS_REG_Status_Probe_H */


/* [] END OF FILE */
