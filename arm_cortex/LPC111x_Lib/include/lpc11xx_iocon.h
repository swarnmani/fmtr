/***********************************************************************//**
 * @file	: lpc11xx_wdt.h
 * @brief	: Contains all macro definitions and function prototypes
 * 				support for WDT firmware library on LPC11xx
 * @version	: 1.0
 * @date	: 22. Jan. 2010
 * @author	: Coocox
 **************************************************************************/

/* Peripheral group ----------------------------------------------------------- */
/** @defgroup WDT
 * @ingroup LPC1100CMSIS_FwLib_Drivers
 * @{
 */

#ifndef __LPC11XX_IOCON_H_
#define __LPC11XX_IOCON_H_

/* Includes ------------------------------------------------------------------- */
#include "LPC11xx.h"
#include "lpc_types.h"


#ifdef __cplusplus
extern "C"
{
#endif


/* Private Macros ------------------------------------------------------------- */
/** @defgroup IOCON_Private_Macros
 * @{
 */

/** @defgroup IOCON_Public_Types
 * @{
 */

/**
 * @brief SCK pin location enumeration
 */

#define  offsetof(TYPE, MEMBER)  ((uint32_t)&((TYPE*)0)->MEMBER)

typedef enum
{
    SCK0_PIO0_10 = 0,     /** Selects SCK0 function in pin location 
                              SWCLK/PIO0_10/SCK0/CT16B0_MAT2        */
    SCK0_PIO2_11,         /** Selects SCK0 function in pin location PIO2_11/SCK0 */
    SCK0_PIO0_6,          /** Selects SCK0 function in pin location PIO0_6/SCK0 */
}SCK0_Position_Typedef;

#define PARAM_SCK(n)     ((n==SCK_PIO0_10) || (n==SCK_PIO2_11) || (n==SCK_PIO0_6))


/**
 * @brief DSR pin location enumeration
 */
typedef enum
{
    DSR_PIO2_1 = 0,      /** Selects DSR function in pin location PIO2_1/DSR/SCK1 */
    DSR_PIO3_1,          /** Selects DSR function in pin location PIO3_1/DSR */
}DSR_Position_Typedef;

#define PARAM_DSR(n)     ((n==DSR_PIO2_1) || (n==DSR_PIO3_1))

/**
 * @brief DCD pin location enumeration
 */
typedef enum
{
    DCD_PIO2_2 = 0,      /** Selects DCD function in pin location PIO2_2/DCD/MISO1 */
    DCD_PIO3_2,          /** Selects DCD function in pin location PIO3_2/DCD */
}DCD_Position_Typedef;

#define PARAM_DCD(n)     ((n==DCD_PIO2_2) || (n==DCD_PIO3_2))

/**
 * @brief RI pin location enumeration
 */
typedef enum
{
    RI_PIO2_3 = 0,       /** Selects RI function in pin location PIO2_3/RI/MOSI1 */
    RI_PIO3_3,           /** Selects RI function in pin location PIO3_3/RI */
}RI_Position_Typedef;

#define PARAM_RI(n)      ((n==RI_PIO2_3) || (n==RI_PIO3_3))


/**
 * @brief Pin Connect Block structure
 */
#define IOCON_PIO0_0      offsetof(IOCON_TypeDef, PIO0_0)
#define IOCON_PIO0_1      offsetof(IOCON_TypeDef, PIO0_1)
#define IOCON_PIO0_2      offsetof(IOCON_TypeDef, PIO0_2)
#define IOCON_PIO0_3      offsetof(IOCON_TypeDef, PIO0_3) 
#define IOCON_PIO0_4      offsetof(IOCON_TypeDef, PIO0_4)
#define IOCON_PIO0_5      offsetof(IOCON_TypeDef, PIO0_5) 
#define IOCON_PIO0_6      offsetof(IOCON_TypeDef, PIO0_6) 
#define IOCON_PIO0_7      offsetof(IOCON_TypeDef, PIO0_7)
#define IOCON_PIO0_8      offsetof(IOCON_TypeDef, PIO0_8) 
#define IOCON_PIO0_9      offsetof(IOCON_TypeDef, PIO0_9)
#define IOCON_PIO0_10     offsetof(IOCON_TypeDef, JTAG_TCK_PIO0_10)
#define IOCON_PIO0_11     offsetof(IOCON_TypeDef, JTAG_TDI_PIO0_11)

#define IOCON_PIO1_0      offsetof(IOCON_TypeDef, JTAG_TMS_PIO1_0) 
#define IOCON_PIO1_1      offsetof(IOCON_TypeDef, JTAG_TDO_PIO1_1)
#define IOCON_PIO1_2      offsetof(IOCON_TypeDef, JTAG_nTRST_PIO1_2)
#define IOCON_PIO1_3      offsetof(IOCON_TypeDef, ARM_SWDIO_PIO1_3) 
#define IOCON_PIO1_4      offsetof(IOCON_TypeDef, PIO1_4) 
#define IOCON_PIO1_5      offsetof(IOCON_TypeDef, PIO1_5)
#define IOCON_PIO1_6      offsetof(IOCON_TypeDef, PIO1_6)
#define IOCON_PIO1_7      offsetof(IOCON_TypeDef, PIO1_7) 
#define IOCON_PIO1_8      offsetof(IOCON_TypeDef, PIO1_8) 
#define IOCON_PIO1_9      offsetof(IOCON_TypeDef, PIO1_9) 
#define IOCON_PIO1_10     offsetof(IOCON_TypeDef, PIO1_10) 
#define IOCON_PIO1_11     offsetof(IOCON_TypeDef, PIO1_11) 

#define IOCON_PIO2_0      offsetof(IOCON_TypeDef, PIO2_0)
#define IOCON_PIO2_1      offsetof(IOCON_TypeDef, PIO2_1)  
#define IOCON_PIO2_2      offsetof(IOCON_TypeDef, PIO2_2)
#define IOCON_PIO2_3      offsetof(IOCON_TypeDef, PIO2_3)
#define IOCON_PIO2_4      offsetof(IOCON_TypeDef, PIO2_4)
#define IOCON_PIO2_5      offsetof(IOCON_TypeDef, PIO2_5)
#define IOCON_PIO2_6      offsetof(IOCON_TypeDef, PIO2_6)
#define IOCON_PIO2_7      offsetof(IOCON_TypeDef, PIO2_7)
#define IOCON_PIO2_8      offsetof(IOCON_TypeDef, PIO2_8)
#define IOCON_PIO2_9      offsetof(IOCON_TypeDef, PIO2_9)
#define IOCON_PIO2_10     offsetof(IOCON_TypeDef, PIO2_10)
#define IOCON_PIO2_11     offsetof(IOCON_TypeDef, PIO2_11)

#define IOCON_PIO3_0      offsetof(IOCON_TypeDef, PIO3_0)
#define IOCON_PIO3_1      offsetof(IOCON_TypeDef, PIO3_1)
#define IOCON_PIO3_2      offsetof(IOCON_TypeDef, PIO3_2)
#define IOCON_PIO3_3      offsetof(IOCON_TypeDef, PIO3_3)
#define IOCON_PIO3_4      offsetof(IOCON_TypeDef, PIO3_4)
#define IOCON_PIO3_5      offsetof(IOCON_TypeDef, PIO3_5) 


/**
 * @brief Pin function mode enumeration (on-chip pull-up/pull-down resistor control)
 */
typedef enum
{
    PIN_MODE_Inactive = 0,    /** No pull-down/pull-up resistor enabled */
    PIN_MODE_PullDown,        /** Pull-down resistor enabled */
    PIN_MODE_PullUp,          /** Pull-up resistor enabled */
    PIN_MODE_Repeater,        /** Repeater mode */
}PIN_MODE_Typedef;

#define PARAM_MODE(n)    ((n==PIN_MODE_Inactive) || \
                          (n==PIN_MODE_PullDown) || \
                          (n==PIN_MODE_PullUp) || \
                          (n==PIN_MODE_Repeater))

#define IOCON_PIN_MODE_MASK  ((uint32_t)3<<3)

/**
 * @brief Pin function I2C mode
 */
typedef enum
{
    I2CMODE_SF = 0,      /** Standard mode/ Fast-mode I2C  with input glitch filter 
                             (this includes an open-drain output according to the I
                              2C-bus specification)*/
    
    I2CMODE_SIO,         /** Standard open-drain I/O functionality without input filter */
    
    I2CMODE_FP,          /** Fast-mode Plus with input glitch filter (this 
                             includes an open-drain output according to the I2C-bus 
                             specification). In this mode, the pins function as 
                             high-current sinks. */
}I2CMODE_Typedef;

#define PARAM_I2CMODE(n)  ((n==I2CMODE_SF) || \
                           (n==I2CMODE_SIO) || \
                           (n==I2CMODE_FP))

#define IOCON_I2CMODE_MASK     ((uint32_t)0x3<<8)


/**
 * @}
 */


/* Public Macros -------------------------------------------------------------- */
/** @defgroup IOCON_Public_Macros
 * @{
 */

/************************************PORT0****************************************/
#define PIO0_0_FUN_RESET           0     /** Selects function PIO */
#define PIO0_0_FUN_PIO             1     /** Selects function RESET */

#define PIO0_1_FUN_PIO             0     /** Selects function PIO */
#define PIO0_1_FUN_CLKOUT          1     /** Selects function CLKOUT */
#define PIO0_1_FUN_CT32B0_MAT2     2     /** Selects function CT32B0_MAT2 */

#define PIO0_2_FUN_PIO             0     /** Selects function PIO */
#define PIO0_2_FUN_SSEL0           1     /** Selects function SSEL0 */
#define PIO0_2_FUN_CT16B0_CAP0     2     /** Selects function CT16B0_CAP0 */

#define PIO0_3_FUN_PIO             0     /** Selects function PIO */

#define PIO0_4_FUN_PIO             0     /** Selects function PIO */
#define PIO0_4_FUN_SCL             1     /** Selects function SCL */

#define PIO0_5_FUN_PIO             0     /** Selects function PIO */
#define PIO0_5_FUN_SDA             1     /** Selects function SDA */

#define PIO0_6_FUN_PIO             0     /** Selects function PIO */
#define PIO0_6_FUN_SCK0            2     /** Selects function SCK0 */

#define PIO0_7_FUN_PIO             0     /** Selects function PIO */
#define PIO0_7_FUN_CTS             1     /** Selects function CTS */

#define PIO0_8_FUN_PIO             0     /** Selects function PIO */
#define PIO0_8_FUN_MISO0           1     /** Selects function MISO0 */
#define PIO0_8_FUN_CT16B0_MAT0     2     /** Selects function CT16B0_MAT0 */

#define PIO0_9_FUN_PIO             0     /** Selects function PIO */     
#define PIO0_9_FUN_MOSI0           1     /** Selects function MOSI0 */     
#define PIO0_9_FUN_CT16B0_MAT1     2     /** Selects function CT16B0_MAT1 */     

#define PIO0_10_FUN_SWCLK          0     /** Selects function SWCLK */
#define PIO0_10_FUN_PIO            1     /** Selects function PIO */
#define PIO0_10_FUN_SCK0           2     /** Selects function SCK0 */
#define PIO0_10_FUN_CT16B0_MAT2    3     /** Selects function MAT2 */ 

#define PIO0_11_FUN_TDI            0     /** Selects function TDI */ 
#define PIO0_11_FUN_PIO            1     /** Selects function PIO */ 
#define PIO0_11_FUN_AD0            2     /** Selects function AD0 */ 
#define PIO0_11_FUN_CT32B0_MAT3    3     /** Selects function CT32B0_MAT3 */ 

/************************************PORT1****************************************/
#define PIO1_0_FUN_TMS             0     /** Selects function TMS */
#define PIO1_0_FUN_PIO             1     /** Selects function PIO */
#define PIO1_0_FUN_AD1             2     /** Selects function AD1 */
#define PIO1_0_FUN_CT32B1_CAP0     3     /** Selects function CT32B1_CAP0 */

#define PIO1_1_FUN_TDO             0     /** Selects function TDO */
#define PIO1_1_FUN_PIO             1     /** Selects function PIO */
#define PIO1_1_FUN_AD2             2     /** Selects function AD2 */
#define PIO1_1_FUN_CT32B1_MAT0     3     /** Selects function CT32B1_MAT0 */

#define PIO1_2_FUN_TRST            0     /** Selects function TRST */
#define PIO1_2_FUN_PIO             1     /** Selects function PIO */
#define PIO1_2_FUN_AD3             2     /** Selects function AD3 */
#define PIO1_2_FUN_CT32B1_MAT1     3     /** Selects function CT32B1_MAT1 */

#define PIO1_3_FUN_SWDIO           0     /** Selects function SWDIO */
#define PIO1_3_FUN_PIO             1     /** Selects function PIO */
#define PIO1_3_FUN_AD4             2     /** Selects function AD4 */
#define PIO1_3_FUN_CT32B1_MAT2     3     /** Selects function CT32B1_MAT2 */ 

#define PIO1_4_FUN_PIO             0     /** Selects function PIO */
#define PIO1_4_FUN_AD5             1     /** Selects function AD5 */
#define PIO1_4_FUN_CT32B1_MAT3     2     /** Selects function CT32B1_MAT3 */

#define PIO1_5_FUN_PIO             0     /** Selects function PIO */
#define PIO1_5_FUN_RTS             1     /** Selects function RTS */
#define PIO1_5_FUN_CT32B0_CAP0     2     /** Selects function CT32B0_CAP0 */

#define PIO1_6_FUN_PIO             0     /** Selects function PIO */
#define PIO1_6_FUN_RXD             1     /** Selects function RXD */
#define PIO1_6_FUN_CT32B0_MAT0     2     /** Selects function CT32B0_MAT0 */

#define PIO1_7_FUN_PIO             0     /** Selects function PIO */
#define PIO1_7_FUN_TXD             1     /** Selects function TXD */
#define PIO1_7_FUN_CT32B0_MAT1     2     /** Selects function MAT1 */

#define PIO1_8_FUN_PIO             0     /** Selects function PIO */
#define PIO1_8_FUN_CT16B1_CAP0     1     /** Selects function CT16B1_CAP0 */

#define PIO1_9_FUN_PIO             0     /** Selects function PIO */
#define PIO1_9_FUN_CT16B1_MAT0     1     /** Selects function MAT0 */

#define PIO1_10_FUN_PIO            0     /** Selects function PIO */
#define PIO1_10_FUN_AD6            1     /** Selects function AD6 */
#define PIO1_10_FUN_CT16B1_MAT1    2     /** Selects function CT16B1_MAT1 */

#define PIO1_11_FUN_PIO            0     /** Selects function PIO */
#define PIO1_11_FUN_AD7            1     /** Selects function AD7 */

/************************************PORT2****************************************/
#define PIO2_0_FUN_PIO             0     /** Selects function PIO */
#define PIO2_0_FUN_DTR             1     /** Select function DTR */
#define PIO2_0_FUN_SSEL1           2     /** Select function SSEL1 */

#define PIO2_1_FUN_PIO             0     /** Selects function PIO */
#define PIO2_1_FUN_DSR             1     /** Selects function DSR */
#define PIO2_1_FUN_SCK1            2     /** Selects function SCK1 */

#define PIO2_2_FUN_PIO             0     /** Selects function PIO */
#define PIO2_2_FUN_DCD             1
#define PIO2_2_FUN_MISO1           2

#define PIO2_3_FUN_PIO_MOSI1       0     /** Selects function PIO */
#define PIO2_3_FUN_RI              1

#define PIO2_4_FUN_PIO             0     /** Selects function PIO */

#define PIO2_5_FUN_PIO             0     /** Selects function PIO */

#define PIO2_6_FUN_PIO             0     /** Selects function PIO */
    
#define PIO2_7_FUN_PIO             0     /** Selects function PIO */

#define PIO_2_8_FUN_PIO

#define PIO2_9_FUN_PIO             0     /** Selects function PIO */

#define PIO2_10_FUN_PIO            0     /** Selects function PIO */

#define PIO2_11_FUN_PIO            0     /** Selects function PIO */
#define PIO2_11_FUN_SCK0           1     /** Selects function SCK0 */

/************************************PORT3****************************************/
#define PIO3_0_FUN_PIO             0     /** Selects function PIO */
#define PIO3_0_FUN_DTR             1     /** Selects function DTR */

#define PIO3_1_FUN_PIO             0     /** Selects function PIO */

#define PIO3_2_FUN_PIO             0     /** Selects function PIO */
#define PIO3_2_FUN_DCD             1     /** Selects function DCD */


#define PIO3_3_FUN_PIO             0     /** Selects function PIO */
#define PIO3_3_FUN_RI              1     /** Selects function RI */

#define PIO3_4_FUN_PIO             0     /** Selects function PIO */

#define PIO3_5_FUN_PIO             0     /** Selects function PIO */

#define PIO_FUN_MASK               0x7


#define IOCON_PIN_HYS_MASK         ((uint32_t)1<<5)

/**
 * @}
 */

/* Public Functions ----------------------------------------------------------- */
/** @defgroup IOCON_Public_Functions
 * @{
 */

void IOCON_SCK0Locate(SCK0_Position_Typedef sck);
void IOCON_DSRLocate(DSR_Position_Typedef dsr);
void IOCON_DCDLocate(DCD_Position_Typedef dcd);
void IOCON_RILocate(RI_Position_Typedef ri);

void IOCON_SetPinFunc(uint32_t pin, uint8_t func);
void IOCON_SetPinMode(uint32_t pin, PIN_MODE_Typedef mod);
void IOCON_SetPinHys(uint32_t pin, FunctionalState hys);
void IOCON_SetI2CMode(uint32_t pin, I2CMODE_Typedef mod);
                                               
/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* LPC11XX_WDT_H_ */

/**
 * @}
 */

/* --------------------------------- End Of File ------------------------------ */
