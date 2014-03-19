/****************************************************************************
 *   $Id:: main.c 1828 2012-07-10 14:48:18Z ToolPC JBK                      $
 *   Project: NXP LPC11xx CMP example
 *
 *   Description:
 *     This file contains Comparator test code example to test
 *     Comparator initialization, COMP interrupt handler, and APIs.
 *
 ****************************************************************************
* Software that is described herein is for illustrative purposes only
* which provides customers with programming information regarding the
* products. This software is supplied "AS IS" without any warranties.
* NXP Semiconductors assumes no responsibility or liability for the
* use of the software, conveys no license or title under any patent,
* copyright, or mask work right to the product. NXP Semiconductors
* reserves the right to make changes in the software without
* notification. NXP Semiconductors also make no representation or
* warranty that such application will be suitable for the specified
* use without further testing or modification.

* Permission to use, copy, modify, and distribute this software and its 
* documentation is hereby granted, under NXP Semiconductors� 
* relevant copyright in the software, without fee, provided that it 
* is used in conjunction with NXP Semiconductors microcontrollers.  This 
* copyright, permission, and disclaimer notice must appear in all copies of 
* this code.

****************************************************************************/

#include "LPC11Axx.h"					/* LPC11Axx definitions */
#include "uart.h"						/* UART driver */
#include "drv_hd44780.h"				/* LCD driver */
#include <stdio.h>

typedef enum _AppState
{
	Calibrating = 0,					/* Frequency counter is in calibration mode */
	ProcessCalibrate,					/* Calibration finished, process result */
	NormalOperation,					/* Measure frequency */
	DisplayFreq,						/* Keep measuring frequency, display reguency and duty cycle */
} AppState;

void SysTick_Handler (void);			/* Configured to generate an interrupt every 1/128th second */

volatile AppState State;				/* Variable to keep track of state of the application */
volatile uint32_t ms78Counter;			/* Counter incremented every 1/128th second */
volatile uint32_t DC;					/* Variable to store measured duty cycle */
volatile uint32_t CounterValue;			/* Variable to store counter value for frequency measurement */
volatile uint32_t PrevCounterValue;		/* Variable to store previous counter value for frequency measurement */

/******************************************************************************
**   Main Function  main()
******************************************************************************/
int main (void)
{
	uint8_t i;								/* Variable used for delay */
	uint8_t LAD;							/* Variable used for configuring voltage ladder */
	uint8_t LowestVal = 32, HighestVal = 0;	/* Variables used for auto-calibration */
	uint8_t ToggleDisplay = 0;				/* Variable used to toggle between frequency and duty cycle on display */
	volatile uint32_t Frequency;			/* Variable to store measured frequency */
	char String[9];							/* Display buffer */

#if defined(__IAR_SYSTEMS_ICC__)
	SystemInit();							/* Call SystemInit when using IAR. LPCXpresso and Keil do that by startup code */
#endif
	SystemCoreClockUpdate();				/* Update clock */

	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<9)|(1<<10)|(1<<20);	/* Enable clock for CT32B0, CT32B1, ACOMP  */
	LPC_SYSCON->PDRUNCFG &= ~(1<<16);						/* Enable power for analog comparator */

	LPC_IOCON->PIO0_16 = 0x02;				/* Configure PIO0_16 as ACMP_I3 */

	UARTInit(115200);						/* Initialize UART at 115200 8n1 */

	/* Initialize display */
	HD44780_IO_Init();
	HD44780_PowerUpInit();

	/* Configure systick timer to generate interrupt every 1/128th second */
	SysTick->LOAD = SystemCoreClock/128;
	SysTick->CTRL = (1<<0) | (1<<1) | (1<<2);
	NVIC_EnableIRQ(SysTick_IRQn);			/* Enable systick interrupt */

	/* Configure analog comparator */
	LPC_CMP->CTL = (1<<6)|(3<<8)|(1<<25);	/* Use synchronization logic, positive voltage input = ACMP_I3,
	 	 	 	 	 	 	 	 	 	 	   negative voltage input = voltage ladder output,
	 	 	 	 	 	 	 	 	 	 	   enable 5mV hysteresis */
	LPC_CMP->LAD = (1<<0);					/* Enable voltage ladder, ref = VDD */

	/* Configure CT32B0 for frequency measurement */
	LPC_CT32B0->CTCR = (3<<0)|(3<<2);		/* Counter mode, triggered by
	 	 	 	 	 	 	 	 	 	   	   rising and falling edge of analog comparator */
	LPC_CT32B0->TCR = (1<<1);				/* Reset counter and prescaler */
	LPC_CT32B0->TCR = (1<<0);				/* Enable counter and prescaler */

	/* Configure CT32B1 for duty-cycle measurement */
	LPC_CT32B1->CTCR = (1<<4)|(6<<5);		/* Timer mode, reset timer on rising edge of the comparator */
	LPC_CT32B1->CCR = (1<<10);				/* Load CR3 on falling edge of comparator */
	LPC_CT32B1->TCR = (1<<1);				/* Reset counter and prescaler */
	LPC_CT32B1->TCR = (1<<0);				/* Enable the timer module */

	/* Print banner */
	printf("\r\n*******************************************\r\n");
	printf("*                                         *\r\n");
	printf("*     NXP LPC11A14 frequency counter      *\r\n");
	printf("*   using the on-chip analog comparator   *\r\n");
	printf("*                                         *\r\n");
	printf("*******************************************\r\n\r\n");

	/* main loop */
	while(1)
	{
		switch(State)
		{
		case NormalOperation:				/* Normal operation = measure frequency, handled by timers / ISR */
			break;
		case DisplayFreq:
			/* Print frequency / duty-cycle on LCD and UART */
			State = NormalOperation;
			Frequency = CounterValue - PrevCounterValue;	/* Result is measured frequency * 2 */
			if(Frequency == 0)
				DC = 0;										/* No frequency means duty-cycle of 0 */
			else
				DC = (100*DC*(Frequency/2)+SystemCoreClock/2)/SystemCoreClock;	/* else calculate frequency */

			/* Print Frequency or duty cycle to string */
			if(ToggleDisplay++ & 0x02)
				sprintf(String, "%7d%%", DC);
			else if(Frequency < 100000)
				sprintf(String, "%5d Hz", Frequency/2);
			else if(Frequency < 1000000)
				sprintf(String, "%6dHz", Frequency/2);
			else
				sprintf(String, "%8d", Frequency/2);

			/* Display string on LCD and print all info to UART */
			HD44780_StrShow(1,1,(HD44780_STRING_DEF *) String);
			printf("F = %8d.%1d Hz          Duty-Cycle = %2d%%\r\n", Frequency/2, (Frequency%2)*5, DC);
			break;
		case Calibrating:
			/* Calibration started, first print calibration banner */
			HD44780_StrShow(1,1,(const HD44780_STRING_DEF *)"Calibr. ");
			printf("\r\n*******************************************\r\n");
			printf("*                                         *\r\n");
			printf("*              Calibrating...             *\r\n");
			printf("*                                         *\r\n");
			/* initialize detected minimum / maximum values */
			LowestVal = 31;
			HighestVal = 0;
			while(State == Calibrating)
			{
				/* Do while state is Calibrating. State will be changed by ISR */
				for(LAD=0; LAD<32; LAD++)
				{
					/* Cycle through all 32 voltage ladder positions for one second */
					LPC_CMP->LAD = (1<<0)|(LAD<<1);
					/* short delay to get a stable output from the comparator */
					for(i=0;i<64;i++)
						__NOP();

					/* Peak detector for highest voltage ladder position */
					if((LPC_CMP->CTL & (1<<21)) && (LAD > HighestVal))
						HighestVal = LAD;
					/* Peak detector for lowest voltage ladder position */
					else if(!(LPC_CMP->CTL & (1<<21)) && (LAD < LowestVal))
						LowestVal = LAD;
				}
			}
			break;
		case ProcessCalibrate:
			/* Calibration done, now process and print the result */
			LAD = (LowestVal + HighestVal)/2;	/* Calculate mid-level of input signal */
			printf("* Vl = %4d mV (LAD @%2d)                  *\r\n", (LowestVal*3300)/31, LowestVal);
			printf("* Vh = %4d mV (LAD @%2d)                  *\r\n", (HighestVal*3300)/31, HighestVal);
			printf("* Vref configured at %4d mV (LAD @%2d)    *\r\n", (LAD*3300)/31, LAD);
			printf("*                                         *\r\n");
			printf("*******************************************\r\n\r\n");
			LPC_CMP->LAD = (1<<0)|(LAD<<1);		/* Set voltage ladder to calculated mid-level of input signal */
			State = NormalOperation;			/* Continue normal operation */
			break;
		}
	}
}

/******************************************************************************
**   ISR Function  SysTick_Handler(), executed every 1/128th second
******************************************************************************/
void SysTick_Handler (void)
{
	uint32_t UserButton;						/* Reflects state of user button. 0 = pressed, 1 = released */
	uint32_t regval;							/* Temp variable to store counter value for frequency measurement */
	static uint8_t PrevUserButton = 0;			/* Static variable to remember the previous state of the user button */

	/* Copy counter values ASAP */
	regval = LPC_CT32B0->TC;
	DC = LPC_CT32B1->CR3;

	if(!(ms78Counter++ %128))					/* Execute next block of code every second */
	{
		PrevCounterValue = CounterValue;		/* Save previous Counter value (for frequency measurement) */
		CounterValue = regval;					/* Save current Counter value (for frequency measurement) */
		if(State == NormalOperation)
			State = DisplayFreq;				/* If present state == NormalOperation, change to DisplayFreq */

		if(State == Calibrating)
			State = ProcessCalibrate;			/* If present state == Calibrating, than change to ProcessCalibrating (calibration has finished) */
	}

	/* Check if button has been pressed */
	UserButton = LPC_GPIO_PORT->PIN[0] >> 31;	/* Save button state */
	if(UserButton && !PrevUserButton)			/* If button is released and previous value was pressed */
	{
		/* Change state to Calibrating */
		State = Calibrating;
		/* Reset ms78Counter to make sure calibration takes 1 second */
		ms78Counter = 1;
	}
	/* Save current user button state for next iteration */
	PrevUserButton = UserButton;
}

/******************************************************************************
**                            End Of File
******************************************************************************/
