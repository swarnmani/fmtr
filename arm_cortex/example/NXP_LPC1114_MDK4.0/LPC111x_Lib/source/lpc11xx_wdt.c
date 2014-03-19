/***********************************************************************//**
 * @file	: lpc11xx_wdt.c
 * @brief	: Contains all functions support for WDT firmware library on LPC11xx
 * @version	: 1.0
 * @date	: 22. Jan. 2010
 * @author	: Coocox
 **********************************************************************/

/* Peripheral group ----------------------------------------------------------- */
/** @addtogroup WDT
 * @{
 */

/* Includes ------------------------------------------------------------------- */
#include "lpc11xx_wdt.h"
#include "lpc11xx_syscon.h"
#include "lpc11xx_libcfg.h"


#if _WDT

/* Private Functions ---------------------------------------------------------- */
/** @defgroup WDT_Private_Functions
 * @{
 */

/********************************************************************//**
 * @brief 		Set WDT time out value and WDT mode
 * @param[in]	clk_source select Clock source for WDT device
 * @param[in]	timeout value of time-out for WDT (us)
 * @return		None
 *********************************************************************/
uint8_t WDT_SetTimeOut (uint32_t timeout)
{

	uint32_t pclk_wdt = 0;
	uint32_t tempval = 0;

    pclk_wdt = SYSCON_GetWDTClock();

    tempval  = (((pclk_wdt) / WDT_US_INDEX) * (timeout / 4));    
    
    if ((tempval >= WDT_TIMEOUT_MIN) && (tempval <= WDT_TIMEOUT_MAX)) {
        LPC_WDT->TC = tempval;
    	return	SUCCESS;
    }    

    return	ERROR;
}

/**
 * @}
 */


/* Public Functions ----------------------------------------------------------- */
/** @addtogroup WDT_Public_Functions
 * @{
 */


/*********************************************************************//**
* @brief 		Initial for Watchdog function
* 					Clock source = RTC ,
*
* @param[in]	ClkSrc  Select clock source
* 				 - SYSCON_WDT_CLK_IRC    : IRC oscillator
*                - SYSCON_WDT_CLK_MCK    : Main clock
*                - SYSCON_WDT_CLK_WDTOSC : Watchdog oscillator
*
* @param[in]	WDTMode WDT mode
* 				-	0: Use WDT to generate interrupt only
* 				-	1:WDT_MODE_RESET
* @return 		None
 **********************************************************************/
void WDT_Init (uint32_t WDTMode)
{
	CHECK_PARAM(PARAM_WDT_CLK_OPT(ClkSrc));
	CHECK_PARAM(PARAM_WDT_MODE_OPT(WDTMode));
	       
	//Set WDT mode
	if (WDTMode == WDT_MODE_RESET){
		LPC_WDT->MOD |= WDT_WDMOD(WDTMode);
	}
}


/**
 * @brief		Start WDT activity with given timeout value
 * @param[in]   TimeOut WDT reset after timeout if it is not feed
 * @return		None
 */
void WDT_Start(uint32_t TimeOut)
{
	WDT_SetTimeOut(TimeOut);
	//enable watchdog
	LPC_WDT->MOD |= WDT_WDMOD_WDEN;
	WDT_Feed();
}


/********************************************************************//**
 * @brief 		Read WDT Time out flag
 * @param		None
 * @return		Time out flag status of WDT
 *********************************************************************/
FlagStatus WDT_ReadTimeOutFlag (void)
{
    FlagStatus sta = RESET;
    if ((LPC_WDT->MOD & WDT_WDMOD_WDTOF) >>2) {
        sta = SET;
    } 
	return sta;
}

/********************************************************************//**
 * @brief 		Clear WDT Time out flag
 * @param		None
 * @return		None
 *********************************************************************/
void WDT_ClrTimeOutFlag (void)
{
	LPC_WDT->MOD &=~WDT_WDMOD_WDTOF;
}

/********************************************************************//**
 * @brief 		Update WDT timeout value and feed
 * @param[in]	TimeOut	TimeOut value to be updated
 * @return		None
 *********************************************************************/
void WDT_UpdateTimeOut ( uint32_t TimeOut)
{
	WDT_SetTimeOut(TimeOut);
	WDT_Feed();
}


/********************************************************************//**
 * @brief 		After set WDTEN, call this function to start Watchdog
 * 				or reload the Watchdog timer
 * @param	None
 *
 * @return		None
 *********************************************************************/
void WDT_Feed (void)
{
	// Disable irq interrupt
	__disable_irq();
	LPC_WDT->FEED = 0xAA;
	LPC_WDT->FEED = 0x55;
	// Then enable irq interrupt
	__enable_irq();
}

/********************************************************************//**
 * @brief 		Get the current value of WDT
 * @param		None
 * @return		current value of WDT
 *********************************************************************/
uint32_t WDT_GetCurrentCount(void)
{
	return LPC_WDT->TV;
}

/**
 * @}
 */

#endif  /* _WDT */

/**
 * @}
 */

/* --------------------------------- End Of File ------------------------------ */
