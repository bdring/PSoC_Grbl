/*******************************************************************************
* File Name: Coolant_Pin.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_Coolant_Pin_H) /* Pins Coolant_Pin_H */
#define CY_PINS_Coolant_Pin_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Coolant_Pin_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Coolant_Pin__PORT == 15 && ((Coolant_Pin__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Coolant_Pin_Write(uint8 value);
void    Coolant_Pin_SetDriveMode(uint8 mode);
uint8   Coolant_Pin_ReadDataReg(void);
uint8   Coolant_Pin_Read(void);
void    Coolant_Pin_SetInterruptMode(uint16 position, uint16 mode);
uint8   Coolant_Pin_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Coolant_Pin_SetDriveMode() function.
     *  @{
     */
        #define Coolant_Pin_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Coolant_Pin_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Coolant_Pin_DM_RES_UP          PIN_DM_RES_UP
        #define Coolant_Pin_DM_RES_DWN         PIN_DM_RES_DWN
        #define Coolant_Pin_DM_OD_LO           PIN_DM_OD_LO
        #define Coolant_Pin_DM_OD_HI           PIN_DM_OD_HI
        #define Coolant_Pin_DM_STRONG          PIN_DM_STRONG
        #define Coolant_Pin_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Coolant_Pin_MASK               Coolant_Pin__MASK
#define Coolant_Pin_SHIFT              Coolant_Pin__SHIFT
#define Coolant_Pin_WIDTH              1u

/* Interrupt constants */
#if defined(Coolant_Pin__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Coolant_Pin_SetInterruptMode() function.
     *  @{
     */
        #define Coolant_Pin_INTR_NONE      (uint16)(0x0000u)
        #define Coolant_Pin_INTR_RISING    (uint16)(0x0001u)
        #define Coolant_Pin_INTR_FALLING   (uint16)(0x0002u)
        #define Coolant_Pin_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Coolant_Pin_INTR_MASK      (0x01u) 
#endif /* (Coolant_Pin__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Coolant_Pin_PS                     (* (reg8 *) Coolant_Pin__PS)
/* Data Register */
#define Coolant_Pin_DR                     (* (reg8 *) Coolant_Pin__DR)
/* Port Number */
#define Coolant_Pin_PRT_NUM                (* (reg8 *) Coolant_Pin__PRT) 
/* Connect to Analog Globals */                                                  
#define Coolant_Pin_AG                     (* (reg8 *) Coolant_Pin__AG)                       
/* Analog MUX bux enable */
#define Coolant_Pin_AMUX                   (* (reg8 *) Coolant_Pin__AMUX) 
/* Bidirectional Enable */                                                        
#define Coolant_Pin_BIE                    (* (reg8 *) Coolant_Pin__BIE)
/* Bit-mask for Aliased Register Access */
#define Coolant_Pin_BIT_MASK               (* (reg8 *) Coolant_Pin__BIT_MASK)
/* Bypass Enable */
#define Coolant_Pin_BYP                    (* (reg8 *) Coolant_Pin__BYP)
/* Port wide control signals */                                                   
#define Coolant_Pin_CTL                    (* (reg8 *) Coolant_Pin__CTL)
/* Drive Modes */
#define Coolant_Pin_DM0                    (* (reg8 *) Coolant_Pin__DM0) 
#define Coolant_Pin_DM1                    (* (reg8 *) Coolant_Pin__DM1)
#define Coolant_Pin_DM2                    (* (reg8 *) Coolant_Pin__DM2) 
/* Input Buffer Disable Override */
#define Coolant_Pin_INP_DIS                (* (reg8 *) Coolant_Pin__INP_DIS)
/* LCD Common or Segment Drive */
#define Coolant_Pin_LCD_COM_SEG            (* (reg8 *) Coolant_Pin__LCD_COM_SEG)
/* Enable Segment LCD */
#define Coolant_Pin_LCD_EN                 (* (reg8 *) Coolant_Pin__LCD_EN)
/* Slew Rate Control */
#define Coolant_Pin_SLW                    (* (reg8 *) Coolant_Pin__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Coolant_Pin_PRTDSI__CAPS_SEL       (* (reg8 *) Coolant_Pin__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Coolant_Pin_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Coolant_Pin__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Coolant_Pin_PRTDSI__OE_SEL0        (* (reg8 *) Coolant_Pin__PRTDSI__OE_SEL0) 
#define Coolant_Pin_PRTDSI__OE_SEL1        (* (reg8 *) Coolant_Pin__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Coolant_Pin_PRTDSI__OUT_SEL0       (* (reg8 *) Coolant_Pin__PRTDSI__OUT_SEL0) 
#define Coolant_Pin_PRTDSI__OUT_SEL1       (* (reg8 *) Coolant_Pin__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Coolant_Pin_PRTDSI__SYNC_OUT       (* (reg8 *) Coolant_Pin__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Coolant_Pin__SIO_CFG)
    #define Coolant_Pin_SIO_HYST_EN        (* (reg8 *) Coolant_Pin__SIO_HYST_EN)
    #define Coolant_Pin_SIO_REG_HIFREQ     (* (reg8 *) Coolant_Pin__SIO_REG_HIFREQ)
    #define Coolant_Pin_SIO_CFG            (* (reg8 *) Coolant_Pin__SIO_CFG)
    #define Coolant_Pin_SIO_DIFF           (* (reg8 *) Coolant_Pin__SIO_DIFF)
#endif /* (Coolant_Pin__SIO_CFG) */

/* Interrupt Registers */
#if defined(Coolant_Pin__INTSTAT)
    #define Coolant_Pin_INTSTAT            (* (reg8 *) Coolant_Pin__INTSTAT)
    #define Coolant_Pin_SNAP               (* (reg8 *) Coolant_Pin__SNAP)
    
	#define Coolant_Pin_0_INTTYPE_REG 		(* (reg8 *) Coolant_Pin__0__INTTYPE)
#endif /* (Coolant_Pin__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Coolant_Pin_H */


/* [] END OF FILE */
