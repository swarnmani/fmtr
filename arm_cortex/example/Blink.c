#include "lpc11xx_syscon.h"
#include "lpc11xx_gpio.h"

void BlinkExp()
{
	int i, j;

	/* Enable GPIO block clock */
	SYSCON_AHBPeriphClockCmd(SYSCON_AHBPeriph_GPIO, ENABLE);

	/* If PIO2_9 had been set to other function, set it to PIO function. 
	 * NOTE: Component IOCON should be checked */
	//IOCON_SetPinFunc(IOCON_PIO2_9, PIO2_9_FUN_PIO);

	/* Set PIO2_9 as output. */
	GPIO_SetDir(PORT2, GPIO_Pin_9, 1);

	while(1) {

		/* Delay some time */
		for(i=0; i<20; i++) {
			for(j=0; j<10000; j++) {
			}
		}

		/* Output high level */
		GPIO_SetBits(PORT2, GPIO_Pin_9);

		/* Delay some time */
		for(i=0; i<20; i++) {
			for(j=0; j<10000; j++) {
			}
		}

		/* Output low level */
		GPIO_ResetBits(PORT2, GPIO_Pin_9);
	}
}