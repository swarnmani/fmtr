#include "lpc11xx_tmr.h"
#include "lpc11xx_gpio.h"
#include "lpc11xx_syscon.h"
#include "lpc11xx_iocon.h"
#include "lpc11xx_uart.h"
#include "lcd.h"
#include "DAC.h"


EVENT_InitTypeDef gpio_int_struct;
TIM_TIMERCFG_Type timer_config;
TIM_MATCHCFG_Type match_config;

static unsigned char blink;

void gpio_init_config(void);
void configTimer1(void);

uint32_t frequency;

int main ()
{
	int i, j;
//	TIM_TIMERCFG_Type timer_config;
//	TIM_MATCHCFG_Type match_config;
	UART_CFG_Type cfg;
	UART_FIFO_CFG_Type UARTFIFOConfigStruct;

	/******************** GPIO **********************************/
	SYSCON_AHBPeriphClockCmd(SYSCON_AHBPeriph_GPIO, ENABLE);
	GPIO_SetDir(PORT0, GPIO_Pin_7, 1);
	GPIO_SetDir(PORT3, GPIO_Pin_3, 0);

	IOCON_SetPinMode(IOCON_PIO3_3, PIN_MODE_PullUp);
	IOCON_SetPinMode(IOCON_PIO0_7, PIN_MODE_PullUp);
	/*************************************************************/

	/******************* LCD ***********************************/
	lcd_init();
	lcd_string(" ** Flow Meter ** ", 1);
	/************************************************************/

	/****************** 32 bit Counter ****************************/
	IOCON_SetPinFunc(IOCON_PIO1_5, PIO1_5_FUN_CT32B0_CAP0);
	SYSCON_AHBPeriphClockCmd(SYSCON_AHBPeriph_CT32B0, ENABLE);
	LPC_TMR32B0->CTCR = (1<<0);

//	LPC_TMR32B0->TCR = (1<<1);
//	LPC_TMR32B0->TCR = (1<<0);
	/***************************************************************/

	/****************** External Interrupt on GPIO *********************/
	gpio_init_config ();
	GPIO_EventInit(&gpio_int_struct);
	GPIO_PortIntCmd(PORT3, ENABLE);
	/*******************************************************************/

	/*************************** UART **************************************/
	/* Assign UART Pins */
	UART_PinsInit();

	cfg.Baud_rate = 115200;
	cfg.Parity = UART_PARITY_NONE;
	cfg.Databits = UART_DATABIT_8;
	cfg.Stopbits = UART_STOPBIT_1;
	UART_FIFOConfigStructInit(&UARTFIFOConfigStruct);

	UART_Init(LPC_UART, &cfg);
	UART_FIFOConfig(LPC_UART, &UARTFIFOConfigStruct);

	/* Enable Transmit */
	UART_TxCmd(LPC_UART,ENABLE);

	UART_Send(LPC_UART, (uint8_t *)"Hello, World!", sizeof("Hello, World!") - 1, NONE_BLOCKING);
	/************************************************************************/

	/******************************** SPI *********************************/
	DAC_SPI1_Config ();
	/***********************************************************************/

	/************************ 32 Bit Timer1 ******************************/
	NVIC_EnableIRQ(TIMER_32_1_IRQn);
	/* Configure Timer Prescale */
	timer_config.PrescaleOption = TIM_PRESCALE_TICKVAL;
	/* We have a 48MHz clock, so a prescale of 48000 will mean the main timer ticks every millisecond. */
	timer_config.PrescaleValue = 11999;
	/* Init! */
	TIM_Init(LPC_TMR32B1, TIM_TIMER_MODE, &timer_config);
	/* COnfigure Timer Match */
	/* Match on channel 0 */
	match_config.MatchChannel = 0;
	/* Interrupt on match */
	match_config.IntOnMatch =   TIM_INT_ON_MATCH(0);
	/* Reset the timer on match */
	match_config.ResetOnMatch = TIM_RESET_ON_MATCH(0);
	/* Match on a count of 75, so interrupt every 75 milliseconds */
	match_config.MatchValue = 4000U;
	/*  Config the match */
	TIM_ConfigMatch(LPC_TMR32B1, &match_config);
	/* Clear the timer, and then start it */
	TIM_Cmd(LPC_TMR32B1, TIM_RESET);
	TIM_Cmd(LPC_TMR32B1, TIM_ENABLE);
	/******************************************************************/
	while(1)
	{
		// DAC_SPI1_Write(0x0E8B); // 3V
		//DAC_SPI1_Write(0x09b2); // 2V
		//DAC_SPI1_Write(0x04D9); // 1V

		//idle
	}
}

void gpio_init_config (void)
{
	gpio_int_struct.port = PORT3;
	gpio_int_struct.pins = GPIO_Pin_3;
	gpio_int_struct.EVENT_Mode = EVENT_RISING_EDGE;
	gpio_int_struct.INTCmd = ENABLE;
}


void PIOINT3_IRQHandler(void)
{
	GPIO_ClearInt(PORT3, GPIO_Pin_3);
	GPIO_PortIntCmd(PORT3, DISABLE);

	TIM_Cmd(LPC_TMR32B1, TIM_RESET); // Start Timer1 for time
	TIM_Cmd(LPC_TMR32B1, TIM_ENABLE);

	LPC_TMR32B0->TCR = (1<<1); //start counter to count
	LPC_TMR32B0->TCR = (1<<0);
//	if(blink) {
//		GPIO_SetBits(PORT0, GPIO_Pin_7);
//	}
//	else {
//		GPIO_ResetBits(PORT0, GPIO_Pin_7);
//	}
//	blink ^= 1;
}


void TIMER32_1_IRQHandler(void)
{
	/*  Clear the pending interrupt */
	frequency = LPC_TMR32B0->TC;
	TIM_Cmd(LPC_TMR32B0, DISABLE);
	TIM_ClearIntPending(LPC_TMR32B1, TIM_MR0_INT);
	TIM_Cmd(LPC_TMR32B1, DISABLE);
	if(blink) {
			GPIO_SetBits(PORT0, GPIO_Pin_7);
	}
	else {
		GPIO_ResetBits(PORT0, GPIO_Pin_7);
	}
	blink ^= 1;
	lcd_string("F = ", 2);
	lcdwriteint(frequency, 5);
	//SSP_SendData(LPC_SSP1, (uint16_t)frequency);
	LPC_TMR32B0->TC = 0;
	GPIO_PortIntCmd(PORT3, ENABLE);
}
