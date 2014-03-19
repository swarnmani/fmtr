/****************************************************************************
 *   $Id:: blinky_main.c 4785 2010-09-03 22:39:27Z nxp21346                        $
 *   Project: LED flashing / ISP test program
 *
 *   Description:
 *     This file contains the main routine for the blinky code sample
 *     which flashes an LED on the LPCXpresso board and also increments an
 *     LED display on the Embedded Artists base board. This project
 *     implements CRP and is useful for testing bootloaders.
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
 ****************************************************************************/

#include "driver_config.h"
#include "target_config.h"
#include "type.h"

#include "timer32.h"
#include "gpio.h"
#include "lcd.h"



int main(void) {
	uint8_t charToPrint = 0;
	uint32_t halfPeriodMS = 200;

	init_timer32(0, 1);

	GPIOSetDir(LED_PORT, LED_BIT, 1);
	lcd_init();
	lcd_print("Hello LPC11c24!");
	lcd_gotoxy(0,1);

	while (1) /* Loop forever */
	{

		GPIOSetValue(LED_PORT, LED_BIT, LED_OFF);
		lcd_send_character(charToPrint++);
		delay32Ms(0,halfPeriodMS);

		GPIOSetValue(LED_PORT, LED_BIT, LED_ON);
		lcd_send_character(charToPrint++);
		delay32Ms(0,halfPeriodMS);
		if(charToPrint%16 == 0)
			lcd_gotoxy(0,1);
	}
}
