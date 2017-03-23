/*******************************************************************************
* File Name: Stepper_Timer_PM.c
* Version 2.70
*
*  Description:
*     This file provides the power management source code to API for the
*     Timer.
*
*   Note:
*     None
*
*******************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#include "Stepper_Timer.h"

static Stepper_Timer_backupStruct Stepper_Timer_backup;


/*******************************************************************************
* Function Name: Stepper_Timer_SaveConfig
********************************************************************************
*
* Summary:
*     Save the current user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  Stepper_Timer_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void Stepper_Timer_SaveConfig(void) 
{
    #if (!Stepper_Timer_UsingFixedFunction)
        Stepper_Timer_backup.TimerUdb = Stepper_Timer_ReadCounter();
        Stepper_Timer_backup.InterruptMaskValue = Stepper_Timer_STATUS_MASK;
        #if (Stepper_Timer_UsingHWCaptureCounter)
            Stepper_Timer_backup.TimerCaptureCounter = Stepper_Timer_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!Stepper_Timer_UDB_CONTROL_REG_REMOVED)
            Stepper_Timer_backup.TimerControlRegister = Stepper_Timer_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: Stepper_Timer_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  Stepper_Timer_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void Stepper_Timer_RestoreConfig(void) 
{   
    #if (!Stepper_Timer_UsingFixedFunction)

        Stepper_Timer_WriteCounter(Stepper_Timer_backup.TimerUdb);
        Stepper_Timer_STATUS_MASK =Stepper_Timer_backup.InterruptMaskValue;
        #if (Stepper_Timer_UsingHWCaptureCounter)
            Stepper_Timer_SetCaptureCount(Stepper_Timer_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!Stepper_Timer_UDB_CONTROL_REG_REMOVED)
            Stepper_Timer_WriteControlRegister(Stepper_Timer_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: Stepper_Timer_Sleep
********************************************************************************
*
* Summary:
*     Stop and Save the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  Stepper_Timer_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void Stepper_Timer_Sleep(void) 
{
    #if(!Stepper_Timer_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(Stepper_Timer_CTRL_ENABLE == (Stepper_Timer_CONTROL & Stepper_Timer_CTRL_ENABLE))
        {
            /* Timer is enabled */
            Stepper_Timer_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            Stepper_Timer_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    Stepper_Timer_Stop();
    Stepper_Timer_SaveConfig();
}


/*******************************************************************************
* Function Name: Stepper_Timer_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  Stepper_Timer_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Stepper_Timer_Wakeup(void) 
{
    Stepper_Timer_RestoreConfig();
    #if(!Stepper_Timer_UDB_CONTROL_REG_REMOVED)
        if(Stepper_Timer_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                Stepper_Timer_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
