/*******************************************************************************
* File Name: EEPROM_PSoC.h
* Version 3.0
*
*  Description:
*   Provides the function definitions for the EEPROM APIs.
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_EEPROM_EEPROM_PSoC_H)
#define CY_EEPROM_EEPROM_PSoC_H

#include "cydevice_trm.h"
#include "CyFlash.h"

#if !defined(CY_PSOC5LP)
    #error Component EEPROM_v3_0 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */


/***************************************
*        Function Prototypes
***************************************/

void EEPROM_PSoC_Enable(void) ;
void EEPROM_PSoC_Start(void) ;
void EEPROM_PSoC_Stop (void) ;
cystatus EEPROM_PSoC_WriteByte(uint8 dataByte, uint16 address) \
                                            ;
uint8 EEPROM_PSoC_ReadByte(uint16 address) ;
uint8 EEPROM_PSoC_UpdateTemperature(void) ;
cystatus EEPROM_PSoC_EraseSector(uint8 sectorNumber) ;
cystatus EEPROM_PSoC_Write(const uint8 * rowData, uint8 rowNumber) ;
cystatus EEPROM_PSoC_StartWrite(const uint8 * rowData, uint8 rowNumber) \
                                                ;
cystatus EEPROM_PSoC_StartErase(uint8 sectorNumber) ;
cystatus EEPROM_PSoC_Query(void) ;
cystatus EEPROM_PSoC_ByteWritePos(uint8 dataByte, uint8 rowNumber, uint8 byteNumber) \
                                                ;


/****************************************
*           API Constants
****************************************/

#define EEPROM_PSoC_EEPROM_SIZE            CYDEV_EE_SIZE
#define EEPROM_PSoC_SPC_BYTE_WRITE_SIZE    (0x01u)

#define EEPROM_PSoC_SECTORS_NUMBER         (CYDEV_EE_SIZE / CYDEV_EEPROM_SECTOR_SIZE)

#define EEPROM_PSoC_AHB_REQ_SHIFT          (0x00u)
#define EEPROM_PSoC_AHB_REQ                ((uint8)(0x01u << EEPROM_PSoC_AHB_REQ_SHIFT))
#define EEPROM_PSoC_AHB_ACK_SHIFT          (0x01u)
#define EEPROM_PSoC_AHB_ACK_MASK           ((uint8)(0x01u << EEPROM_PSoC_AHB_ACK_SHIFT))


/***************************************
* Registers
***************************************/
#define EEPROM_PSoC_SPC_EE_SCR_REG                 (*(reg8 *) CYREG_SPC_EE_SCR)
#define EEPROM_PSoC_SPC_EE_SCR_PTR                 ( (reg8 *) CYREG_SPC_EE_SCR)



/***************************************
* The following code is DEPRECATED and
* should not be used in new projects.
***************************************/
#define EEPROM_PSoC_ByteWrite                  EEPROM_PSoC_ByteWritePos
#define EEPROM_PSoC_QueryWrite                 EEPROM_PSoC_Query

#endif /* CY_EEPROM_EEPROM_PSoC_H */

/* [] END OF FILE */
