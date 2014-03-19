
#include "LPC13xx.h"    
#include "type.h"
#include "lcd.h"

#define     EN_IOCON        (1<<16)

volatile uint32_t msTicks; /* counts 1ms timeTicks */
/*----------------------------------------------------------------------------
 SysTick_Handler
 *----------------------------------------------------------------------------*/
void SysTick_Handler(void) {
	msTicks++; /* increment counter necessary in Delay() */
}

/*----------------------------------------------------------------------------
 Main Program
 *---------------------------------------------------------------------------*/
int main(void) {

	/* Enable IOCON */
	LPC_SYSCON->SYSAHBCLKCTRL |= EN_IOCON;

	// Setup SysTick Timer for 1 msec interrupts
	if (SysTick_Config(SystemCoreClock / 1000)) {
		while (1)
			; // Capture error
	}

	if (!(SysTick->CTRL & SysTick_CTRL_CLKSOURCE_Msk)) {
		/* When external reference clock is used(CLKSOURCE in
		 Systick Control and register bit 2 is set to 0), the
		 SYSTICKCLKDIV must be a non-zero value and 2.5 times
		 faster than the reference clock.
		 When core clock, or system AHB clock, is used(CLKSOURCE
		 in Systick Control and register bit 2 is set to 1), the
		 SYSTICKCLKDIV has no effect to the SYSTICK frequency. See
		 more on Systick clock and status register in Cortex-M3
		 technical Reference Manual. */
		LPC_SYSCON->SYSTICKCLKDIV = 0x08;
	}
	lcd_init();

	lcd_gotoxy(0, 0);
	lcd_print("Hello world!");

	for (;;) {
		// main loop
	}

}
