/*******************************************************************************
* File Name: PWM_Spindle_PM.c
* Version 3.30
*
* Description:
*  This file provides the power management source code to API for the
*  PWM.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "PWM_Spindle.h"

static PWM_Spindle_backupStruct PWM_Spindle_backup;


/*******************************************************************************
* Function Name: PWM_Spindle_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration of the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  PWM_Spindle_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void PWM_Spindle_SaveConfig(void) 
{

    #if(!PWM_Spindle_UsingFixedFunction)
        #if(!PWM_Spindle_PWMModeIsCenterAligned)
            PWM_Spindle_backup.PWMPeriod = PWM_Spindle_ReadPeriod();
        #endif /* (!PWM_Spindle_PWMModeIsCenterAligned) */
        PWM_Spindle_backup.PWMUdb = PWM_Spindle_ReadCounter();
        #if (PWM_Spindle_UseStatus)
            PWM_Spindle_backup.InterruptMaskValue = PWM_Spindle_STATUS_MASK;
        #endif /* (PWM_Spindle_UseStatus) */

        #if(PWM_Spindle_DeadBandMode == PWM_Spindle__B_PWM__DBM_256_CLOCKS || \
            PWM_Spindle_DeadBandMode == PWM_Spindle__B_PWM__DBM_2_4_CLOCKS)
            PWM_Spindle_backup.PWMdeadBandValue = PWM_Spindle_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(PWM_Spindle_KillModeMinTime)
             PWM_Spindle_backup.PWMKillCounterPeriod = PWM_Spindle_ReadKillTime();
        #endif /* (PWM_Spindle_KillModeMinTime) */

        #if(PWM_Spindle_UseControl)
            PWM_Spindle_backup.PWMControlRegister = PWM_Spindle_ReadControlRegister();
        #endif /* (PWM_Spindle_UseControl) */
    #endif  /* (!PWM_Spindle_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: PWM_Spindle_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration of the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  PWM_Spindle_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void PWM_Spindle_RestoreConfig(void) 
{
        #if(!PWM_Spindle_UsingFixedFunction)
            #if(!PWM_Spindle_PWMModeIsCenterAligned)
                PWM_Spindle_WritePeriod(PWM_Spindle_backup.PWMPeriod);
            #endif /* (!PWM_Spindle_PWMModeIsCenterAligned) */

            PWM_Spindle_WriteCounter(PWM_Spindle_backup.PWMUdb);

            #if (PWM_Spindle_UseStatus)
                PWM_Spindle_STATUS_MASK = PWM_Spindle_backup.InterruptMaskValue;
            #endif /* (PWM_Spindle_UseStatus) */

            #if(PWM_Spindle_DeadBandMode == PWM_Spindle__B_PWM__DBM_256_CLOCKS || \
                PWM_Spindle_DeadBandMode == PWM_Spindle__B_PWM__DBM_2_4_CLOCKS)
                PWM_Spindle_WriteDeadTime(PWM_Spindle_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(PWM_Spindle_KillModeMinTime)
                PWM_Spindle_WriteKillTime(PWM_Spindle_backup.PWMKillCounterPeriod);
            #endif /* (PWM_Spindle_KillModeMinTime) */

            #if(PWM_Spindle_UseControl)
                PWM_Spindle_WriteControlRegister(PWM_Spindle_backup.PWMControlRegister);
            #endif /* (PWM_Spindle_UseControl) */
        #endif  /* (!PWM_Spindle_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: PWM_Spindle_Sleep
********************************************************************************
*
* Summary:
*  Disables block's operation and saves the user configuration. Should be called
*  just prior to entering sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  PWM_Spindle_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void PWM_Spindle_Sleep(void) 
{
    #if(PWM_Spindle_UseControl)
        if(PWM_Spindle_CTRL_ENABLE == (PWM_Spindle_CONTROL & PWM_Spindle_CTRL_ENABLE))
        {
            /*Component is enabled */
            PWM_Spindle_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            PWM_Spindle_backup.PWMEnableState = 0u;
        }
    #endif /* (PWM_Spindle_UseControl) */

    /* Stop component */
    PWM_Spindle_Stop();

    /* Save registers configuration */
    PWM_Spindle_SaveConfig();
}


/*******************************************************************************
* Function Name: PWM_Spindle_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration. Should be called just after
*  awaking from sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  PWM_Spindle_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void PWM_Spindle_Wakeup(void) 
{
     /* Restore registers values */
    PWM_Spindle_RestoreConfig();

    if(PWM_Spindle_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        PWM_Spindle_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
