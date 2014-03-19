/*
 * lcd.h
 *
 *  Created on: Jan 22, 2011
 *      Author: James
 */

#ifndef LCD_H_
#define LCD_H_

void lcd_init(void);
void lcd_gotoxy(uint8_t x, uint8_t y);
void lcd_send_character(uint8_t theChar);
void lcd_print(char *p);

#endif /* LCD_H_ */
