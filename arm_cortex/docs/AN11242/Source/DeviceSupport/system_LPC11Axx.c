/**************************************************************************//**
 * @file     system_LPC11Axx.c
 * @brief    CMSIS Cortex-M0 Device Peripheral Access Layer Source File
 *           for the NXP LPC11Axx Devices
 * @version  V1.00
 * @date     21. December 2010
 *
 * @note
 * Copyright (C) 2009 ARM Limited. All rights reserved.
 *
 * @par
 * ARM Limited (ARM) is supplying this software for use with Cortex-M 
 * processor based microcontrollers.  This file can be freely distributed 
 * within development tools that are supporting such ARM based processors. 
 *
 * @par
 * THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 * ARM SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR
 * CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 ******************************************************************************/
#include <stdint.h>
#include "LPC11Axx.h"
#include "power_api.h"

/*
//-------- <<< Use Configuration Wizard in Context Menu >>> ------------------
*/

/*--------------------- Clock Configuration ----------------------------------
//<e0>SystemCoreClock Configuration
//
//	<o13>Crystal Oscillator (XTO) Frequency [Hz] <1000000-25000000>
//		<i>XTO frequency must be in the range of  1 MHz to  25 MHz
//	
//	<o12>CLKIN Frequency [Hz]                    <1000000-25000000>
//		<i>CLKIN frequency must be in the range of  1 MHz to  25 MHz
//	
//	<o6.0..1>Main Clock Source Select (MAINCLKSEL)
//		<0=> IRC Oscillator
//		<1=> PLL Input
//		<2=> LF Oscillator
//		<3=> PLL Output	
//	<o3.0..1>System PLL Clock Source Select (SYSPLLCLKSEL)
//		<0=> IRC Oscillator
//		<1=> Crystal Oscillator (XTO)
//		<2=> CLKIN Pin	
//
//	<e2>Manual SystemCoreClock Configuration			
//		<e10>LF Oscillator Setting (LFOSCCTRL)
//			<o4.0..4>DIVSEL: Select Divider for Fclkana
//				<i> lf_osc_clk = Fclkana / (2 � (1 + DIVSEL))
//				<0-31>
//			<o4.5..8>FREQSEL: Select LF Oscillator Analog Output Frequency (Fclkana)
//				<1=> 0.5 MHz
//				<2=> 0.8 MHz
//				<3=> 1.1 MHz
//				<4=> 1.4 MHz
//				<5=> 1.6 MHz
//				<6=> 1.8 MHz
//				<7=> 2.0 MHz
//				<8=> 2.2 MHz
//				<9=> 2.4 MHz
//				<10=> 2.6 MHz
//				<11=> 2.7 MHz
//				<12=> 2.9 MHz
//				<13=> 3.1 MHz
//				<14=> 3.2 MHz
//				<15=> 3.4 MHz
//		</e>
//	
//		<e11> System PLL Setting (SYSPLLCTRL)
//			<i> F_clkout = M * F_clkin = F_CCO / (2 * P)
//			<i> F_clkin must be in the range of  10 MHz to  25 MHz
//			<i> F_CCO   must be in the range of 156 MHz to 320 MHz
//			<o5.0..4>MSEL: Feedback Divider Selection
//				<i> M = MSEL + 1
//				<0-31>
//			<o5.5..6>PSEL: Post Divider Selection
//				<0=> P = 1
//				<1=> P = 2
//				<2=> P = 4
//				<3=> P = 8
//		</e>	
//		<o7.0..7>System AHB Clock Divider (SYSAHBCLKDIV.DIV)
//		<i> Divides main clock to provide system clock to core, memories, and peripherals.
//		<i> 0 = is disabled
//		<0-255>
//	</e>
//
//	<e1> SystemCoreClock Configuration via PLL API
//		<o8> PLL API Mode Select
//			<0=> Exact
//			<1=> Less than or equal
//			<2=> Greater than or equal
//			<3=> As close as possible
//		<o9>CPU Frequency [Hz]  <1000000-50000000:1000>
//	</e>
//
//</e>
*/
#define CLOCK_SETUP           1
#define CLOCK_SETUP_API       0
#define CLOCK_SETUP_REG       1

#define SYSPLLCLKSEL_Val      0x00000001
#define LFOSCCTRL_Val         0x0000003F
#define SYSPLLCTRL_Val        0x00000021
#define MAINCLKSEL_Val        0x00000003
#define SYSAHBCLKDIV_Val      0x00000001

#define PLL_API_MODE_Val      0
#define PLL_API_FREQ_Val      48000000

#define USE_LFOSC       	  0
#define USE_PLL       	  	  1
#define CLKIN_CLK_Val		  12000000
#define XTO_CLK_Val			  25000000

/*
//-------- <<< end of configuration section >>> ------------------------------
*/

/*----------------------------------------------------------------------------
  Check the register settings
 *----------------------------------------------------------------------------*/
#define CHECK_RANGE(val, min, max)                ((val < min) || (val > max))
#define CHECK_RSVD(val, mask)                     (val & mask)

/*----------------------------------------------------------------------------
  Define clocks
 *----------------------------------------------------------------------------*/
#define __XTO_CLK     (XTO_CLK_Val)          /* Oscillator frequency          */
#define __IRC_OSC_CLK (  12000000UL)         /* Internal RC oscillator freq   */
#define __CLKIN_CLK   (CLKIN_CLK_Val)        /* CLKIN pin frequency           */

/* Clock Configuration -------------------------------------------------------*/
#if (CHECK_RSVD((LFOSCCTRLL_Val),  ~0x000001FF))
   #error "LFOSCCTRL: Invalid values of reserved bits!"
#endif

#if (CHECK_RANGE((SYSPLLCLKSEL_Val), 0, 2))
   #error "SYSPLLCLKSEL: Value out of range!"
#endif

#if (CHECK_RANGE(__XTO_CLK, 1000000, 25000000))
	#error "XTO frequency is out of bounds"
#endif

#if (CHECK_RANGE(__CLKIN_CLK, 1000000, 25000000))
	#error "CLKIN frequency is out of bounds"
#endif

#if (CHECK_RSVD((SYSPLLCTRL_Val),  ~0x000001FF))
   #error "SYSPLLCTRL: Invalid values of reserved bits!"
#endif

#if (CHECK_RSVD((MAINCLKSEL_Val),  ~0x00000003))
   #error "MAINCLKSEL: Invalid values of reserved bits!"
#endif

#if (CHECK_RANGE((SYSAHBCLKDIV_Val), 0, 255))
   #error "SYSAHBCLKDIV: Value out of range!"
#endif

#if (CLOCK_SETUP_REG == CLOCK_SETUP_API)
   #error "You must select either manual or API based SystemCoreClock Configuration!"
#endif

#if ( (1==CLOCK_SETUP_REG) && (0==USE_PLL) && ((MAINCLKSEL_Val&0x3)==0x3) )
	#error "You must enable PLL!"	
#endif 

#if ((1==CLOCK_SETUP_REG) && (0==USE_LFOSC) && ((MAINCLKSEL_Val&0x3)==0x2) )
	#error "You must enable LFOSC!"	
#endif 

#if (CLOCK_SETUP)                            /* Clock Setup                   */
#if (CLOCK_SETUP_REG == 1)                   /* Clock Setup via Register      */
	#define __FREQSEL   ((LFOSCCTRL_Val >> 5) & 0x0F)
	#define __DIVSEL   (((LFOSCCTRL_Val & 0x1F) << 1) + 2)

	#if  (__FREQSEL ==  0)
		#define __LF_OSC_CLK         ( 0)        /* undefined                     */
	#elif (__FREQSEL ==  1)
		#define __LF_OSC_CLK         ( 500000 / __DIVSEL)
	#elif (__FREQSEL ==  2)
		#define __LF_OSC_CLK         ( 800000 / __DIVSEL)
	#elif (__FREQSEL ==  3)
		#define __LF_OSC_CLK         (1100000 / __DIVSEL)
	#elif (__FREQSEL ==  4)
		#define __LF_OSC_CLK         (1400000 / __DIVSEL)
	#elif (__FREQSEL ==  5)
		#define __LF_OSC_CLK         (1600000 / __DIVSEL)
	#elif (__FREQSEL ==  6)
		#define __LF_OSC_CLK         (1800000 / __DIVSEL)
	#elif (__FREQSEL ==  7)
		#define __LF_OSC_CLK         (2000000 / __DIVSEL)
	#elif (__FREQSEL ==  8)
		#define __LF_OSC_CLK         (2200000 / __DIVSEL)
	#elif (__FREQSEL ==  9)
		#define __LF_OSC_CLK         (2400000 / __DIVSEL)
	#elif (__FREQSEL == 10)
		#define __LF_OSC_CLK         (2600000 / __DIVSEL)
	#elif (__FREQSEL == 11)
		#define __LF_OSC_CLK         (2700000 / __DIVSEL)
	#elif (__FREQSEL == 12)
		#define __LF_OSC_CLK         (2900000 / __DIVSEL)
	#elif (__FREQSEL == 13)
		#define __LF_OSC_CLK         (3100000 / __DIVSEL)
	#elif (__FREQSEL == 14)
		#define __LF_OSC_CLK         (3200000 / __DIVSEL)
	#else
		#define __LF_OSC_CLK         (3400000 / __DIVSEL)
	#endif

	/* sys_pllclkin calculation */
	#if   ((SYSPLLCLKSEL_Val & 0x03) == 0)
		#define __SYS_PLLCLKIN           (__IRC_OSC_CLK)
	#elif ((SYSPLLCLKSEL_Val & 0x03) == 1)
		#define __SYS_PLLCLKIN           (__XTO_CLK)
	#elif ((SYSPLLCLKSEL_Val & 0x03) == 2)
		#if (((MAINCLKSEL_Val & 0x03) == 3) && (__CLKIN_CLK <  10000000))
			#error "SYSPLLCLKSEL: CLKIN selected but Frequency is too low!"
		#endif
		#define __SYS_PLLCLKIN           (__CLKIN_CLK)
	#else
		#define __SYS_PLLCLKIN           (0)
	#endif

  #define  __SYS_PLLCLKOUT         (__SYS_PLLCLKIN * ((SYSPLLCTRL_Val & 0x01F) + 1))

  /* main clock calculation */
  #if   ((MAINCLKSEL_Val & 0x03) == 0)
    #define __MAIN_CLOCK             (__IRC_OSC_CLK)
  #elif ((MAINCLKSEL_Val & 0x03) == 1)
    #define __MAIN_CLOCK             (__SYS_PLLCLKIN)
  #elif ((MAINCLKSEL_Val & 0x03) == 2)
    #if (__FREQSEL ==  0)
      #error "MAINCLKSEL: LF Oscillator selected but FREQSEL is undefined!"
    #else
      #define __MAIN_CLOCK           (__LF_OSC_CLK)
    #endif
  #elif ((MAINCLKSEL_Val & 0x03) == 3)
    #define __MAIN_CLOCK             (__SYS_PLLCLKOUT)
  #else
    #define __MAIN_CLOCK             (0)
  #endif

  #define __SYSTEM_CLOCK             (__MAIN_CLOCK / SYSAHBCLKDIV_Val)         

#endif /* Clock Setup via Register */

#if (CLOCK_SETUP_API == 1)                   /* Clock Setup via PLL API       */
	/* sys_pllclkin calculation */
	#if   ((SYSPLLCLKSEL_Val & 0x03) == 0)
		#define __SYS_PLLCLKIN           (__IRC_OSC_CLK)
	#elif ((SYSPLLCLKSEL_Val & 0x03) == 1)
		#if (                                  (__XTO_CLK <  10000000))
			#error "SYSPLLCLKSEL: XTO selected but Frequency is too low!"
		#endif	
		#define __SYS_PLLCLKIN           (__XTO_CLK)
	#elif ((SYSPLLCLKSEL_Val & 0x03) == 2)
		#if (                                  (__CLKIN_CLK <  10000000))
			#error "SYSPLLCLKSEL: CLKIN selected but Frequency is too low!"
		#endif
		#define __SYS_PLLCLKIN           (__CLKIN_CLK)
	#else
		#define __SYS_PLLCLKIN           (0)
	#endif
	#define __SYSTEM_CLOCK             (PLL_API_FREQ_Val)         
#endif /* Clock Setup via PLL API */

#else
  #define __SYSTEM_CLOCK             (__IRC_OSC_CLK)
#endif  /* CLOCK_SETUP */

#if ((CLOCK_SETUP==1) && (CLOCK_SETUP_API == 1))	/* Clock Setup via PLL API       */
/*----------------------------------------------------------------------------
  PLL API Function
 *----------------------------------------------------------------------------*/
static void setPLL(const uint32_t pllMode, const uint32_t pllInFreq, const uint32_t reqCpuFreq)
{
	uint32_t cmd[5], res[5];
	ROM ** rom = (ROM **) 0x1FFF1FF8;          	/* pointer for power API calls   	*/
	
	cmd[0] = pllInFreq;                        	/* PLL's input   freq in KHz     	*/
	cmd[1] = reqCpuFreq;                       	/* requested CPU freq in KHz     	*/
	cmd[2] = pllMode;                  	
	cmd[3] = 0;                                	/* no timeout for PLL to lock    	*/
	
	/* Execute API call */
	(*rom)->pPWRD->set_pll(cmd ,res);          	/* set PLL and AHB clock divider	*/
	if ((res[0] != PLL_CMD_SUCCESS)){          	/* in case of an error ...       	*/
		while(1);                         		/* ... stay here               		*/
	}
}
#endif

/*----------------------------------------------------------------------------
  Clock Variable definitions
 *----------------------------------------------------------------------------*/
uint32_t SystemCoreClock = __SYSTEM_CLOCK;/*!< System Clock Frequency (Core Clock)*/


/*----------------------------------------------------------------------------
  Clock functions
 *----------------------------------------------------------------------------*/
void SystemCoreClockUpdate (void)            /* Get Core Clock Frequency      */
{
  uint32_t lf_osc = 0;

  /* Determine clock frequency according to clock register values             */
  switch ((LPC_SYSCON->LFOSCCTRL >> 5) & 0x0F) {
    case 0:  lf_osc =       0; break;
    case 1:  lf_osc =  500000; break;
    case 2:  lf_osc =  800000; break;
    case 3:  lf_osc = 1100000; break;
    case 4:  lf_osc = 1400000; break;
    case 5:  lf_osc = 1600000; break;
    case 6:  lf_osc = 1800000; break;
    case 7:  lf_osc = 2000000; break;
    case 8:  lf_osc = 2200000; break;
    case 9:  lf_osc = 2400000; break;
    case 10: lf_osc = 2600000; break;
    case 11: lf_osc = 2700000; break;
    case 12: lf_osc = 2900000; break;
    case 13: lf_osc = 3100000; break;
    case 14: lf_osc = 3200000; break;
    case 15: lf_osc = 3400000; break;
  }
  lf_osc /= ((LPC_SYSCON->LFOSCCTRL & 0x1F) << 1) + 2;
 
  switch (LPC_SYSCON->MAINCLKSEL & 0x03) {
    case 0:                                  /* Internal RC oscillator        */
      SystemCoreClock = __IRC_OSC_CLK;
      break;
    case 1:                                  /* Input Clock to System PLL     */
      switch (LPC_SYSCON->SYSPLLCLKSEL & 0x03) {
          case 0:                            /* Internal RC oscillator        */
            SystemCoreClock = __IRC_OSC_CLK;
            break;
          case 1:                            /* System oscillator             */
            SystemCoreClock = __XTO_CLK;
            break;
          case 2:                            /* CLKIN pin                     */
            SystemCoreClock = __CLKIN_CLK;
            break;
          case 3:                            /* Reserved                      */
            SystemCoreClock = 0;
            break;
      }
      break;
    case 2:                                  /* LF Oscillator                 */
      SystemCoreClock = lf_osc;
      break;
    case 3:                                  /* System PLL Clock Out          */
      switch (LPC_SYSCON->SYSPLLCLKSEL & 0x03) {
          case 0:                            /* Internal RC oscillator        */
            if (LPC_SYSCON->SYSPLLCTRL & 0x180) {
              SystemCoreClock = __IRC_OSC_CLK;
            } else {
              SystemCoreClock = __IRC_OSC_CLK  * ((LPC_SYSCON->SYSPLLCTRL & 0x01F) + 1);
            }
            break;
          case 1:                            /* System oscillator             */
            if (LPC_SYSCON->SYSPLLCTRL & 0x180) {
              SystemCoreClock = __XTO_CLK;
            } else {
              SystemCoreClock = __XTO_CLK  * ((LPC_SYSCON->SYSPLLCTRL & 0x01F) + 1);
            }
            break;
          case 2:                            /* CLKIN pin                     */
            if (LPC_SYSCON->SYSPLLCTRL & 0x180) {
              SystemCoreClock = __CLKIN_CLK;
            } else {
              SystemCoreClock = __CLKIN_CLK * ((LPC_SYSCON->SYSPLLCTRL & 0x01F) + 1);
            }
            break;
          case 3:                            /* Reserved                      */
            SystemCoreClock = 0;
            break;
      }
      break;
  }

  SystemCoreClock /= LPC_SYSCON->SYSAHBCLKDIV;  

}

/**
 * Initialize the system
 *
 * @param  none
 * @return none
 *
 * @brief  Setup the microcontroller system.
 */
void SystemInit (void)
{
#if (CLOCK_SETUP)
	volatile uint32_t i;
#endif

#if (CLOCK_SETUP)                            		/* Clock Setup                 	*/
#if ((SYSPLLCLKSEL_Val & 0x03) == 1)          		/* Power up sysosc        	  	*/
  	LPC_SYSCON->PDRUNCFG     &= ~(1 << 5);    		/* Power-up sysosc              */
  	for (i = 0; i < 200; i++) __NOP();		  		/* Wait for osc to stabilize	*/
#endif
#if ((SYSPLLCLKSEL_Val & 0x03) == 2)          		/* Setup IO for CLKIN        	*/
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<16);
	LPC_IOCON->PIO0_24 &= ~0x07;	
	LPC_IOCON->PIO0_24 |= 0x02;		/* CLK IN */
  	for (i = 0; i < 200; i++) __NOP();		  		/* Wait for osc to stabilize	*/
#endif
	LPC_SYSCON->SYSPLLCLKSEL  = SYSPLLCLKSEL_Val; 	/* Select PLL Input           	*/
	LPC_SYSCON->SYSPLLCLKUEN  = 0x01;           	/* Update Clock Source          */
	LPC_SYSCON->SYSPLLCLKUEN  = 0x00;           	/* Toggle Update Register       */
	LPC_SYSCON->SYSPLLCLKUEN  = 0x01;
	while (!(LPC_SYSCON->SYSPLLCLKUEN & 0x01)); 	/* Wait Until Updated           */

#if (CLOCK_SETUP_REG == 1)                    		/* Clock Setup via Register     */

#if (((MAINCLKSEL_Val & 0x03) == 2) )
  	LPC_SYSCON->LFOSCCTRL     = LFOSCCTRL_Val;
  	LPC_SYSCON->PDRUNCFG     &= ~(1 << 13);    		/* Power-up lfosc               */
  	for (i = 0; i < 200; i++) __NOP();		  		/* Wait for osc to stabilize	*/
#endif

#if ((MAINCLKSEL_Val & 0x03) == 3)            		/* Main Clock is PLL Out        */
	LPC_SYSCON->SYSPLLCTRL    = SYSPLLCTRL_Val;
	LPC_SYSCON->PDRUNCFG     &= ~(1 << 7);      	/* Power-up SYSPLL              */
	while (!(LPC_SYSCON->SYSPLLSTAT & 0x01));	 	/* Wait Until PLL Locked        */
#endif

	LPC_SYSCON->MAINCLKSEL    = MAINCLKSEL_Val; 	/* Select Clock Source      	*/
	LPC_SYSCON->MAINCLKUEN    = 0x01;           	/* Update MCLK Clock Source     */
	LPC_SYSCON->MAINCLKUEN    = 0x00;           	/* Toggle Update Register       */
	LPC_SYSCON->MAINCLKUEN    = 0x01;
	while (!(LPC_SYSCON->MAINCLKUEN & 0x01));   	/* Wait Until Updated           */
	
	LPC_SYSCON->SYSAHBCLKDIV  = SYSAHBCLKDIV_Val;
#endif                                       		/* Clock Setup via Register      */

#if (CLOCK_SETUP_API == 1)                   		/* Clock Setup via PLL API       */	

	LPC_SYSCON->SYSPLLCLKSEL  = 0x00; 				/* Use IRC */
	LPC_SYSCON->SYSPLLCLKUEN  = 0x01;           	/* Update Clock Source          */
	LPC_SYSCON->SYSPLLCLKUEN  = 0x00;           	/* Toggle Update Register       */
	LPC_SYSCON->SYSPLLCLKUEN  = 0x01;
	while (!(LPC_SYSCON->SYSPLLCLKUEN & 0x01)); 	/* Wait Until Updated           */

	LPC_SYSCON->MAINCLKSEL    = 0x01; 				/* Select PLL Input      		*/
	LPC_SYSCON->MAINCLKUEN    = 0x01;           	/* Update MCLK Clock Source     */
	LPC_SYSCON->MAINCLKUEN    = 0x00;           	/* Toggle Update Register       */
	LPC_SYSCON->MAINCLKUEN    = 0x01;
	while (!(LPC_SYSCON->MAINCLKUEN & 0x01));   	/* Wait Until Updated           */

	LPC_SYSCON->SYSAHBCLKDIV  = 1;

													/* Use API to configure device	*/				
	setPLL(PLL_API_MODE_Val, __SYS_PLLCLKIN / 1000, PLL_API_FREQ_Val / 1000);
#endif                                       		/* Clock Setup via PLL API       */

#endif                                       		/* Clock Setup                   */

	/* System clock to the IOCON needs to be enabled or
	most of the I/O related peripherals won't work. */
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<16);
}
