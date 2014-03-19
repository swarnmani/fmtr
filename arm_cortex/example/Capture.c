#include "lpc11xx_tmr.h"
#include "lpc11xx_gpio.h"
#include "lpc11xx_syscon.h"


/**
 * 23-bit Counter/Timer0 Capture Function
 */
void TIMCaptureExp()
{
	TIM_TIMERCFG_Type TIM_ConfigStruct;
	TIM_CAPTURECFG_Type TIM_CaptureConfigStruct;

	/* Initialize timer 0, prescale count time of 1000uS = 1mS */
	TIM_ConfigStruct.PrescaleOption = TIM_PRESCALE_USVAL;
	TIM_ConfigStruct.PrescaleValue	= 1000;

	/* Enable capture on CAPn.0 rising edge */
	TIM_CaptureConfigStruct.RisingEdge = ENABLE;
	/* Enable capture on CAPn.0 falling edge */
	TIM_CaptureConfigStruct.FallingEdge = ENABLE;
	/* Generate capture interrupt */
	TIM_CaptureConfigStruct.IntOnCaption = ENABLE;

	/* Assign TMR32B0 Capture pin: PIO1_5 */
	TIM_CapturePins(LPC_TMR32B0);
	/* Set configuration for Tim_config and Tim_MatchConfig */
	TIM_Init(LPC_TMR32B0, TIM_TIMER_MODE,&TIM_ConfigStruct);
	TIM_ConfigCapture(LPC_TMR32B0, &TIM_CaptureConfigStruct);
	TIM_ResetCounter(LPC_TMR32B0);

	/* Enable interrupt for timer 0 */
	NVIC_EnableIRQ(TIMER_32_0_IRQn);

	/* Start 32-Bit Timer 0 */
	TIM_Cmd(LPC_TMR32B0, ENABLE);
}


/**
 * 23-bit Counter/Timer0 Interrupt Service Routine
 */
void TIMER32_0_IRQHandler(void)
{
	int val;

	TIM_ClearIntPending(LPC_TMR32B0,TIM_CR0_INT);

	val = TIM_GetCaptureValue(LPC_TMR32B0);

	//printf("Capture Value : %d", val);
}