/***********************************************************************//**
 * @file	: lpc11xx_tmr.c
 * @brief	: Contains all functions support for TMR16B and TMR32B firmware 
 *            library on LPC11xx
 * @version	: 1.0
 * @date	: 4. Feb. 2010
 * @author	: Coocox
 **********************************************************************/

/* Peripheral group ----------------------------------------------------------- */
/** @addtogroup TMR
 * @{
 */

/* Includes ------------------------------------------------------------------- */
#include "lpc11xx_libcfg.h"
#include "lpc11xx_tmr.h"
#include "lpc11xx_syscon.h"
#include "lpc11xx_iocon.h"

#if _TMR

/* Private Functions ---------------------------------------------------------- */
/** @defgroup TMR_Private_Functions
 * @{
 */

/*********************************************************************//**
 * @brief 		Convert a time to a timer count value
 * @param[in]	timernum Timer number
 * @param[in]	usec Time in microseconds
 * @return 		The number of required clock ticks to give the time delay
 **********************************************************************/
uint32_t TIM_ConverUSecToVal (uint32_t usec)
{
	uint64_t clkdlycnt;

	// Get Pclock of timer
	clkdlycnt = SystemAHBFrequency;

	clkdlycnt = (clkdlycnt * usec) / 1000000;
	return (uint32_t) clkdlycnt;
}

/**
 * @}
 */


/* Public Functions ----------------------------------------------------------- */
/** @addtogroup TMR_Public_Functions
 * @{
 */
  
/*********************************************************************//**
 * @brief 		Get Interrupt Status
 * @param[in]	TIMx Timer selection, should be LPC_TMR16B0, 
 *                   LPC_TMR16B1, LPC_TMR32B0, LPC_TMR32B1
 * @param[in]	IntFlag
 * @return 		FlagStatus
 * 				- SET : interrupt
 * 				- RESET : no interrupt
 **********************************************************************/
FlagStatus TIM_GetIntStatus(TMR_TypeDef *TIMx, uint8_t IntFlag)
{    
	CHECK_PARAM(PARAM_TIMx(TIMx));
	CHECK_PARAM(PARAM_TIM_INT_TYPE(IntFlag));
	
	if ((TIMx->IR)& TIM_IR_CLR(IntFlag)) {
        return SET;    
    }
		
	return RESET;

}

/*********************************************************************//**
 * @brief 		Clear Interrupt pending
 * @param[in]	TIMx Timer selection, should be LPC_TMR16B0, 
 *                   LPC_TMR16B1, LPC_TMR32B0, LPC_TMR32B1
 * @param[in]	IntFlag should be in TIM_INT_TYPE enum
 * @return 		None
 **********************************************************************/
void TIM_ClearIntPending(TMR_TypeDef *TIMx, uint8_t IntFlag)
{
	CHECK_PARAM(PARAM_TIMx(TIMx));
	CHECK_PARAM(PARAM_TIM_INT_TYPE(IntFlag));

	TIMx->IR = TIM_IR_CLR(IntFlag) 	;
}


/*********************************************************************//**
 * @brief	 	Start/Stop Timer/Counter device
 * @param[in]	TIMx Pointer to timer device, should be LPC_TMR16B0, 
 *                    LPC_TMR16B1, LPC_TMR32B0, LPC_TMR32B1
 * @param[in]	NewState
 * 				-	ENABLE  : set timer enable
 * 				-	DISABLE : disable timer
 * @return 		None
 **********************************************************************/
void TIM_Cmd(TMR_TypeDef *TIMx, FunctionalState NewState)
{
	CHECK_PARAM(PARAM_TIMx(TIMx));
	if (NewState == ENABLE) {
		TIMx->TCR	|=  TIM_ENABLE;
	} else {
		TIMx->TCR &= ~TIM_ENABLE;
	}
}

/*********************************************************************//**
 * @brief 		Reset Timer/Counter device,
 * 					Make TC and PC are synchronously reset on the next
 * 					positive edge of PCLK
 * @param[in]	TIMx Pointer to timer device, should be LPC_TMR16B0, 
 *                    LPC_TMR16B1, LPC_TMR32B0, LPC_TMR32B1
 * @return 		None
 **********************************************************************/
void TIM_ResetCounter(TMR_TypeDef *TIMx)
{
	CHECK_PARAM(PARAM_TIMx(TIMx));
	TIMx->TCR |= TIM_RESET;
	TIMx->TCR &= ~TIM_RESET;
}


/*********************************************************************//**
 * @brief 		Close Timer/Counter device
 * @param[in]	TIMx  Pointer to timer device, should be LPC_TMR16B0, 
 *                    LPC_TMR16B1, LPC_TMR32B0, LPC_TMR32B1
 * @return 		None
 **********************************************************************/
void TIM_DeInit (TMR_TypeDef *TIMx)
{
	CHECK_PARAM(PARAM_TIMx(TIMx));

	// Disable timer/counter
	TIMx->TCR = 0x00;

	// Disable power
    if       (TIMx == LPC_TMR16B0) {    //  16-bit counter/timer 0
        SYSCON_AHBPeriphClockCmd(SYSCON_AHBPeriph_CT16B0, DISABLE);
    } else if(TIMx == LPC_TMR16B1) {    //  16-bit counter/timer 1
        SYSCON_AHBPeriphClockCmd(SYSCON_AHBPeriph_CT16B1, DISABLE);    
    } else if(TIMx == LPC_TMR32B0) {    //  32-bit counter/timer 0
        SYSCON_AHBPeriphClockCmd(SYSCON_AHBPeriph_CT32B0, DISABLE);    
    } else if(TIMx == LPC_TMR32B1) {    //  32-bit counter/timer 1
        SYSCON_AHBPeriphClockCmd(SYSCON_AHBPeriph_CT32B1, DISABLE);    
    }    	
}


/*********************************************************************//**
 * @brief 		Initial Timer/Counter device
 * 				 	Set Clock frequency for ADC
 * 					Set initial configuration for ADC
 * @param[in]	TIMx  Timer selection, should be LPC_TMR16B0, LPC_TMR16B1
 *                    LPC_TMR32B0, LPC_TMR32B1
 * @param[in]	TimerCounterMode TIM_MODE_OPT
 * @param[in]	TIM_ConfigStruct pointer to TIM_TIMERCFG_Type
 * 				that contains the configuration information for the
 *                    specified Timer peripheral.
 * @return 		None
 **********************************************************************/
void TIM_Init(TMR_TypeDef *TIMx, uint8_t TimerCounterMode, void *TIM_ConfigStruct)
{
	TIM_TIMERCFG_Type *pTimeCfg;
	TIM_COUNTERCFG_Type *pCounterCfg;
    uint32_t val;

	CHECK_PARAM(PARAM_TIMx(TIMx));
	CHECK_PARAM(PARAM_TIM_MODE_OPT(TimerCounterMode));

	// Set power
    if(TIMx == LPC_TMR16B0) {
        SYSCON_AHBPeriphClockCmd(SYSCON_AHBPeriph_CT16B0, ENABLE);    

    } else if(TIMx == LPC_TMR16B1) {
        SYSCON_AHBPeriphClockCmd(SYSCON_AHBPeriph_CT16B1, ENABLE);    
    
    } else if(TIMx == LPC_TMR32B0) {
        SYSCON_AHBPeriphClockCmd(SYSCON_AHBPeriph_CT32B0, ENABLE);    
    
    } else if(TIMx == LPC_TMR32B1) {
        SYSCON_AHBPeriphClockCmd(SYSCON_AHBPeriph_CT32B1, ENABLE);        
    } 
	
	TIMx->CCR &= ~TIM_CTCR_MODE_MASK;
	TIMx->CCR |= TimerCounterMode;

	TIMx->TC =0;
	TIMx->PC =0;
	TIMx->PR =0;

	if (TimerCounterMode == TIM_TIMER_MODE )
	{
		pTimeCfg = (TIM_TIMERCFG_Type *)TIM_ConfigStruct;
		if (pTimeCfg->PrescaleOption  == TIM_PRESCALE_TICKVAL) {
			val = pTimeCfg->PrescaleValue -1  ;            
		} else {
            val = TIM_ConverUSecToVal (pTimeCfg->PrescaleValue)-1;
		}

        if ((TIMx == LPC_TMR16B0) || (TIMx == LPC_TMR16B1)) {
            val &= 0xFFFF;
        }

        TIMx->PR = val;
	} else {
		pCounterCfg = (TIM_COUNTERCFG_Type *)TIM_ConfigStruct;
		TIMx->CCR  &= ~TIM_CTCR_INPUT_MASK;
		if (pCounterCfg->CountInputSelect == TIM_COUNTER_INCAP1)
			TIMx->CCR |= _BIT(2);
	}

	// Clear interrupt pending
	TIMx->IR = 0x3F;
}


/*********************************************************************//**
* @brief 		Configuration for Timer at initial time
* @param[in] 	TimerCounterMode Should be :
* 					- PrescaleOption = TC_PRESCALE_USVAL,
* 					- PrescaleValue = 1
* 				Counter mode with
* 					- Caption channel 0
* @param[in] 	TIM_ConfigStruct pointer to TIM_TIMERCFG_Type or
* 				TIM_COUNTERCFG_Type
* @return 		None
 **********************************************************************/
void TIM_ConfigStructInit(uint8_t TimerCounterMode, void *TIM_ConfigStruct)
{
	if (TimerCounterMode == TIM_TIMER_MODE ) {
		TIM_TIMERCFG_Type * pTimeCfg = (TIM_TIMERCFG_Type *)TIM_ConfigStruct;
		pTimeCfg->PrescaleOption = TIM_PRESCALE_USVAL;
		pTimeCfg->PrescaleValue = 1;
	} else {
		TIM_COUNTERCFG_Type * pCounterCfg = (TIM_COUNTERCFG_Type *)TIM_ConfigStruct;
		pCounterCfg->CountInputSelect = TIM_COUNTER_INCAP0;

	}
}


/*********************************************************************//**
 * @brief 		Configuration for Match register
 * @param[in]	TIMx Pointer to timer device
 * @param[in]   TIM_MatchConfigStruct Pointer to TIM_MATCHCFG_Type
 * 					- MatchChannel : choose channel 0 or 1
 * 					- IntOnMatch	 : if SET, interrupt will be generated when MRxx match
 * 									the value in TC
 * 					- StopOnMatch	 : if SET, TC and PC will be stopped whenM Rxx match
 * 									the value in TC
 * 					- ResetOnMatch : if SET, Reset on MR0 when MRxx match
 * 									the value in TC
 * 					-ExtMatchOutputType: Select output for external match
 * 						 +	 0:	Do nothing for external output pin if match
 *						 +   1:	Force external output pin to low if match
 *						 + 	 2: Force external output pin to high if match
 *						 + 	 3: Toggle external output pin if match
 *					MatchValue: Set the value to be compared with TC value
 * @return 		None
 **********************************************************************/
void TIM_ConfigMatch(TMR_TypeDef *TIMx, TIM_MATCHCFG_Type *TIM_MatchConfigStruct)
{    
	CHECK_PARAM(PARAM_TIMx(TIMx));
	CHECK_PARAM(PARAM_TIM_EXTMATCH_OPT(TIM_MatchConfigStruct->ExtMatchOutputType));

	switch(TIM_MatchConfigStruct->MatchChannel)
	{
	case 0:
		TIMx->MR0 = TIM_MatchConfigStruct->MatchValue & 0xFFFF;
		break;
	case 1:
		TIMx->MR1 = TIM_MatchConfigStruct->MatchValue & 0xFFFF;
		break;
    case 2:
		TIMx->MR2 = TIM_MatchConfigStruct->MatchValue;
		break;
    case 3:
		TIMx->MR3 = TIM_MatchConfigStruct->MatchValue;
		break;
	}

	//interrupt on MRn
	TIMx->MCR &=~TIM_MCR_CHANNEL_MASKBIT(TIM_MatchConfigStruct->MatchChannel);

	if (TIM_MatchConfigStruct->IntOnMatch)
		TIMx->MCR |= TIM_INT_ON_MATCH(TIM_MatchConfigStruct->MatchChannel);

	//reset on MRn
	if (TIM_MatchConfigStruct->ResetOnMatch)
		TIMx->MCR |= TIM_RESET_ON_MATCH(TIM_MatchConfigStruct->MatchChannel);

	//stop on MRn
	if (TIM_MatchConfigStruct->StopOnMatch)
		TIMx->MCR |= TIM_STOP_ON_MATCH(TIM_MatchConfigStruct->MatchChannel);

	// match output type

	TIMx->EMR &= ~TIM_EM_MASK(TIM_MatchConfigStruct->MatchChannel);
	TIMx->EMR |= TIM_EM_SET(TIM_MatchConfigStruct->MatchChannel,TIM_MatchConfigStruct->ExtMatchOutputType);
}


/*********************************************************************//**
 * @brief 		Configuration for Capture register
 * @param[in]	TIMx Pointer to timer device, can be LPC_TMR16B0, 
 *                   LPC_TMR16B1, LPC_TMR32B0, LPC_TMR32B1       
 * @param[in]   TIM_CaptureConfigStruct	Pointer to TIM_CAPTURECFG_Type
 *                  - CaptureChannel: set the channel to capture data
 * 					- RisingEdge    : if SET, Capture at rising edge
 * 					- FallingEdge	: if SET, Capture at falling edge
 * 					- IntOnCaption  : if SET, Capture generate interrupt
 * @return 		None
 **********************************************************************/
void TIM_ConfigCapture(TMR_TypeDef *TIMx, TIM_CAPTURECFG_Type *TIM_CaptureConfigStruct)
{
	CHECK_PARAM(PARAM_TIMx(TIMx));
	
	TIMx->CCR &= ~TIM_CCR_CHANNEL_MASKBIT(0);

	if (TIM_CaptureConfigStruct->RisingEdge) {
        TIMx->CCR |= TIM_CAP_RISING(0);    
    }
		
	if (TIM_CaptureConfigStruct->FallingEdge) {
        TIMx->CCR |= TIM_CAP_FALLING(0);
    }
		
	if (TIM_CaptureConfigStruct->IntOnCaption) {
        TIMx->CCR |= TIM_INT_ON_CAP(0);    
    }		
}

/*********************************************************************//**
 * @brief 		Read value of capture register in timer/counter device
 * @param[in]	TIMx Pointer to timer/counter device, can be LPC_TMR16B0,
 *                   LPC_TMR16B1, LPC_TMR32B0, LPC_TMR32B1 
 * @return 		Value of capture register
 **********************************************************************/
uint32_t TIM_GetCaptureValue(TMR_TypeDef *TIMx)
{
    uint32_t val;
	CHECK_PARAM(PARAM_TIMx(TIMx));
	CHECK_PARAM(PARAM_TIM_COUNTER_INPUT_OPT(CaptureChannel));
    
    val = TIMx->CR0;
	if((TIMx == LPC_TMR16B0) || (TIMx == LPC_TMR16B1)) {
        val &= 0xFFFF;                
    } 

    return val;
}


/*********************************************************************//**
 * @brief 		Assign Capture Signals
 *                - CT16B0_CAP0 : PIO0_2
 *                - CT16B1_CAP0 : PIO1_8
 *                - CT32B0_CAP0 : PIO1_5
 *                - CT32B1_CAP0 : PIO1_0
 * @param[in]	TIMx Pointer to timer/counter device, can be LPC_TMR16B0,
 *                   LPC_TMR16B1, LPC_TMR32B0, LPC_TMR32B1 
 * @return 		None
 **********************************************************************/
void TIM_CapturePins(TMR_TypeDef *TIMx)
{
    CHECK_PARAM(PARAM_TIMx(TIMx));

    if        (TIMx == LPC_TMR16B0) {  /** CT16B0_CAP0 */
        IOCON_SetPinFunc(IOCON_PIO0_2, PIO0_2_FUN_CT16B0_CAP0);

    } else if (TIMx == LPC_TMR16B1) {  /** CT16B1_CAP0 */
        IOCON_SetPinFunc(IOCON_PIO1_8, PIO1_8_FUN_CT16B1_CAP0);
            
    } else if (TIMx == LPC_TMR32B0) {  /** CT32B0_CAP0 */
        IOCON_SetPinFunc(IOCON_PIO1_5, PIO1_5_FUN_CT32B0_CAP0); 
               
    } else if (TIMx == LPC_TMR32B1) {  /** CT32B1_CAP0 */
        IOCON_SetPinFunc(IOCON_PIO1_0, PIO1_0_FUN_CT32B1_CAP0);        
    }
}


/*********************************************************************//**
 * @brief 		Assign External Match Output Pins
 * @param[in]	TIMx Pointer to timer/counter device, can be LPC_TMR16B0,
 *                   LPC_TMR16B1, LPC_TMR32B0, LPC_TMR32B1, pins assgign: 
 *                  16-bit Counter/Timer 0
 *                      - MAT0 : PIO0_8
 *                      - MAT1 : PIO0_9
 *                      - MAT2 : PIO0_10
 *                      - MAT3 : None pin out
 *                  16-bit Counter/Timer 1
 *                      - MAT0 : PIO1_9
 *                      - MAT1 : PIO1_10
 *                      - MAT2 : None pin out
 *                      - MAT3 : None pin out
 *                  32-bit Counter/Timer 0
 *                      - MAT0 : PIO1_6
 *                      - MAT1 : PIO1_7
 *                      - MAT2 : PIO0_1
 *                      - MAT3 : PIO0_11
 *                  32-bit Counter/Timer 1
 *                      - MAT0 : PIO1_1
 *                      - MAT1 : PIO1_2
 *                      - MAT2 : PIO1_3
 *                      - MAT3 : PIO1_4
 * @param[in]	matFlag, external Match Output, can be:
 *                   - TIM_PINS_MAT0 : External Match Output 0
 *                   - TIM_PINS_MAT1 : External Match Output 1 
 *                   - TIM_PINS_MAT2 : External Match Output 2 
 *                   - TIM_PINS_MAT3 : External Match Output 3
 * @return 		None
 **********************************************************************/
void TIM_MatchPins(TMR_TypeDef *TIMx, uint8_t matFlag)
{
    CHECK_PARAM(PARAM_TIMx(TIMx));
    CHECK_PARAM(PARAM_TIM_MAT_PINS(matFlag));
    
    // 16-bit counter/timer 0 external Match Output 
    if (TIMx == LPC_TMR16B0) {
        switch(matFlag) {
        case TIM_PINS_MAT0:
            IOCON_SetPinFunc(IOCON_PIO0_8, PIO0_8_FUN_CT16B0_MAT0); break;
        case TIM_PINS_MAT1:
            IOCON_SetPinFunc(IOCON_PIO0_9, PIO0_9_FUN_CT16B0_MAT1); break;
        case TIM_PINS_MAT2:
            IOCON_SetPinFunc(IOCON_PIO0_10, PIO0_10_FUN_CT16B0_MAT2); break;
        case TIM_PINS_MAT3:
            break;
        }    
    
    // 16-bit counter/timer 1 external Match Output 
    } else
    if (TIMx == LPC_TMR16B1) {
        switch(matFlag) {
        case TIM_PINS_MAT0:
            IOCON_SetPinFunc(IOCON_PIO1_9, PIO1_9_FUN_CT16B1_MAT0); break;
        case TIM_PINS_MAT1:
            IOCON_SetPinFunc(IOCON_PIO1_10, PIO1_10_FUN_CT16B1_MAT1); break;
        case TIM_PINS_MAT2:            
        case TIM_PINS_MAT3:
            break;
        }
    
    // 32-bit counter/timer 0 external Match Output 
    } else
    if (TIMx == LPC_TMR32B0) {
        switch(matFlag) {
        case TIM_PINS_MAT0:
            IOCON_SetPinFunc(IOCON_PIO1_6, PIO1_6_FUN_CT32B0_MAT0); break;
        case TIM_PINS_MAT1:
            IOCON_SetPinFunc(IOCON_PIO1_7, PIO1_7_FUN_CT32B0_MAT1); break;
        case TIM_PINS_MAT2:            
            IOCON_SetPinFunc(IOCON_PIO0_1, PIO0_1_FUN_CT32B0_MAT2); break;
        case TIM_PINS_MAT3:
            IOCON_SetPinFunc(IOCON_PIO0_11, PIO0_11_FUN_CT32B0_MAT3); break;
       }
    
    // 32-bit counter/timer 1 external Match Output 
    } else
    if (TIMx == LPC_TMR32B1) {
        switch(matFlag) {
        case TIM_PINS_MAT0:
            IOCON_SetPinFunc(IOCON_PIO1_1, PIO1_1_FUN_CT32B1_MAT0); break;
        case TIM_PINS_MAT1:
            IOCON_SetPinFunc(IOCON_PIO1_2, PIO1_2_FUN_CT32B1_MAT1); break;
        case TIM_PINS_MAT2:            
            IOCON_SetPinFunc(IOCON_PIO1_3, PIO1_3_FUN_CT32B1_MAT2); break;
        case TIM_PINS_MAT3:
            IOCON_SetPinFunc(IOCON_PIO1_4, PIO1_4_FUN_CT32B1_MAT3); break;
       }
    } 
        
}


/**
 * @}
 */

#endif /* _TMR */

/**
 * @}
 */

/* --------------------------------- End Of File ------------------------------ */
