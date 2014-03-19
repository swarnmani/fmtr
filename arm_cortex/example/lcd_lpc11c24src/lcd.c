/*
 * lcd.c
 *
 *  Created on: Jan 22, 2011
 *      Author: James
 */

//#include "LPC13xx.h"                                   // LPC13xx definitions
#include "driver_config.h"
#include "target_config.h"

#include "small_gpio.h"
#include "type.h"
#include "lcd.h"
#include "timer32.h"

#define LCD_PORT  2
#define LCD_PIN0  0	// d4->Pio0_0, d5->Pio0_1, d6->Pio0_2, d7->Pio0_3
#define LCD_PINRS 7
#define LCD_PINE  8

#define LCD_FUNCTION_SET      0x30 // 0b00110000
#define LCD_FUNCTION_SET_4BIT 0x28 // 0b00101000
#define LCD_DISPLAY_OFF       0x08 // 0b00001000
//#define LCD_DISPLAY_ON        0x0F // 0b00001111
#define LCD_DISPLAY_ON        0x0c // no cursor, no blink
#define LCD_DISPLAY_CLEAR     0x01 // 0b00000001
#define LCD_ENTRY_MODE_SET    0x06 // 0b00000110
#define LCD_CURSOR_HOME       0x02 // 0b00000010

#define LCD_DDRAM			7

#define LCD_START_LINE1 0x0
#define LCD_START_LINE2 0x040
#define LCD_START_LINE3 0x014
#define LCD_START_LINE4 0x054

static LPC_GPIO_TypeDef(* const LPC_GPIO[4]) = { LPC_GPIO0, LPC_GPIO1,
		LPC_GPIO2, LPC_GPIO3 };

extern volatile uint32_t msTicks;

void lcd_delay(int msec) {
	//volatile uint32_t done = msTicks + msec;
	//while (msTicks != done);
	delay32Ms(0,msec);

}
/* LcdSendNibble
 *
 * Sends a 4-bit nibble to the display.
 *
 * Parameters:
 *	uint8_t nibble	The high nibble of of this byte
 *					is sent to the display.
 * Returns:
 *	nothing
 */
void LcdSendNibble(uint32_t nibble) {
	lcd_delay(3);
	// Output upper nibble on the data ports upper bits
	LPC_GPIO[LCD_PORT]->MASKED_ACCESS[(0x0f << LCD_PIN0)] = ((nibble & 0x0f) << LCD_PIN0);

	// Toggle the E line
	LPC_GPIO[LCD_PORT]->MASKED_ACCESS[(1 << LCD_PINE)] = (1 << LCD_PINE); // up
	//lcd_delay(1);
	LPC_GPIO[LCD_PORT]->MASKED_ACCESS[(1 << LCD_PINE)] = 0; // down
}
/* LcdSendByte
 *
 * Sends a 8-bit byte to the display.
 *
 * Parameters:
 *	uint8_t theByte	The byte to send to the display
 *
 * Returns:
 *	nothing
 */
void LcdSendByte(uint8_t theByte) {
	// Send the high nibble
	LcdSendNibble(theByte >> 4);

	// send low nibble
	LcdSendNibble(theByte);
}

/* LcdSendInstruction
 *
 * Sends an instruction to the display.
 *
 * Parameters:
 *	uint8_t command	This byte is sent to the display as
 *					an instruction (RS low).
 * Returns:
 *	nothing
 */
void LcdSendInstruction(uint8_t theInstruction) {
	// RS low for instructions
	LPC_GPIO[LCD_PORT]->MASKED_ACCESS[(1 << LCD_PINRS)] = 0; // RS LOW

	// Send the instruction
	LcdSendByte(theInstruction);
}

void lcd_gotoxy(uint8_t x, uint8_t y) {
    if ( y==0 )
    	LcdSendInstruction((1<<LCD_DDRAM)+LCD_START_LINE1+x);
    else if ( y==1)
    	LcdSendInstruction((1<<LCD_DDRAM)+LCD_START_LINE2+x);
    else if ( y==2)
    	LcdSendInstruction((1<<LCD_DDRAM)+LCD_START_LINE3+x);
    else /* y==3 */
    	LcdSendInstruction((1<<LCD_DDRAM)+LCD_START_LINE4+x);

}

/* LcdSendCharacter
 *
 * Sends a character to the display.
 *
 * Parameters:
 *	uint8_t nibble	This byte is sent to the display as
 *					a character (RS high).
 * Returns:
 *	nothing
 */
void lcd_send_character(uint8_t theChar) {
	// RS high for characters to display
	LPC_GPIO[LCD_PORT]->MASKED_ACCESS[(1 << LCD_PINRS)] = (1 << LCD_PINRS); // RS HIGH

	// Send the command
	LcdSendByte(theChar);
}

void lcd_print(char *p) {
	while(*p != 0) {
		lcd_send_character(*p++);
	}

}

void lcd_init(void) {
	LPC_GPIO[LCD_PORT]->DIR |= (0x00f << LCD_PIN0); // set pins to output for lcd data d4-d7
	LPC_GPIO[LCD_PORT]->DIR |= (0x001 << LCD_PINRS); // set pins to output for lcd rs
	LPC_GPIO[LCD_PORT]->DIR |= (0x001 << LCD_PINE); // set pins to output for lcd e

	LPC_GPIO[LCD_PORT]->MASKED_ACCESS[(1 << LCD_PINRS)] = 0; // RS LOW
	LPC_GPIO[LCD_PORT]->MASKED_ACCESS[(1 << LCD_PINE)] = 0; // E LOW
	// First part of init sequence is 3 x Function Set with
	// stipulated waits. Note that the display is in 8-bit mode
	// initially, but although the four low data lines are not connected
	// this does not matter as the instructions low nibble is zero anyway.
	lcd_delay(16);
	LcdSendNibble(0x03);
	lcd_delay(5);
	LcdSendNibble(0x03);
	lcd_delay(100);
	LcdSendNibble(0x03);

	// Now, still in 8-bit mode, set the display to 4-bit mode
	LcdSendNibble(0x02);

	// We are now in 4-bit mode.
	// Do the rest of the init sequence.
	LcdSendInstruction(LCD_FUNCTION_SET_4BIT);
	LcdSendInstruction(LCD_DISPLAY_OFF);
	LcdSendInstruction(LCD_DISPLAY_CLEAR);
	LcdSendInstruction(LCD_ENTRY_MODE_SET);
	LcdSendInstruction(LCD_DISPLAY_ON);
}

