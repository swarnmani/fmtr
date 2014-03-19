/***********************************************************************//**
 * @file	: lpc11xx_iocon.c
 * @brief	: Contains all functions support for IOCON firmware library on LPC11xx
 * @version	: 1.0
 * @date	: 26. Jan. 2010
 * @author	: Coocox
 **********************************************************************/

/* Peripheral group ----------------------------------------------------------- */
/** @addtogroup IOCON
 * @{
 */

/* Includes ------------------------------------------------------------------- */
#include "lpc11xx_iocon.h"
#include "lpc11xx_libcfg.h"


#if _IOCON


/* Public Functions ----------------------------------------------------------- */
/** @addtogroup IOCON_Public_Functions
 * @{
 */


/*********************************************************************//**
 * @brief 		Selects pin location for SCK0 pin
 * @param[in]	sck SCK0 pin position, it can be :
 *                -SCK_PIO0_10 : SWCLK/PIO0_10/SCK0/CT16B0_MAT2        
 *                -SCK_PIO2_11 : PIO2_11/SCK0
 *                -SCK_PIO0_6  : PIO0_6/SCK0
 * @param[in]	None
 * @return 		None
 **********************************************************************/
void IOCON_SCK0Locate(SCK0_Position_Typedef sck)
{
    CHECK_PARAM(PARAM_SCK(sck));
    LPC_IOCON->SCKLOC = sck;
}

/*********************************************************************//**
 * @brief 		Selects pin location for DSR pin
 * @param[in]	sck SCK0 pin position, it can be :
 *                -DSR_PIO2_1 : PIO2_1/DSR/SCK1     
 *                -DSR_PIO3_1 : PIO3_1/DSR
 * @param[in]	None
 * @return 		None
 **********************************************************************/
void IOCON_DSRLocate(DSR_Position_Typedef dsr)
{
    CHECK_PARAM(PARAM_DSR(dsr));
    LPC_IOCON->DSRLOC = dsr;
}


/*********************************************************************//**
 * @brief 		Selects pin location for DCD pin
 * @param[in]	sck SCK0 pin position, it can be :
 *                -DCD_PIO2_2 : PIO2_2/DCD/MISO1     
 *                -DCD_PIO3_2 : PIO3_2/DCD
 * @param[in]	None
 * @return 		None
 **********************************************************************/
void IOCON_DCDLocate(DCD_Position_Typedef dcd)
{
    CHECK_PARAM(PARAM_DCD(dcd));
    LPC_IOCON->DCDLOC = dcd;
}


/*********************************************************************//**
 * @brief 		Selects pin location for RI pin
 * @param[in]	sck RI pin position, it can be :
 *                -RI_PIO2_3 : PIO2_3/RI/MOSI1     
 *                -RI_PIO3_3 : PIO3_3/RI
 * @param[in]	None
 * @return 		None
 **********************************************************************/
void IOCON_RILocate(RI_Position_Typedef ri)
{
    CHECK_PARAM(PARAM_RI(ri));
    LPC_IOCON->RILOC = ri;
}


/********************************************************************//**
 * @brief 		Enable or Disable the port interrupt in NVIC
 * @param[in]	pin specifies the pin, it can be 
 *              IOCON_PIO0_0 - IOCON_PIO3_5
 * @param[in]	func, Selects pin function, it can be
 *              PIOx_x_FUN_xxx
 * @return		None
 *********************************************************************/
void IOCON_SetPinFunc(uint32_t pin, uint8_t func)
{
    uint32_t tmp;
    tmp = *(uint32_t *)((uint32_t)&(LPC_IOCON->PIO2_6) + pin);
    tmp &= ~PIO_FUN_MASK;
    tmp |= func & PIO_FUN_MASK;
    *(uint32_t *)((uint32_t)&(LPC_IOCON->PIO2_6) + pin) = tmp;
}


/********************************************************************//**
 * @brief 		Selects function mode (on-chip pull-up/pull-down resistor
 *               control).
 * @param[in]	pin specifies the pin, it can be 
 *              IOCON_PIO0_0 - IOCON_PIO3_5
 * @param[in]	mod, Selects function mode, it can be
 *               -PIN_MODE_Inactive : No pull-down/pull-up resistor enabled
 *               -PIN_MODE_PullDown : Pull-down resistor enabled 
 *               -PIN_MODE_PullUp   : Pull-up resistor enabled
 *               -PIN_MODE_Repeater : Repeater mode
 * @return		None
 *********************************************************************/
void IOCON_SetPinMode(uint32_t pin, PIN_MODE_Typedef mod)
{
    uint32_t tmp;
    
    CHECK_PARAM(PARAM_MODE(mod));

    tmp = *(uint32_t *)((uint32_t)&(LPC_IOCON->PIO2_6) + pin);
    tmp &= ~IOCON_PIN_MODE_MASK;
    tmp |= (mod<<3) & PIO_FUN_MASK;
    *(uint32_t *)((uint32_t)&(LPC_IOCON->PIO2_6) + pin) = tmp;
}


/********************************************************************//**
 * @brief 		Selects function mode (on-chip pull-up/pull-down resistor
 *               control).
 * @param[in]	pin specifies the pin, it can be 
 *              IOCON_PIO0_0 - IOCON_PIO3_5
 * @param[in]	hys, Enable or Disable hysteresis
 *               -ENABLE
 *               -DISABLE 
 * @return		None
 *********************************************************************/
void IOCON_SetPinHys(uint32_t pin, FunctionalState hys)
{
    uint32_t tmp;
     
    tmp = *(uint32_t *)((uint32_t)&(LPC_IOCON->PIO2_6) + pin);

    if(hys == DISABLE) {
        tmp &= ~IOCON_PIN_HYS_MASK;   
    } else {
        tmp |= IOCON_PIN_HYS_MASK;       
    }

    *(uint32_t *)((uint32_t)&(LPC_IOCON->PIO2_6) + pin) = tmp;
}


/********************************************************************//**
 * @brief 		Selects I2C mode , only for pins SDA and SCL
 * @param[in]	pin specifies the pin, it can be 
 *              IOCON_PIO0_0 - IOCON_PIO3_5
 * @param[in]	mod, i2c mode, it can be
 *               -I2CMODE_SF  : Standard mode/ Fast-mode I2C
 *               -I2CMODE_SIO : Standard I/O functionality
 *               -I2CMODE_FP  : Fast-mode Plus I2C
 * @return		None
 *********************************************************************/
void IOCON_SetI2CMode(uint32_t pin, I2CMODE_Typedef mod)
{
    uint32_t tmp;        

    CHECK_PARAM(PARAM_I2CMODE(mod));

    tmp = *(uint32_t *)((uint32_t)&(LPC_IOCON->PIO2_6) + pin);
    
    tmp &= ~IOCON_I2CMODE_MASK;   
    
    tmp |=  ((uint32_t)mod<<8) & IOCON_I2CMODE_MASK;
         
    *(uint32_t *)((uint32_t)&(LPC_IOCON->PIO2_6) + pin) = tmp;
}


/**
 * @}
 */

#endif  /* _IOCON */

/**
 * @}
 */

/* --------------------------------- End Of File ------------------------------ */
