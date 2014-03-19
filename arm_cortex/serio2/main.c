/* This program uses UART to send data back to the host using
 * simple print statements.  UART transmission is not interrupt
 * driven.  
 * 
 * Operation:
 * 
 * Wiring.
 * A USB to serial converter is wired to the TX and RX pins of UART0
 */
#include "lpc111x.h"
void UART_isr(void);
void initUART()
{
	SYSAHBCLKCTRL |= BIT6 + BIT16; // Turn on clock for GPIO and IOCON
	// Enable UART RX function on PIO1_6
	IOCON_PIO1_6 |= BIT0; 
	IOCON_PIO1_6 &= ~(BIT1+BIT2);
	// Enable UART TX function on PIO1_7
	IOCON_PIO1_7 |= BIT0;
	IOCON_PIO1_7 &= ~(BIT1+BIT2);
	// Turn on clock for UART
	SYSAHBCLKCTRL |= BIT12;
	UARTCLKDIV = 1;
	// PCLK = 48Mhz. Desired Baud rate = 9600
	// See table 199
	// 9600=48MHz/(16* (256*U0DLM + U0DLL)*(1+DivAddVal/MulVal))
	// 312.5 = (256*U0DLM+U0DLL)*(1+DivAddVal/MulVal)
	// let U0DLM=1, DivAddVal=0,MulVal =1
	// 312.5=256+U0DLL
	// U0DLL=56.5.  
	// Choose U0DLL=56.
	// Actual baud rate achieved = 9615 - close enough.
	U0LCR |= BIT7; // Enable divisor latch access
	U0FDR = (1<<4)+0; // Set DivAddVal = 0; MulVal = 1
	U0DLL = 56;
	U0DLM = 1;
	U0LCR &= ~BIT7; // Disable divisor latch access
	U0LCR |= (BIT1+BIT0); // set word length to 8 bits.
	U0IER = BIT0+BIT2;	// Enable UART RX Data available interrupts
	ISER |= BIT21; 		// enable UART IRQ's in NVIC was 13
}
void UART_isr(void)
{
	if (U0IIR & BIT2) // Is the interrupt caused by 'Read-Data-Available'?
		U0THR = U0RBR;
}
int main() 
{	
	initUART();
	enable_interrupts();
	while(1) 
	{		
		
	}    
}



