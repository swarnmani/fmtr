// Initialization and interrupt vectors for the LPC1114 microcontroller
// No claims are made as to the suitability of this code for any 
// purpose whatsoever.  Use at your own risk!
// Does not include initialization for C++ global/static objects
// so probably best to use this with C projects for now.
// Latest version of this code can be found by visiting
// http://eleceng.dit.ie/frank and follow the links
// Author: Frank Duignan

#include "lpc111x.h"
void init(void);
void clock_init();
void Default_Handler(void);
void UART_isr(void);
// The following are 'declared' in the linker script
extern unsigned char  INIT_DATA_VALUES;
extern unsigned char  INIT_DATA_START;
extern unsigned char  INIT_DATA_END;
extern unsigned char  BSS_START;
extern unsigned char  BSS_END;

// the section "vectors" is placed at the beginning of flash 
// by the linker script
const void * Vectors[] __attribute__((section(".vectors"))) ={
	(void *)0x10002000, /* Top of stack */ 
	init,   			/* Reset Handler */
	Default_Handler,	/* NMI */
	Default_Handler,	/* Hard Fault */
	0,	                /* Reserved */
	0,                  /* Reserved */
	0,                  /* Reserved */
	0,                  /* Reserved */
	0,                  /* Reserved */
	0,                  /* Reserved */
	0,                  /* Reserved */
	Default_Handler,	/* SVC */
	0,                 	/* Reserved */
	0,                 	/* Reserved */
	Default_Handler,   	/* PendSV */
	Default_Handler, 	/* SysTick */		
/* External interrupt handlers follow */
	Default_Handler, 	/* PIO0_0 */
	Default_Handler, 	/* PIO0_1 */
	Default_Handler, 	/* PIO0_2 */
	Default_Handler, 	/* PIO0_3 */
	Default_Handler, 	/* PIO0_4 */
	Default_Handler, 	/* PIO0_5 */
	Default_Handler, 	/* PIO0_6 */
	Default_Handler, 	/* PIO0_7 */
	Default_Handler, 	/* PIO0_8 */
	Default_Handler, 	/* PIO0_9 */
	Default_Handler, 	/* PIO0_10 */
	Default_Handler, 	/* PIO0_11 */
	Default_Handler,	/* PIO1_0 */
	Default_Handler ,  	/* C_CAN */
	Default_Handler, 	/* SSP1 */
	Default_Handler, 	/* I2C */
	Default_Handler, 	/* CT16B0 */
	Default_Handler, 	/* CT16B1 */
	Default_Handler, 	/* CT32B0 */
	Default_Handler, 	/* CT32B1 */
	Default_Handler, 	/* SSP0 */
	UART_isr,			/* UART */
	Default_Handler, 	/* RESERVED */
	Default_Handler, 	/* RESERVED */
	Default_Handler, 	/* ADC */
	Default_Handler, 	/* WDT */
	Default_Handler, 	/* BOD */
	Default_Handler, 	/* RESERVED */
	Default_Handler, 	/* PIO3 */
	Default_Handler, 	/* PIO2 */
	Default_Handler, 	/* PIO1 */
	Default_Handler 	/* PIO0 */
};
void clock_init()
{
	// This function sets the main clock to the PLL
	// The PLL input is the built in 12MHz RC oscillator
	// This is multiplied up to 48MHz for the main clock
	// MSEL = 3, PSEL = 1 see page 51 of UM10398 user manual
	SYSPLLCLKSEL = 0; // select internal RC oscillator
	SYSPLLCTRL = (3 << 0) | (1 << 5); // set divisors/multipliers
	PDRUNCFG &= ~BIT7; // Power up the PLL.
	SYSPLLCLKUEN = 1; // inform PLL of update
	
	MAINCLKSEL = 3; // Use PLL as main clock
	MAINCLKUEN = 1; // Inform core of clock update
}
void init()
{
// do global/static data initialization
	unsigned char *src;
	unsigned char *dest;
	unsigned len;
	src= &INIT_DATA_VALUES;
	dest= &INIT_DATA_START;
	len= &INIT_DATA_END-&INIT_DATA_START;
	while (len--)
		*dest++ = *src++;
// zero out the uninitialized global/static variables
	dest = &BSS_START;
	len = &BSS_END - &BSS_START;
	while (len--)
		*dest++=0;
	clock_init();
	main();
}

void Default_Handler()
{
	while(1);
}
