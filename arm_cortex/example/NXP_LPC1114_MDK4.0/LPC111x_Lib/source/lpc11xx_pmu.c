/***********************************************************************//**
 * @file	: lpc11xx_pmu.c
 * @brief	: Contains all functions support for PMU firmware library on LPC11xx
 * @version	: 1.0
 * @date	: 22. Jan. 2010
 * @author	: Coocox
 **********************************************************************/

/* Peripheral group ----------------------------------------------------------- */
/** @addtogroup PMU
 * @{
 */

/* Includes ------------------------------------------------------------------- */
#include "lpc11xx_pmu.h"
#include "lpc11xx_libcfg.h"

#if _PMU

/* Public Functions ---------------------------------------------------------- */
/** @defgroup GPIO_Public_Functions
 * @{
 */

/*********************************************************************//**
 * @brief		Select whether Sleep mode or Deep-sleep mode is entered 
                when using the ARM WFI instruction.
 * @param[in]	mod  Sleep mode, it can be
 *               - PMU_SLEEP_MODE      : ARM WFI will enter Sleep mode 
                    (ARM Cortex-M0 core powered-down)
                 - PMU_DEEP_SLEEP_MODE : ARM WFI will enter Deep-power 
                    down mode (clock to ARM Cortex-M0 core turned off)	
 * @return 		None
 **********************************************************************/
void PMU_SleepModeCon (SLEEP_MODE_Type mod)
{
    CHECK_PARAM (PARAM_SLEEP_MODE(mod));

    if(mod == PMU_DEEP_SLEEP_MODE) {
        LPC_PMU->PCON |= PMU_PCON_DPDEN;
    } else {
        LPC_PMU->PCON &= (~PMU_PCON_DPDEN);
    }   
}

/*********************************************************************//**
 * @brief		Check whether deep sleep mode entered or not
 * @param[in]	None 	
 * @return 		it can be:
 *                -SET   : Deep power-down mode entered
 *                -RESET : Deep power-down mode not entered.
 **********************************************************************/
FlagStatus PMU_GetDPFlag (void)
{
    FlagStatus sta;
    if (LPC_PMU->PCON & PMU_PCON_DPDFLAG) {
        sta = SET;
    } else {
        sta = RESET;
    }

    return sta;
}


/*********************************************************************//**
 * @brief		Check whether deep power-down mode entered or not
 * @param[in]	None 	
 * @return 		it can be:
 *                -SET   : Deep power-down mode entered
 *                -RESET : Deep power-down mode not entered.
 **********************************************************************/
void PMU_ClearDPFlag (void)
{
    LPC_PMU->PCON |= PMU_PCON_DPDFLAG;
}


/*********************************************************************//**
 * @brief		Write General purpose register 0 - 4
 *              GPREG0-3 are 32-bit, GPREG4 is 21-bit
 * @param[in]	idex : Index of General purpose register, it can be
                       0 - 4	 
 * @param[in]	dat  : Data written to GPREG 	
 * @return 		None
 **********************************************************************/
void PMU_WriteGPReg (uint8_t idex, uint32_t dat)
{
    uint32_t tmp;    

    CHECK_PARAM (PARAM_IDEX(idex));

    if(idex <= 3) {
        ((uint32_t *)(&LPC_PMU->GPREG0))[idex] = dat;
    } else if (idex == 4) {
        tmp = LPC_PMU->GPREG4 & (~PMU_DPREG4_DATA_MASK);
        LPC_PMU->GPREG4 = tmp | ((dat<<11) & PMU_DPREG4_DATA_MASK);
    }        
}


/*********************************************************************//**
 * @brief		Read General purpose register 0 - 4
 *              GPREG0-3 are 32-bit, GPREG4 is 21-bit
 * @param[in]	idex : Index of General purpose register, it can be
                       0 - 4	 
 * @param[in]	None	
 * @return 		The value of GPREG 
 **********************************************************************/
uint32_t PMU_ReadGPReg(uint8_t idex)
{
    uint32_t tmp = 0;    

    CHECK_PARAM (PARAM_IDEX(idex));

    if (idex <= 3) {
        tmp = ((uint32_t *)(&LPC_PMU->GPREG0))[idex];
    } else if (idex == 4){
        tmp = (LPC_PMU->GPREG4>>11) & PMU_DPREG4_DATA;        
    }    
    
    return tmp;  
}

/*********************************************************************//**
 * @brief		Write  multi General purpose register
 *              GPREG0-3 are 32-bit, GPREG4 is 21-bit
 * @param[in]	idex : Start index of General purpose register, it can be
                       0 - 4
                len  : Number of data 
                buf  : Data buffer written to GPREG        	 
 * @param[in]	None	
 * @return 		The value of GPREG 
 **********************************************************************/
void PMU_WriteGPRegs (uint8_t idex, uint8_t len, uint32_t *buf)
{
    uint8_t i;
    uint32_t tmp;
    
    CHECK_PARAM (PARAM_IDEX(idex));
    CHECK_PARAM (PARAM_IDEXLEN(idex, len));

    for(i=0; ((idex+i)<4) && (i<len); i++) {
        ((uint32_t *)&LPC_PMU->GPREG0)[i + idex] = buf[i];   
    }
    
    if (i<len) {     
        tmp = LPC_PMU->GPREG4 & (~PMU_DPREG4_DATA_MASK);
        LPC_PMU->GPREG4 = tmp | ((buf[idex + i]<<11) & PMU_DPREG4_DATA_MASK);
    }      
}

/*********************************************************************//**
 * @brief		Write  multi General purpose register
 *              GPREG0-3 are 32-bit, GPREG4 is 21-bit
 * @param[in]	idex : Start index of General purpose register, it can be
                       0 - 4
                len  : Number of data 
                buf  : Data buffer contains read data
 * @param[in]	None	
 * @return 		None
 **********************************************************************/
void PMU_ReadGPRegs (uint8_t idex, uint8_t len, uint32_t *buf)
{
    uint8_t i;

    CHECK_PARAM (PARAM_IDEX(idex));
    CHECK_PARAM (PARAM_IDEXLEN(idex, len));
    
     CHECK_PARAM (PARAM_IDEX(idex));
    CHECK_PARAM (PARAM_IDEXLEN(idex, len));

    for(i=0; ((idex+i)<4) && (i<len); i++) {
        buf[i] = ((uint32_t *)&LPC_PMU->GPREG0)[i + idex];   
    }
    
    if (i<len) {     
        buf[i] = (LPC_PMU->GPREG4>>11) & PMU_DPREG4_DATA;        
    } 
}


/*********************************************************************//**
 * @brief		Enable pin hysteresis enable
 *              GPREG0-3 are 32-bit, GPREG4 is 21-bit
 * @param[in]	sta : it can be
                 - ENABLE  : Hysteresis for WAKEUP pin enabled
                 - DISABLE : Hysteresis for WAKUP pin disabled 
 * @param[in]	None	
 * @return 		None
 **********************************************************************/
void PMU_WakeupHysCmd (FunctionalState sta)
{
    if(sta == ENABLE) {
        LPC_PMU->GPREG4 |= PMU_DPREG4_WAKEUPHYS;
    } else if (sta == DISABLE) {
        LPC_PMU->GPREG4 &= ~PMU_DPREG4_WAKEUPHYS;    
    }
}



/**
 * @}
 */

#endif /* _PMU */

/**
 * @}
 */

/* --------------------------------- End Of File ------------------------------ */

