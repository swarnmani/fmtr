#include "lpc11xx_syscon.h"
#include "lpc11xx_gpio.h"
#include "lcd.h"
#include "lpc11xx_tmr.h"

static unsigned char blink;

int main()
{
	//int i, j;

	TIM_TIMERCFG_Type timer_config;
	TIM_MATCHCFG_Type match_config;

	NVIC_EnableIRQ(TIMER_32_0_IRQn);

	/* Configure Timer Prescale */
	timer_config.PrescaleOption = TIM_PRESCALE_TICKVAL;
	/* We have a 48MHz clock, so a prescale of 48000 will mean the main timer ticks every millisecond. */
	timer_config.PrescaleValue = 12000U;
	/* Init! */
	TIM_Init(LPC_TMR32B0, TIM_TIMER_MODE, &timer_config);
		/* COnfigure Timer Match */
	/* Match on channel 0 */
	match_config.MatchChannel = 0;
	/* Interrupt on match */
	match_config.IntOnMatch =   TIM_INT_ON_MATCH(0);
	/* Reset the timer on match */
	match_config.ResetOnMatch = TIM_RESET_ON_MATCH(0);
	/* Match on a count of 75, so interrupt every 75 milliseconds */
	match_config.MatchValue = 3000U;
	/*  Config the match */
	TIM_ConfigMatch(LPC_TMR32B0, &match_config);
	/* Clear the timer, and then start it */
	TIM_Cmd(LPC_TMR32B0, TIM_RESET);
	TIM_Cmd(LPC_TMR32B0, TIM_ENABLE);

	/* Enable GPIO block clock */
	SYSCON_AHBPeriphClockCmd(SYSCON_AHBPeriph_GPIO, ENABLE);

	/* If PIO2_9 had been set to other function, set it to PIO function.
	 * NOTE: Component IOCON should be checked */
	//IOCON_SetPinFunc(IOCON_PIO2_9, PIO2_9_FUN_PIO);

	/* Set PIO2_9 as output. */
	GPIO_SetDir(PORT3, GPIO_Pin_4, 1);
	GPIO_SetDir(PORT0, GPIO_Pin_7, 1);
	lcd_init();
	//_delay_ms(10);
	lcd_string("***Flow Meter***", 1);
	while(1) {
		;
	}
}

void TIMER32_0_IRQHandler(void)
{
	if(blink) {
		GPIO_SetBits(PORT3, GPIO_Pin_4);
		GPIO_SetBits(PORT0, GPIO_Pin_7);
	}
	else {
		GPIO_ResetBits(PORT3, GPIO_Pin_4);
		GPIO_ResetBits(PORT0, GPIO_Pin_7);
	}
	blink ^= 1;

	/*  Clear the pending interrupt */
	TIM_ClearIntPending(LPC_TMR32B0, TIM_MR0_INT);
}


#include "lpc11xx_tmr.h"
#include "lpc11xx_gpio.h"
#include "lpc11xx_syscon.h"
#include "lcd.h"

void TIMCaptureExp();
/**
 * 23-bit Counter/Timer0 Capture Function
 */
static unsigned char blink;

int main(void)
{
	/* Enable GPIO block clock */
		SYSCON_AHBPeriphClockCmd(SYSCON_AHBPeriph_GPIO, ENABLE);

		/* If PIO2_9 had been set to other function, set it to PIO function.
		 * NOTE: Component IOCON should be checked */
		//IOCON_SetPinFunc(IOCON_PIO2_9, PIO2_9_FUN_PIO);

		/* Set PIO2_9 as output. */
		GPIO_SetDir(PORT3, GPIO_Pin_4, 1);
		GPIO_SetDir(PORT0, GPIO_Pin_7, 1);
		lcd_init();
		//_delay_ms(10);

		TIMCaptureExp();

//	TIM_TIMERCFG_Type TIM_ConfigStruct;
//	TIM_CAPTURECFG_Type TIM_CaptureConfigStruct;
//
//	/* Initialize timer 0, prescale count time of 1000uS = 1mS */
//	TIM_ConfigStruct.PrescaleOption = TIM_PRESCALE_USVAL;
//	TIM_ConfigStruct.PrescaleValue	= 1000;
//
//	/* Enable capture on CAPn.0 rising edge */
//	TIM_CaptureConfigStruct.RisingEdge = ENABLE;
//	/* Enable capture on CAPn.0 falling edge */
//	TIM_CaptureConfigStruct.FallingEdge = ENABLE;
//	/* Generate capture interrupt */
//	TIM_CaptureConfigStruct.IntOnCaption = ENABLE;
//
//	/* Assign TMR32B0 Capture pin: PIO1_5 */
//	TIM_CapturePins(LPC_TMR32B0);
//	/* Set configuration for Tim_config and Tim_MatchConfig */
//	TIM_Init(LPC_TMR32B0, TIM_TIMER_MODE,&TIM_ConfigStruct);
//	TIM_ConfigCapture(LPC_TMR32B0, &TIM_CaptureConfigStruct);
//	TIM_ResetCounter(LPC_TMR32B0);
//
//	/* Enable interrupt for timer 0 */
//	NVIC_EnableIRQ(TIMER_32_0_IRQn);
//
//	/* Start 32-Bit Timer 0 */
//	TIM_Cmd(LPC_TMR32B0, ENABLE);
//	//automatically added by CoIDE
//	TIMCaptureExp();

	while(1) {
		;
	}
}

void TIMER32_0_IRQHandler(void)
{
	int val;

	TIM_ClearIntPending(LPC_TMR32B0,TIM_CR0_INT);

	val = TIM_GetCaptureValue(LPC_TMR32B0);
	if(blink) {
		GPIO_SetBits(PORT3, GPIO_Pin_4);
		GPIO_SetBits(PORT0, GPIO_Pin_7);
	}
	else {
		GPIO_ResetBits(PORT3, GPIO_Pin_4);
		GPIO_ResetBits(PORT0, GPIO_Pin_7);
	}
	blink ^= 1;
	TIM_ClearIntPending(LPC_TMR32B0, TIM_MR0_INT);
}

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
	lcd_string("***Flow Meter***", 1);
}
