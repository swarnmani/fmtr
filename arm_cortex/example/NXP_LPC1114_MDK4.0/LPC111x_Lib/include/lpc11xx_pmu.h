/***********************************************************************//**
 * @file	: LPC11xx_PMU.h
 * @brief	: Contains all macro definitions and function prototypes
 * 				support for PMU firmware library on LPC11xx
 * @version	: 1.0
 * @date	: 21. Jan. 2010
 * @author	: Coocox
 **************************************************************************/

/* Peripheral group ----------------------------------------------------------- */
/** @defgroup PMU
 * @ingroup LPC1100CMSIS_FwLib_Drivers
 * @{
 */

#ifndef __LPC11XX_PMU_H
#define __LPC11XX_PMU_H

/* Includes ------------------------------------------------------------------- */
#include "LPC11xx.h"
#include "lpc_types.h"


#ifdef __cplusplus
extern "C"
{
#endif


/* Public Types --------------------------------------------------------------- */
/** @defgroup PMU_Public_Types
 * @{
 */


/**
 * @brief Sleep mode definitions
 */
typedef enum
{
	PMU_SLEEP_MODE = 0,		/**< ARM WFI will enter Sleep mode (ARM Cortex-M0 
                                 core powered-down). */                                 
	PMU_DEEP_SLEEP_MODE,	/**< ARM WFI will enter Sleep mode (clock to ARM 
                                 Cortex-M0 core turned off). */
} SLEEP_MODE_Type;

/**
 * @}
 */


/* Public Macros -------------------------------------------------------------- */
/** @defgroup GPIO_Public_Macros
 * @{
 */

#define PARAM_SLEEP_MODE(n) ((n==PMU_SLEEP_MODE) || (n==PMU_DEEP_SLEEP_MODE))

#define PARAM_IDEXLEN(m, n) ((m+n)<=5)


#define PMU_GPREG_NUM       5     /* Macro defines for GPREG number */

/** Macro to check the input idex parameters */
#define PARAM_IDEX(n)       (n<=4)

/* Macro defines for PMU PCON Register */
#define PMU_PCON_DPDEN      ((uint32_t)1<<1)   /**< Deep power-down mode enable */
#define PMU_PCON_DPDFLAG    ((uint32_t)1<<11)  /**< Deep power-down flag */

/* Macro defines for PMU DPREG4 Register */
#define PMU_DPREG4_DATA_MASK     ((uint32_t)0xFFFFF800) /**< PDREG4 GPDATA bit mask */
#define PMU_DPREG4_DATA          ((uint32_t)0x1FFFFF)   /**< PDREG4 GPDATA mask */
#define PMU_DPREG4_WAKEUPHYS     ((uint32_t)1<<10)      /**< WAKEUP pin hysteresis enable */


/**
 * @}
 */

    

/* Public Functions ----------------------------------------------------------- */
/** @defgroup PMU_Public_Functions
 * @{
 */

void PMU_SleepModeCon (SLEEP_MODE_Type mod);
FlagStatus PMU_GetDPFlag (void);
void PMU_ClearDPFlag (void);

void PMU_WakeupHysCmd (FunctionalState sta);

void PMU_WriteGPReg (uint8_t idex, uint32_t dat);
uint32_t PMU_ReadGPReg(uint8_t idex);
void PMU_WriteGPRegs (uint8_t idex, uint8_t len, uint32_t *buf);
void PMU_ReadGPRegs (uint8_t idex, uint8_t len, uint32_t *buf);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif
   
#endif /* __LPC11XX_PMU_H */

/**
 * @}
 */

/* --------------------------------- End Of File ------------------------------ */
