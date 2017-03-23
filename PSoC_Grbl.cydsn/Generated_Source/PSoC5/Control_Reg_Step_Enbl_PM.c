/*******************************************************************************
* File Name: Control_Reg_Step_Enbl_PM.c
* Version 1.80
*
* Description:
*  This file contains the setup, control, and status commands to support 
*  the component operation in the low power mode. 
*
* Note:
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "Control_Reg_Step_Enbl.h"

/* Check for removal by optimization */
#if !defined(Control_Reg_Step_Enbl_Sync_ctrl_reg__REMOVED)

static Control_Reg_Step_Enbl_BACKUP_STRUCT  Control_Reg_Step_Enbl_backup = {0u};

    
/*******************************************************************************
* Function Name: Control_Reg_Step_Enbl_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the control register value.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Control_Reg_Step_Enbl_SaveConfig(void) 
{
    Control_Reg_Step_Enbl_backup.controlState = Control_Reg_Step_Enbl_Control;
}


/*******************************************************************************
* Function Name: Control_Reg_Step_Enbl_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the control register value.
*
* Parameters:
*  None
*
* Return:
*  None
*
*
*******************************************************************************/
void Control_Reg_Step_Enbl_RestoreConfig(void) 
{
     Control_Reg_Step_Enbl_Control = Control_Reg_Step_Enbl_backup.controlState;
}


/*******************************************************************************
* Function Name: Control_Reg_Step_Enbl_Sleep
********************************************************************************
*
* Summary:
*  Prepares the component for entering the low power mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Control_Reg_Step_Enbl_Sleep(void) 
{
    Control_Reg_Step_Enbl_SaveConfig();
}


/*******************************************************************************
* Function Name: Control_Reg_Step_Enbl_Wakeup
********************************************************************************
*
* Summary:
*  Restores the component after waking up from the low power mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Control_Reg_Step_Enbl_Wakeup(void)  
{
    Control_Reg_Step_Enbl_RestoreConfig();
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
