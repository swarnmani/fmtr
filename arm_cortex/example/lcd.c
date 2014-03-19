#ifndef lcd_C
#define lcd_C

#include "lpc11xx_gpio.h"
#include "lpc11xx_syscon.h"
#include "lpc11xx_libcfg.h"
#include "lcd.h"



void lcd_config(void)
{
	GPIO_SetDir(LCD_PORT, LCD_BIT_RS, PORT_DIR_OUTPUT);
	GPIO_SetDir(LCD_PORT, LCD_BIT_RW, PORT_DIR_INPUT);
	GPIO_SetDir(LCD_PORT, LCD_BIT_E,  PORT_DIR_OUTPUT);

	GPIO_SetDir(LCD_PORT, LCD_BIT_D4, PORT_DIR_OUTPUT);
	GPIO_SetDir(LCD_PORT, LCD_BIT_D5, PORT_DIR_OUTPUT);
	GPIO_SetDir(LCD_PORT, LCD_BIT_D6, PORT_DIR_OUTPUT);
	GPIO_SetDir(LCD_PORT, LCD_BIT_D7, PORT_DIR_OUTPUT);

	LCD_RWOFF(); //PORTD&=~(1<<RW); //RW off

	return;
}

void lcd_init(void)
{
	/* Enable GPIO block clock */
		//SYSCON_AHBPeriphClockCmd(SYSCON_AHBPeriph_GPIO, ENABLE);
	GPIO_SetBits(PORT0, GPIO_Pin_7);
	lcd_config();
	_delay_ms(5);				// wait after power up

	lcd_nibble(0x03,0);			// send 03h 3 times to initialize
	_delay_ms(1);
	lcd_nibble(0x03,0);
	_delay_ms(1);
	lcd_nibble(0x03,0);
	_delay_ms(1);
	lcd_cmd(0x20);
	_delay_ms(1);
	lcd_cmd(0x28);
	_delay_ms(1);
	lcd_en_tgl();
	_delay_ms(1);

	lcd_en_tgl();
	_delay_ms(1);

	lcd_en_tgl();
	_delay_ms(10);

	lcd_nibble(0x02,0);			// enable 4 bit mode
	_delay_ms(1);

	lcd_cmd(0x10);					//cursor move & shift left
	_delay_ms(1);

	lcd_cmd(0x06);					//entry mode = increment
	_delay_ms(1);

	lcd_cmd(0x0C);					//display on - cursor blink on
	_delay_ms(1);

	lcd_cmd(0x01);					//clear display ram
	_delay_ms(10);
	GPIO_ResetBits(PORT0, GPIO_Pin_7);
	return;
}

void lcd_en_tgl (void)
{
	LCD_ENABLE(); //PORTD|=(1<<EN);
	LCD_DISABLE(); //PORTD&=~(1<<EN);					//Enable pin
	return;
}

void lcd_cmd(unsigned char letter)
{
// Command Function
//The RS is set to 0 to signify this is a command
	unsigned char temp;             // temp Variable
	temp=letter;                    //move letter to temp
	temp=temp>>4;                   //shift temp to right by 4
	lcd_nibble(temp,0);             //send out higher nibble

	temp=letter;                    //move letter to temp
	temp=temp&0x0F;
	lcd_nibble(temp,0);             //send out lower nibble
	_delay_ms(1);
	return;
}

void lcd_char(unsigned char letter)
{
//TData  Function
//The RS is set to 1 to signify this is a command
	unsigned char temp;             // temp Variable
	temp=letter;                    //move letter to temp
	temp=temp>>4;                   //shift temp to right by 4
	lcd_nibble(temp,1);             //send out higher nibble

	temp=letter;                    //move letter to temp
	temp=temp&0x0F;
	lcd_nibble(temp,1);             //send out lower nibble
	_delay_ms(1);
	return;
}

void lcd_nibble(unsigned char nib,unsigned char reg_sel)
{
//unsigned char i,x;
	GPIO_SetBits(PORT0, GPIO_Pin_7);
	if(reg_sel)
		LCD_RSON(); //PORTD|=(1<<RS);               // Set RS Pin (defined in header file)
	else
		LCD_RSOFF(); //PORTD&=~(1<<RS);
	nib=(nib<<4);
	lcd_data(nib); //PORTC=nib;
	_delay_ms(1);
	lcd_en_tgl();
	GPIO_ResetBits(PORT0, GPIO_Pin_7);// Toggle E pin (defined in header file)
	return;
}

void lcd_clr_line(unsigned char line)
{
	unsigned char x=0;
// clear line cxC0;                         // 2 = Line 2
	lcd_cmd(line);                         // Send command to jump to beggining of line (1/2)
	_delay_ms(1);

    for(x=0x00;x<0x14;x++)
{                   					    // Loop through all 20 chars of line (even tho 16 are viewable)
        lcd_char(0x20);                     // Send Blank Character
        _delay_ms(1);
    }

    lcd_cmd(line);                         // Go back to beggining of line
    _delay_ms(1);
return;
}

void lcd_string(char *senpoint, unsigned char line)
{
    if(line==1)
        lcd_cmd(line1);
    if(line==2)
        lcd_cmd(line2);
    while(*senpoint != '\0')            // While we havent seen a \0 (esc) go on
	{
		lcd_char(*senpoint);            // Send 1st char to our char function
		senpoint++;                     // Send next
	}

return;
}

void lcd_string_position (char *senpoint, unsigned char line, unsigned char position, unsigned char l_r)	//position starts from 0
{
	lcd_cmd (line);
  while (position != 0)			//first position or home position is 0 and last position is 15
  {
    if(l_r)
      lcd_cmd(CURSOR_SHIFT_LEFT);	//move to left
    else
      lcd_cmd(CURSOR_SHIFT_RIGHT);	//move to right
    position--;
  }
  while (*senpoint != '\0' )
  {
    lcd_char(*senpoint);		// send the character to be displayed
    senpoint++;
  }
}

/*************************************************************************
Set cursor to specified position
Input:    x  horizontal position  (0: left most position)
          y  vertical position    (0: first line)
Returns:  none
*************************************************************************/
void lcd_gotoxy(uint8_t x,uint8_t y)
{
 if(x<40)
 {
  if(y) x|=0b01000000;
  x|=0b10000000;
  lcd_cmd(x);
  }
}
/* lcd_gotoxy */

void lcdwritestring(const char *msg)
{
	/*****************************************************************

	This function Writes a given string to lcd at the current cursor
	location.

	Arguments:
	msg: a null terminated string to print


	*****************************************************************/
 while(*msg!='\0')
 {
	lcd_char(*msg);
	msg++;
 }
}

void lcdwriteint(int val,unsigned int field_length)
{
	/***************************************************************
	This function writes a integer type value to LCD module

	Arguments:
	1)int val	: Value to print

	2)unsigned int field_length :total length of field in which the value is printed
	must be between 1-5 if it is -1 the field length is no of digits in the val

	****************************************************************/

	char str[5]={0,0,0,0,0};
	int i=4,j=0;
	while(val)
	{
	str[i]=val%10;
	val=val/10;
	i--;
	}
	if(field_length==-1)
		while(str[j]==0) j++;
	else
		j=5-field_length;

	if(val<0) lcd_char('-');
	for(i=j;i<5;i++)
	{
	lcd_char(48+str[i]);
	}
}

void lcd_data(unsigned char data)
{
	 LPC_GPIO2->MASKED_ACCESS[0x03c0] = ((data&0xf0) << 2);
}

void _delay_ms(double ms)
{
	INT_32 i;
	double j;

	for(j = 0; j < ms; j++) {
		for(i = 0; i < 30000; i++);
	}
}

void _delay_us (double us)
{
	UNS_8 i;
	double j;
	for (j = 0; j < us; j++) {
		for(i = 0; i < 300; i++);
	}
}

#endif
