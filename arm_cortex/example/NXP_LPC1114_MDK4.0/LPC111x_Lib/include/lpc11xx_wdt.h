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

#ifndef __LPC11XX_WDT_H_
#define __LPC11XX_WDT_H_

/* Includes ------------------------------------------------------------------- */
#include "LPC11xx.h"
#include "lpc_types.h"


#ifdef __cplusplus
extern "C"
{
#endif


/* Private Macros ------------------------------------------------------------- */
/** @defgroup WDT_Private_Macros
 * @{
 */

/** @defgroup WDT_REGISTER_BIT_DEFINITIONS
 * @{
 */
/************************** WDT Control **************************/
/** WDT interrupt enable bit */
#define WDT_WDMOD_WDEN			    ((uint32_t)(1<<0))
/** WDT interrupt enable bit */
#define WDT_WDMOD_WDRESET			((uint32_t)(1<<1))
/** WDT time out flag bit */
#define WDT_WDMOD_WDTOF				((uint32_t)(1<<2))
/** WDT Time Out flag bit */
#define WDT_WDMOD_WDINT				((uint32_t)(1<<3))
/** WDT Mode */
#define WDT_WDMOD(n)				((uint32_t)(1<<1))

/**************************** PRIVATE TYPES ***************************/
/** Define divider index for microsecond ( us ) */
#define WDT_US_INDEX	((uint32_t)(1000000))
/** WDT Time out minimum value */
#define WDT_TIMEOUT_MIN	((uint32_t)(0xFF))
/** WDT Time out maximum value */
#define WDT_TIMEOUT_MAX	((uint32_t)(0xFFFFFFFF))


/**************************** GLOBAL/PUBLIC TYPES ***************************/
/** Watchdog mode register mask */
#define WDT_WDMOD_MASK			(uint8_t)(0x02)
/** Watchdog timer constant register mask */
#define WDT_WDTC_MASK			(uint8_t)(0xFFFFFFFF)
/** Watchdog feed sequence register mask */
#define WDT_WDFEED_MASK 		(uint8_t)(0x000000FF)
/** Watchdog timer value register mask */
#define WDT_WDCLKSEL_MASK 		(uint8_t)(0x03)
/** Clock selected from internal RC */
#define WDT_WDCLKSEL_RC			(uint8_t)(0x00)
/** Clock selected from PCLK */
#define WDT_WDCLKSEL_PCLK		(uint8_t)(0x01)
/** Clock selected from external RTC */
#define WDT_WDCLKSEL_RTC		(uint8_t)(0x02)

/**
 * @}
 */

/**
 * @}
 */


/* Public Types --------------------------------------------------------------- */
/** @defgroup WDT_Public_Types
 * @{
 */

/** @brief Clock source option for WDT */
typedef enum {
	WDT_CLKSRC_IRC = 0, /*!< Clock source from Internal RC oscillator */
	WDT_CLKSRC_PCLK = 1, /*!< Selects the APB peripheral clock (PCLK) */
	WDT_CLKSRC_RTC = 2 /*!< Selects the RTC oscillator */
} WDT_CLK_OPT;
#define PARAM_WDT_CLK_OPT(OPTION)  ((OPTION ==WDT_CLKSRC_IRC)||\
								   (OPTION ==WDT_CLKSRC_IRC)||\
								   (OPTION ==WDT_CLKSRC_IRC))
/** @brief WDT operation mode */
typedef enum {
	WDT_MODE_INT_ONLY = 0, /*!< Use WDT to generate interrupt only */
	WDT_MODE_RESET = 1    /*!< Use WDT to generate interrupt and reset MCU */
} WDT_MODE_OPT;
#define PARAM_WDT_MODE_OPT(OPTION)  ((OPTION ==WDT_MODE_INT_ONLY)||\
								  (OPTION ==WDT_MODE_RESET))

/**
 * @}
 */


/* Public Functions ----------------------------------------------------------- */
/** @defgroup WDT_Public_Functions
 * @{
 */

void WDT_Init (uint32_t WDTMode);
void WDT_Start(uint32_t TimeOut);
void WDT_Feed (void);
FlagStatus WDT_ReadTimeOutFlag (void);
void WDT_ClrTimeOutFlag (void);
void WDT_UpdateTimeOut ( uint32_t TimeOut);
uint32_t WDT_GetCurrentCount(void);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __LPC11XX_WDT_H_ */

/**
 * @}
 */

/* --------------------------------- End Of File ------------------------------ */
