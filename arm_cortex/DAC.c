#include "DAC.h"

void DAC_SPI1_Config (void)
{
	LPC_SYSCON->PRESETCTRL |= (1<<2);
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<18);  // clk for spi1
	LPC_SYSCON->SSP1CLKDIV = 0x02;               /* Divided by 2 */
	/*  SSP I/O config */
//	LPC_IOCON->PIO2_3           &= ~0x07;
//	LPC_IOCON->PIO2_3           |=  0x02;                /* SSP1 MOSI */
//	LPC_IOCON->PIO2_2           &= ~0x07;
//	LPC_IOCON->PIO2_2           |=  0x02;                /* SSP1 MISO */
//	LPC_IOCON->PIO2_1           &= ~0x07;
//	LPC_IOCON->PIO2_1           |=  0x02;                /* SSP1 CLK */
//	LPC_IOCON->PIO2_0           &= ~0x07;
//	LPC_IOCON->PIO2_0           |=  0x02;                /* SSP1 SSEL */
	SSP_SSP1PinsInit (ENABLE); // Select the pins
	/* SSPCPSR clock prescale register, master mode, minimum divisor is 0x02 */
	LPC_SSP1->CPSR = 0x2;
	/* Set DSS data to 16-bit, Frame format SPI, CPOL = 0, CPHA = 0, and SCR is 15 */
    LPC_SSP1->CR0 = 0x070F;
    LPC_SSP1->CR1 |= 2;  /* Enable SSP */
    return;
}

void DAC_SPI1_Write (uint16_t data)
{
	data = data | 0x3000;
	SSP_SendData(LPC_SSP1, (uint16_t)data); // 1V
}
