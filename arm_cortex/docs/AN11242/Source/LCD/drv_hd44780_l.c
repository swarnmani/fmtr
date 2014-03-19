/*************************************************************************
 *
 *    Used with ICCARM and AARM.
 *
 *    (c) Copyright IAR Systems 2011
 *
 *    File name   : drv_hd44780_l.c
 *    Description : I/O function
 *
 *    History :
 *    1. Date        : February 5, 2009
 *       Author      : Stanimir Bonev
 *       Description : Create
 *    2. Date        : April 18, 2011
 *       Author      : Stanimir Bonev
 *       Description : Port for IAR-LPC11A14-SK
 *
 *    $Revision: 47021 $
**************************************************************************/
#include "drv_hd44780_l.h"

/*************************************************************************
 * Function Name: HD44780_IO_Init
 * Parameters: none
 * Return: none
 * Description: Init IO ports directions and level
 *
 *************************************************************************/
void HD44780_IO_Init (void)
{

  LCD_RS_DIR |= LCD_RS;
  LCD_E_DIR  |= LCD_E;
  LDC_DATA_DIR |= LCD_DATA_MASK << LCD_DATA_SHIFT;
#if HD4780_WR > 0
  LCD_RW_DIR |= LCD_RW;
  LCD_RW_LOW();
#endif // HD4780_WR > 0

  HD44780SetPD();
}

/*************************************************************************
 * Function Name: HD44780SetPD
 * Parameters: none
 * Return: none
 * Description: Set power down
 *
 *************************************************************************/
void HD44780SetPD (void)
{
  // RS Output - Low
  LCD_RS_LOW();
  // E  Output - Low
  LCD_E_LOW();
  // Data lines High
  LCD_DATA_PORT_SET = LCD_DATA_MASK << LCD_DATA_SHIFT;
#if HD4780_WR > 0
  // WR Output - Low
  LCD_RW_LOW();
#endif // HD4780_WR > 0
}

/*************************************************************************
 * Function Name: HD44780SetPU
 * Parameters: none
 * Return: none
 * Description: Set power up
 *
 *************************************************************************/
void HD44780SetPU (void)
{
  HD44780_BusDly();
  // RS Output - Low
  LCD_RS_LOW();
  // E  Output - Low
  LCD_E_LOW();
#if HD4780_WR > 0
  // WR Output - Low
  LCD_RW_HIGH();
#endif // HD4780_WR > 0
}

/*************************************************************************
 * Function Name: HD44780WrIO
 * Parameters: Int32U Data
 * Return: none
 * Description: Write to HD44780 I/O
 *
 *************************************************************************/
void HD44780WrIO (uint32_t Data)
{
  // Write Data
#if HD4780_WR > 0
  LCD_RW_LOW();
  LDC_DATA_DIR |= LCD_DATA_MASK<<LCD_DATA_SHIFT;
#endif
  LCD_E_HIGH();
  LCD_DATA_PORT_CLR = LCD_DATA_MASK << LCD_DATA_SHIFT;
  LCD_DATA_PORT_SET = (Data & LCD_DATA_MASK) << LCD_DATA_SHIFT;
  HD44780_BusDly();
  LCD_E_LOW();
}

#if HD4780_WR > 0
/*************************************************************************
 * Function Name: HD44780RdIO
 * Parameters: none
 * Return: Int8U
 * Description: Read from HD44780 I/O
 *
 *************************************************************************/
uint8_t HD44780RdIO (void)
{
uint8_t Data;
  // Set Direction
  LDC_DATA_DIR &= ~(LCD_DATA_MASK << LCD_DATA_SHIFT);
  LCD_RW_HIGH();
  // Read Data
  LCD_E_HIGH();
  HD44780_BusDly();
  Data = (LCD_DATA_PORT_IN >> LCD_DATA_SHIFT) & LCD_DATA_MASK;
  LCD_E_LOW();
  return Data;
}
#endif

void HD44780_BusDly(void)
{
	volatile uint32_t dly;
	for(dly = 10;dly;--dly)
		;
}
