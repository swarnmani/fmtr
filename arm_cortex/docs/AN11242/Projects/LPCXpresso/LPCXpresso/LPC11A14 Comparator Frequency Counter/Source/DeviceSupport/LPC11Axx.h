
/****************************************************************************************************//**
 * @file     LPC11Axx.h
 *
 * @status   EXPERIMENTAL
 *
 * @brief    CMSIS Cortex-M0 Core Peripheral Access Layer Header File for
 *           default LPC11Axx Device Series
 *
 * @version  V0.1
 * @date     20. December 2011
 *
 * @note     Generated with SVDConv V2.6 Build 6c  on Tuesday, 20.12.2011 07:37:42
 *
 *           from CMSIS SVD File 'LPC11Axxv0.1.xml' Version 0.1,
 *           created on Tuesday, 20.12.2011 15:36:19, last modified on Tuesday, 20.12.2011 15:36:20
 *
 *******************************************************************************************************/



/** @addtogroup (null)
  * @{
  */

/** @addtogroup LPC11Axx
  * @{
  */

#ifndef __LPC11AXX_H__
#define __LPC11AXX_H__

#ifdef __cplusplus
extern "C" {
#endif 



/********************************************
** Start of section using anonymous unions **
*********************************************/

#if defined(__ARMCC_VERSION)
  #pragma push
  #pragma anon_unions
#elif defined(__CWCC__)
  #pragma push
  #pragma cpp_extensions on
#elif defined(__GNUC__)
  /* anonymous unions are enabled by default */
#elif defined(__IAR_SYSTEMS_ICC__)
  #pragma push
  #pragma language=extended
#else
  #error Not supported compiler type
#endif


 /* Interrupt Number Definition */

typedef enum {
// -------------------------  Cortex-M0 Processor Exceptions Numbers  -----------------------------
  Reset_IRQn                        = -15,  /*!<   1  Reset Vector, invoked on Power up and warm reset */
  NonMaskableInt_IRQn               = -14,  /*!<   2  Non maskable Interrupt, cannot be stopped or preempted */
  HardFault_IRQn                    = -13,  /*!<   3  Hard Fault, all classes of Fault */
  SVCall_IRQn                       =  -5,  /*!<  11  System Service Call via SVC instruction */
  DebugMonitor_IRQn                 =  -4,  /*!<  12  Debug Monitor                    */
  PendSV_IRQn                       =  -2,  /*!<  14  Pendable request for system service */
  SysTick_IRQn                      =  -1,  /*!<  15  System Tick Timer                */
// ---------------------------  LPC11Axx Specific Interrupt Numbers  ------------------------------
  PIN_INT0_IRQn                     =   0,  /*!<   0  PIN_INT0                         */
  PIN_INT1_IRQn                     =   1,  /*!<   1  PIN_INT1                         */
  PIN_INT2_IRQn                     =   2,  /*!<   2  PIN_INT2                         */
  PIN_INT3_IRQn                     =   3,  /*!<   3  PIN_INT3                         */
  PIN_INT4_IRQn                     =   4,  /*!<   4  PIN_INT4                         */
  PIN_INT5_IRQn                     =   5,  /*!<   5  PIN_INT5                         */
  PIN_INT6_IRQn                     =   6,  /*!<   6  PIN_INT6                         */
  PIN_INT7_IRQn                     =   7,  /*!<   7  PIN_INT7                         */
  GINT0_IRQn                        =   8,  /*!<   8  GINT0                            */
  GINT1_IRQn                        =   9,  /*!<   9  GINT1                            */
  CMP_IRQn                          =  10,  /*!<  10  CMP                              */
  DAC_IRQn                          =  11,  /*!<  11  DAC                              */
  RESERVED0_IRQn                    =  12,  /*!<  12  RESERVED0                        */
  RESERVED1_IRQn                    =  13,  /*!<  13  RESERVED1                        */
  SSP1_IRQn                         =  14,  /*!<  14  SSP1                             */
  I2C_IRQn                          =  15,  /*!<  15  I2C                              */
  TIMER_16_0_IRQn               = 16,       /*!< 16-bit Timer0 Interrupt                          */
  TIMER_16_1_IRQn               = 17,       /*!< 16-bit Timer1 Interrupt                          */
  TIMER_32_0_IRQn               = 18,       /*!< 32-bit Timer0 Interrupt                          */
  TIMER_32_1_IRQn               = 19,       /*!< 32-bit Timer1 Interrupt                          */
  SSP0_IRQn                         =  20,  /*!<  20  SSP0                             */
  USART_IRQn                        =  21,  /*!<  21  USART                            */
  RESERVED2_IRQn                    =  22,  /*!<  22  RESERVED2                        */
  RESERVED3_IRQn                    =  23,  /*!<  23  RESERVED3                        */
  ADC_IRQn                          =  24,  /*!<  24  ADC                              */
  WDT_IRQn                          =  25,  /*!<  25  WDT                              */
  BOD_IRQn                          =  26,  /*!<  26  BOD                              */
  FMC_IRQn                          =  27,  /*!<  27  FMC_IRQ                          */
  RESERVED4_IRQn                    =  28,  /*!<  28  RESERVED4                        */
  RESERVED5_IRQn                    =  29,  /*!<  29  RESERVED5                        */
  RESERVED6_IRQn                    =  30,  /*!<  30  RESERVED6                        */
  RESERVED7_IRQn                    =  31   /*!<  31  RESERVED7                        */
} IRQn_Type;


/** @addtogroup Configuration_of_CMSIS
  * @{
  */

/* Processor and Core Peripheral Section */ /* Configuration of the Cortex-M0 Processor and Core Peripherals */

#define __CM0_REV              0x0000       /*!< Cortex-M0 Core Revision               */
#define __MPU_PRESENT             0         /*!< MPU present or not                    */
#define __NVIC_PRIO_BITS          0         /*!< Number of Bits used for Priority Levels */
#define __Vendor_SysTickConfig    0         /*!< Set to 1 if different SysTick Config is used */
/** @} */ /* End of group Configuration_of_CMSIS */

#include <core_cm0.h>                       /*!< Cortex-M0 processor and core peripherals */
#include "system_LPC11Axx.h"                /*!< LPC11Axx System                       */

/** @addtogroup Device_Peripheral_Registers
  * @{
  */


// ------------------------------------------------------------------------------------------------
// -----                                          I2C                                         -----
// ------------------------------------------------------------------------------------------------


/**
  * @brief Product name title=UM10462 Chapter title=LPC11U1x I2C-bus controller Modification date=3/16/2011 Major revision=0 Minor revision=3  (I2C)
  */



typedef struct { 
  __IO  uint32_t  CONSET; /*!< (@ 0x000) I2C Control Set Register. When a one is written to a bit of this register, the corresponding bit in the I2C control register is set. Writing a zero has no effect on the corresponding bit in the I2C control register.*/
  __I   uint32_t  STAT; /*!< (@ 0x004) I2C Status Register. During I2C operation, this register provides detailed status codes that allow software to determine the next action needed.*/
  __IO  uint32_t  DAT; /*!< (@ 0x008) I2C Data Register. During master or slave transmit mode, data to be transmitted is written to this register. During master or slave receive mode, data that has been received may be read from this register.*/
  __IO  uint32_t  ADR0; /*!< (@ 0x00C) I2C Slave Address Register 0. Contains the 7-bit slave address for operation of the I2C interface in slave mode, and is not used in master mode. The least significant bit determines whether a slave responds to the General Call address.*/
  __IO  uint32_t  SCLH; /*!< (@ 0x010) SCH Duty Cycle Register High Half Word. Determines the high time of the I2C clock.*/
  __IO  uint32_t  SCLL; /*!< (@ 0x014) SCL Duty Cycle Register Low Half Word. Determines the low time of the I2C clock. I2nSCLL and I2nSCLH together determine the clock frequency generated by an I2C master and certain times used in slave mode.*/
  __O   uint32_t  CONCLR; /*!< (@ 0x018) I2C Control Clear Register. When a one is written to a bit of this register, the corresponding bit in the I2C control register is cleared. Writing a zero has no effect on the corresponding bit in the I2C control register.*/
  __IO  uint32_t  MMCTRL; /*!< (@ 0x01C) Monitor mode control register.*/
    union{ 
      __IO   uint32_t  ADR[3]; /*!< (@ 0x020) I2C Slave Address Register. Contains the 7-bit slave address for operation of the I2C interface in slave mode, and is not used in master mode. The least significant bit determines whether a slave responds to the General Call address.*/
       struct{
           __IO  uint32_t ADR1;  
           __IO  uint32_t ADR2;  
           __IO  uint32_t ADR3;  
        };
    };
  __I   uint32_t  DATA_BUFFER; /*!< (@ 0x02C) Data buffer register. The contents of the 8 MSBs of the I2DAT shift register will be transferred to the DATA_BUFFER automatically after every nine bits (8 bits of data plus ACK or NACK) has been received on the bus.*/
    union{ 
      __IO   uint32_t  MASK[4]; /*!< (@ 0x030) I2C Slave address mask register. This mask register is associated with I2ADR0 to determine an address match. The mask register has no effect when comparing to the General Call address (0000000).*/
            struct{
          __IO  uint32_t MASK0;  
          __IO  uint32_t MASK1;  
          __IO  uint32_t MASK2;  
          __IO  uint32_t MASK3;  
         };
    };
 } LPC_I2C_Type; 


// ------------------------------------------------------------------------------------------------
// -----                                         WWDT                                         -----
// ------------------------------------------------------------------------------------------------


/**
  * @brief Product name title=UM10462 Chapter title=LPC11U1x Windowed Watchdog Timer (WWDT) Modification date=3/16/2011 Major revision=0 Minor revision=3  (WWDT)
  */

typedef struct {                            /*!< (@ 0x40004000) WWDT Structure         */
  __IO uint32_t  MOD;                       /*!< (@ 0x40004000) Watchdog mode register. This register contains the basic mode and status of the Watchdog Timer. */
  __IO uint32_t  TC;                        /*!< (@ 0x40004004) Watchdog timer constant register. This 24-bit register determines the time-out value. */
  __O  uint32_t  FEED;                      /*!< (@ 0x40004008) Watchdog feed sequence register. Writing 0xAA followed by 0x55 to this register reloads the Watchdog timer with the value contained in WDTC. */
  __I  uint32_t  TV;                        /*!< (@ 0x4000400C) Watchdog timer value register. This 24-bit register reads out the current value of the Watchdog timer. */
  __IO uint32_t  CLKSEL;                    /*!< (@ 0x40004010) Watchdog clock select register. */
  __IO uint32_t  WARNINT;                   /*!< (@ 0x40004014) Watchdog Warning Interrupt compare value. */
  __IO uint32_t  WINDOW;                    /*!< (@ 0x40004018) Watchdog Window compare value. */
} LPC_WWDT_Type;


// ------------------------------------------------------------------------------------------------
// -----                                         USART                                        -----
// ------------------------------------------------------------------------------------------------


/**
  * @brief Product name title=UM10462 Chapter title=LPC11U1x USART Modification date=3/22/2011 Major revision=0 Minor revision=4  (USART)
  */

typedef struct {                            /*!< (@ 0x40008000) USART Structure        */
  
  union {
    __IO uint32_t  DLL;                     /*!< (@ 0x40008000) Divisor Latch LSB. Least significant byte of the baud rate divisor value. The full divisor is used to generate a baud rate from the fractional rate divider. (DLAB=1) */
    __O  uint32_t  THR;                     /*!< (@ 0x40008000) Transmit Holding Register. The next character to be transmitted is written here. (DLAB=0) */
    __I  uint32_t  RBR;                     /*!< (@ 0x40008000) Receiver Buffer Register. Contains the next received character to be read. (DLAB=0) */
  } ;
  
  union {
    __IO uint32_t  IER;                     /*!< (@ 0x40008004) Interrupt Enable Register. Contains individual interrupt enable bits for the 7 potential USART interrupts. (DLAB=0) */
    __IO uint32_t  DLM;                     /*!< (@ 0x40008004) Divisor Latch MSB. Most significant byte of the baud rate divisor value. The full divisor is used to generate a baud rate from the fractional rate divider. (DLAB=1) */
  } ;
  
  union {
    __O  uint32_t  FCR;                     /*!< (@ 0x40008008) FIFO Control Register. Controls USART FIFO usage and modes. */
    __I  uint32_t  IIR;                     /*!< (@ 0x40008008) Interrupt ID Register. Identifies which interrupt(s) are pending. */
  } ;
  __IO uint32_t  LCR;                       /*!< (@ 0x4000800C) Line Control Register. Contains controls for frame formatting and break generation. */
  __IO uint32_t  MCR;                       /*!< (@ 0x40008010) Modem Control Register. */
  __I  uint32_t  LSR;                       /*!< (@ 0x40008014) Line Status Register. Contains flags for transmit and receive status, including line errors. */
  __I  uint32_t  MSR;                       /*!< (@ 0x40008018) Modem Status Register. */
  __IO uint32_t  SCR;                       /*!< (@ 0x4000801C) Scratch Pad Register. Eight-bit temporary storage for software. */
  __IO uint32_t  ACR;                       /*!< (@ 0x40008020) Auto-baud Control Register. Contains controls for the auto-baud feature. */
  __IO uint32_t  ICR;                       /*!< (@ 0x40008024) IrDA Control Register. Enables and configures the IrDA (remote control) mode. */
  __IO uint32_t  FDR;                       /*!< (@ 0x40008028) Fractional Divider Register. Generates a clock input for the baud rate divider. */
  __IO uint32_t  OSR;                       /*!< (@ 0x4000802C) Oversampling Register. Controls the degree of oversampling during each bit time. */
  __IO uint32_t  TER;                       /*!< (@ 0x40008030) Transmit Enable Register. Turns off USART transmitter for use with software flow control. */
  __I  uint32_t  RESERVED0[3];
  __IO uint32_t  HDEN;                      /*!< (@ 0x40008040) Half duplex enable register. */
  __I  uint32_t  RESERVED1;
  __IO uint32_t  SCICTRL;                   /*!< (@ 0x40008048) Smart Card Interface Control register. Enables and configures the Smart Card Interface feature. */
  __IO uint32_t  RS485CTRL;                 /*!< (@ 0x4000804C) RS-485/EIA-485 Control. Contains controls to configure various aspects of RS-485/EIA-485 modes. */
  __IO uint32_t  RS485ADRMATCH;             /*!< (@ 0x40008050) RS-485/EIA-485 address match. Contains the address match value for RS-485/EIA-485 mode. */
  __IO uint32_t  RS485DLY;                  /*!< (@ 0x40008054) RS-485/EIA-485 direction control delay. */
  __IO uint32_t  SYNCCTRL;                  /*!< (@ 0x40008058) Synchronous mode control register. */
} LPC_USART_Type;


// ------------------------------------------------------------------------------------------------
// -----                                        CT16B0                                        -----
// ------------------------------------------------------------------------------------------------


/**
  * @brief Product name title=UM10462 Chapter title=LPC11U1x 16-bit counter/timers CT16B0/1 Modification date=3/16/2011 Major revision=0 Minor revision=3  (CT16B0)
  */

typedef struct {                            /*!< (@ 0x4000C000) CT16B0 Structure       */
  __IO   uint32_t  IR; /*!< (@ 0x000) Interrupt Register. The IR can be written to clear interrupts. The IR can be read to identify which of eight possible interrupt sources are pending.*/
  __IO   uint32_t  TCR; /*!< (@ 0x004) Timer Control Register. The TCR is used to control the Timer Counter functions. The Timer Counter can be disabled or reset through the TCR.*/
  __IO   uint32_t  TC; /*!< (@ 0x008) Timer Counter. The 16-bit TC is incremented every PR+1 cycles of PCLK. The TC is controlled through the TCR.*/
  __IO   uint32_t  PR; /*!< (@ 0x00C) Prescale Register. When the Prescale Counter (below) is equal to this value, the next clock increments the TC and clears the PC.*/
  __IO   uint32_t  PC; /*!< (@ 0x010) Prescale Counter. The 16-bit PC is a counter which is incremented to the value stored in PR. When the value in PR is reached, the TC is incremented and the PC is cleared. The PC is observable and controllable through the bus interface.*/
  __IO   uint32_t  MCR; /*!< (@ 0x014) Match Control Register. The MCR is used to control if an interrupt is generated and if the TC is reset when a Match occurs.*/
    union{ 
      __IO   uint32_t  MR[4]; /*!< (@ 0x018) Match Register. MR can be enabled through the MCR to reset the TC, stop both the TC and PC, and/or generate an interrupt every time MR matches the TC.*/
           struct{
         __IO  uint32_t MR0 ;  
         __IO  uint32_t MR1 ;  
         __IO  uint32_t MR2 ;  
         __IO  uint32_t MR3 ;  
        };
    };
  __IO   uint32_t  CCR; /*!< (@ 0x028) Capture Control Register. The CCR controls which edges of the capture inputs are used to load the Capture Registers and whether or not an interrupt is generated when a capture takes place.*/
    union{ 
      __I   uint32_t  CR[4]; /*!< (@ 0x02C) Capture Register. CR is loaded with the value of TC when there is an event on the CT16B0_CAP input.*/
           struct{
          __I uint32_t CR0 ;  
          __I uint32_t CR1 ;  
          __I uint32_t CR2 ;  
          __I uint32_t CR3 ;  
        };
    };
  __IO   uint32_t  EMR; /*!< (@ 0x03C) External Match Register. The EMR controls the match function and the external match pins */
  __I    uint32_t  Reserved0[12]; 
  __IO   uint32_t  CTCR; /*!< (@ 0x070) Count Control Register. The CTCR selects between Timer and Counter mode, and in Counter mode selects the signal and edge(s) for counting.*/
  __IO   uint32_t  PWMC; /*!< (@ 0x074) PWM Control Register. The PWMCON enables PWM mode for the external match pins CT16B0_MAT[1:0] and CT16B1_MAT[1:0].*/
 } LPC_CT16B0_Type; 

// ------------------------------------------------------------------------------------------------
// -----                                        CT32B0                                        -----
// ------------------------------------------------------------------------------------------------


/**
  * @brief Product name title=UM10462 Chapter title=LPC11U1x 32-bitcounter/timers CT32B0/1 Modification date=3/16/2011 Major revision=0 Minor revision=3  (CT32B0)
  */



typedef struct { 
  __IO   uint32_t  IR; /*!< (@ 0x000) Interrupt Register. The IR can be written to clear interrupts. The IR can be read to identify which of eight possible interrupt sources are pending.*/
  __IO   uint32_t  TCR; /*!< (@ 0x004) Timer Control Register. The TCR is used to control the Timer Counter functions. The Timer Counter can be disabled or reset through the TCR.*/
  __IO   uint32_t  TC; /*!< (@ 0x008) Timer Counter. The 32-bit TC is incremented every PR+1 cycles of PCLK. The TC is controlled through the TCR.*/
  __IO   uint32_t  PR; /*!< (@ 0x00C) Prescale Register. When the Prescale Counter (below) is equal to this value, the next clock increments the TC and clears the PC.*/
  __IO   uint32_t  PC; /*!< (@ 0x010) Prescale Counter. The 32-bit PC is a counter which is incremented to the value stored in PR. When the value in PR is reached, the TC is incremented and the PC is cleared. The PC is observable and controllable through the bus interface.*/
  __IO   uint32_t  MCR; /*!< (@ 0x014) Match Control Register. The MCR is used to control if an interrupt is generated and if the TC is reset when a Match occurs.*/
    union{ 
      __IO   uint32_t  MR[4]; /*!< (@ 0x018) Match Register. MR can be enabled through the MCR to reset the TC, stop both the TC and PC, and/or generate an interrupt every time MR matches the TC.*/
           struct{
         __IO  uint32_t MR0 ;  
         __IO  uint32_t MR1 ;  
         __IO  uint32_t MR2 ;  
         __IO  uint32_t MR3 ;  
        };
    };
  __IO   uint32_t  CCR; /*!< (@ 0x028) Capture Control Register. The CCR controls which edges of the capture inputs are used to load the Capture Registers and whether or not an interrupt is generated when a capture takes place.*/
    union{ 
      __I   uint32_t  CR[4]; /*!< (@ 0x02C) Capture Register. CR is loaded with the value of TC when there is an event on the CT32B_CAP0 input.*/
           struct{
          __I uint32_t CR0 ;  
          __I uint32_t CR1 ;  
          __I uint32_t CR2 ;  
          __I uint32_t CR3 ;  
        };
    };
  __IO   uint32_t  EMR; /*!< (@ 0x03C) External Match Register. The EMR controls the match function and the external match pins CT32Bn_MAT[3:0].*/
  __I    uint32_t  Reserved0[12]; 
  __IO   uint32_t  CTCR; /*!< (@ 0x070) Count Control Register. The CTCR selects between Timer and Counter mode, and in Counter mode selects the signal and edge(s) for counting.*/
  __IO   uint32_t  PWMC; /*!< (@ 0x074) PWM Control Register. The PWMCON enables PWM mode for the external match pins CT32Bn_MAT[3:0].*/
 } LPC_CT32B0_Type; 


// ------------------------------------------------------------------------------------------------
// -----                                          ADC                                         -----
// ------------------------------------------------------------------------------------------------


/**
  * @brief Product name title=UM10462 Chapter title=LPC11U1x ADC Modification date=3/16/2011 Major revision=0 Minor revision=3  (ADC)
  */


typedef struct { 
  __IO   uint32_t  CR; /*!< (@ 0x000) A/D Control Register. The CR register must be written to select the operating mode before A/D conversion can occur.*/
  __IO   uint32_t  GDR; /*!< (@ 0x004) A/D Global Data Register. Contains the result of the most recent A/D conversion.*/
  __IO   uint32_t  SEL; /*!< (@ 0x008) A/D Select Register. Selects between external pins and internal sources.*/
  __IO   uint32_t  INTEN; /*!< (@ 0x00C) A/D Interrupt Enable Register. This register contains enable bits that allow the DONE flag of each A/D channel to be included or excluded from contributing to the generation of an A/D interrupt.*/
    union{ 
      __I   uint32_t  DR[8]; /*!< (@ 0x010) A/D Channel Data Register. This register contains the result of the most recent conversion completed on channel N*/
           struct{
          __I uint32_t DR0 ;  
          __I uint32_t DR1 ;  
          __I uint32_t DR2 ;  
          __I uint32_t DR3 ;  
          __I uint32_t DR4 ;  
          __I uint32_t DR5 ;  
          __I uint32_t DR6 ;  
          __I uint32_t DR7 ;  
        };
    };
  __I   uint32_t  STAT; /*!< (@ 0x030) A/D Status Register. This register contains DONE and OVERRUN flags for all of the A/D channels, as well as the A/D interrupt flag.*/
 } LPC_ADC_Type; 


// ------------------------------------------------------------------------------------------------
// -----                                          DAC                                         -----
// ------------------------------------------------------------------------------------------------


/**
  * @brief DAC (DAC)
  */

typedef struct {                            /*!< (@ 0x40024000) DAC Structure          */
  __IO uint32_t  CR;                        /*!< (@ 0x40024000) D/A control register   */
} LPC_DAC_Type;


// ------------------------------------------------------------------------------------------------
// -----                                          CMP                                         -----
// ------------------------------------------------------------------------------------------------


/**
  * @brief Comparator (CMP)
  */

typedef struct {                            /*!< (@ 0x40028000) CMP Structure          */
  __IO uint32_t  CTL;                       /*!< (@ 0x40028000) Comparator control register */
  __IO uint32_t  LAD;                       /*!< (@ 0x40028004) Voltage ladder register */
} LPC_CMP_Type;


// ------------------------------------------------------------------------------------------------
// -----                                          FMC                                         -----
// ------------------------------------------------------------------------------------------------


/**
  * @brief Product name title=UM10462 Chapter title=LPC11Uxx Flashprogramming firmware Modification date=12/2/2011 Major revision=2 Minor revision=0  (FMC)
  */

typedef struct {                            /*!< (@ 0x4003C000) FMC Structure          */
  __I  uint32_t  RESERVED0[4];
  __IO uint32_t  FLASHCFG;                  /*!< (@ 0x4003C010) Flash memory access time configuration register */
  __I  uint32_t  RESERVED1[3];
  __IO uint32_t  FMSSTART;                  /*!< (@ 0x4003C020) Signature start address register */
  __IO uint32_t  FMSSTOP;                   /*!< (@ 0x4003C024) Signature stop-address register */
  __I  uint32_t  RESERVED2;
    union{ 
      __I   uint32_t  FMSW[4];              /*!< (@ 0x4003C02C) Word 0 [31:0]          */
           struct{
         __I  uint32_t FMSW0;               /*!< (@ 0x4003C02C) Word 0 [31:0]          */
         __I  uint32_t FMSW1;               /*!< (@ 0x4003C030) Word 1 [63:32]         */
         __I  uint32_t FMSW2;               /*!< (@ 0x4003C034) Word 2 [95:64]         */  
         __I  uint32_t FMSW3;               /*!< (@ 0x4003C038) Word 3 [127:96]        */
        };
    };
  __I  uint32_t  RESERVED3[24];
  __IO uint32_t  EEMSSTART;                 /*!< (@ 0x4003C09C) EEPROM BIST start address register */
  __IO uint32_t  EEMSSTOP;                  /*!< (@ 0x4003C0A0) EEPROM BIST stop address register */
  __I  uint32_t  EEMSSIG;                   /*!< (@ 0x4003C0A4) EEPROM 24-bit BIST signature register */
  __I  uint32_t  RESERVED4[974];
  __I  uint32_t  FMSTAT;                    /*!< (@ 0x4003CFE0) Signature generation status register */
  __I  uint32_t  RESERVED5;
  __O  uint32_t  FMSTATCLR;                 /*!< (@ 0x4003CFE8) Signature generation status clear register */
} LPC_FMC_Type;


// ------------------------------------------------------------------------------------------------
// -----                                         SSP0                                         -----
// ------------------------------------------------------------------------------------------------


/**
  * @brief Product name title=UM10462 Chapter title=LPC11U1x SSP/SPI Modification date=3/16/2011 Major revision=0 Minor revision=3  (SSP0)
  */

typedef struct {                            /*!< (@ 0x40040000) SSP0 Structure         */
  __IO uint32_t  CR0;                       /*!< (@ 0x40040000) Control Register 0. Selects the serial clock rate, bus type, and data size. */
  __IO uint32_t  CR1;                       /*!< (@ 0x40040004) Control Register 1. Selects master/slave and other modes. */
  __IO uint32_t  DR;                        /*!< (@ 0x40040008) Data Register. Writes fill the transmit FIFO, and reads empty the receive FIFO. */
  __I  uint32_t  SR;                        /*!< (@ 0x4004000C) Status Register        */
  __IO uint32_t  CPSR;                      /*!< (@ 0x40040010) Clock Prescale Register */
  __IO uint32_t  IMSC;                      /*!< (@ 0x40040014) Interrupt Mask Set and Clear Register */
  __I  uint32_t  RIS;                       /*!< (@ 0x40040018) Raw Interrupt Status Register */
  __I  uint32_t  MIS;                       /*!< (@ 0x4004001C) Masked Interrupt Status Register */
  __O  uint32_t  ICR;                       /*!< (@ 0x40040020) SSPICR Interrupt Clear Register */
} LPC_SSP0_Type;


// ------------------------------------------------------------------------------------------------
// -----                                         IOCON                                        -----
// ------------------------------------------------------------------------------------------------


/**
  * @brief Product name title=UM10462 Chapter title=LPC11Uxx I/O configuration Modification date=12/2/2011 Major revision=2 Minor revision=0  (IOCON)
  */

typedef struct {                            /*!< (@ 0x40044000) IOCON Structure        */
  __IO uint32_t  RESET_PIO0_0;              /*!< (@ 0x40044000) I/O configuration for pin RESET/PIO0_0 */
  __IO uint32_t  PIO0_1;                    /*!< (@ 0x40044004) I/O configuration for pin P0_1/RXD/CLKOUT/CT32B0_MAT2/SSEL0/CLKIN */
  __IO uint32_t  PIO0_2;                    /*!< (@ 0x40044008) I/O configuration for pin P0_2 / I2C_SCL /ACMPO / SWCLK / CT16B0_CAP0 / unused */
  __IO uint32_t  PIO0_3;                    /*!< (@ 0x4004400C) I/O configuration for pinP0_3 / I2C_SDA /ACMPO / SWIO / CT16B1_CAP0 / unused / */
  __IO uint32_t  PIO0_4;                    /*!< (@ 0x40044010) I/O configuration for pin P0_4 / unused / AOUT /CT16B0_MAT1 / SSP0_MOSI / unused */
  __IO uint32_t  SWCLK_PIO0_5;              /*!< (@ 0x40044014) I/O configuration for pin TCK / P0_5 / VDDCMP /CT16B0_MAT2 / SSP0_SCLK / unused */
  __IO uint32_t  TDI_PIO0_6;                /*!< (@ 0x40044018) I/O configuration for pin TDI / P0_6 / AD0 /CT32B0_MAT3 / SSP0_MISO / unused */
  __IO uint32_t  TMS_PIO0_7;                /*!< (@ 0x4004401C) I/O configuration for pin TMS/P0_7/AD1/CT32B1_CAP0/CT16B0_MAT0 */
  __IO uint32_t  TDO_PIO0_8;                /*!< (@ 0x40044020) I/O configuration for pin TDO/P0_8/AD2/CT32B1_MAT0/SCK1 */
  __IO uint32_t  TRST_PIO0_9;               /*!< (@ 0x40044024) I/O configuration for pin TRST/P0_9/AD3/CT32B1_MAT1/CT16B0_MAT1/CTS */
  __IO uint32_t  SWDIO_PIO0_10;             /*!< (@ 0x40044028) I/O configuration for pin SWDIO/P0_10/AD4/ CT32B1_MAT2/CT16B0_MAT2/RTS */
  __IO uint32_t  PIO0_11;                   /*!< (@ 0x4004402C) I/O configuration for pin P0_11(WAKEUP) /UART_SCLK / AD5 / CT32B1_MAT3 /CT32B0_CAP0 / unused */
  __IO uint32_t  PIO0_12;                   /*!< (@ 0x40044030) I/O configuration for pin P0_12 / UART_RXD /ACMPO / CT32B0_MAT0 / I2C_SCL / CLKIN / */
  __IO uint32_t  PIO0_13;                   /*!< (@ 0x40044034) I/O configuration for pin P0_13 / UART_TXD /ACMPI2 / CT32B0_MAT1 / I2C_SDA / unused */
  __IO uint32_t  PIO0_14;                   /*!< (@ 0x40044038) I/O configuration for pin P0_14/MISO1/AD6/CT32B0_CAP1/CT16B1_MAT1 */
  __IO uint32_t  PIO0_15;                   /*!< (@ 0x4004403C) I/O configuration for pin P0_15/TXD/AD7/CT32B0_CAP2/SDA */
  __IO uint32_t  PIO0_16;                   /*!< (@ 0x40044040) I/O configuration for pin P0_16 / ATRG0 /ACMPI3 / CT16B0_CAP1 / I2C_SCL / unused */
  __IO uint32_t  PIO0_17;                   /*!< (@ 0x40044044) I/O configuration for pin P0_17 / ATRG1 /ACMPI4 / CT16B0_CAP2 / CT16B0_MAT0 /unused  */
  __IO uint32_t  PIO0_18;                   /*!< (@ 0x40044048) I/O configuration for pin P0_18/SSEL0/CT16B0_CAP0/CT16B1_CAP1 */
  __IO uint32_t  PIO0_19;                   /*!< (@ 0x4004404C) I/O configuration for pin P0_19/CLKIN/CLKOUT/MOSI0/CT16B1_MAT0 */
  __IO uint32_t  PIO0_20;                   /*!< (@ 0x40044050) I/O configuration for pin P0_20 / unused /SSP0_SCLK / CT32B1_CAP0 / CT16B1_MAT2 /unused */
  __IO uint32_t  PIO0_21;                   /*!< (@ 0x40044054) I/O configuration for pin P0_21/CTS/ACMPO/CT32B1_CAP1/SCLK */
  __IO uint32_t  PIO0_22;                   /*!< (@ 0x40044058) I/O configuration for pin P0_22/MISO0/ACMPI5/CT32B1_MAT2/CT32B1_CAP2 */
  __IO uint32_t  PIO0_23;                   /*!< (@ 0x4004405C) I/O configuration for pin P0_23/RTS/ACMPO/CT32B0_CAP0/SCLK */
  __IO uint32_t  PIO0_24;                   /*!< (@ 0x40044060) I/O configuration for pin P0_24/SCL/CLKIN/CT16B1_CAP0 */
  __IO uint32_t  PIO0_25;                   /*!< (@ 0x40044064) I/O configuration for pin P0_25/SDA/SSEL1/CT16B1_MAT0 */
  __IO uint32_t  PIO0_26;                   /*!< (@ 0x40044068) I/O configuration for pin P0_26/TXD/MISO1/CT16B1_CAP1/CT32B0_CAP2 */
  __IO uint32_t  PIO0_27;                   /*!< (@ 0x4004406C) I/O configuration for pin P0_27/MOSI1/ACMPI1/CT32B1_MAT1/CT16B1_CAP2 */
  __IO uint32_t  PIO0_28;                   /*!< (@ 0x40044070) I/O configuration for pin P0_28 / UART_nDTR /SSP1_SSEL / CT32B0_CAP0 / unused / unused */
  __IO uint32_t  PIO0_29;                   /*!< (@ 0x40044074) I/O configuration for pin P0_29 / UART_nDSR /SSP1_SCLK / CT32B0_CAP1 / unused / unused */
  __IO uint32_t  PIO0_30;                   /*!< (@ 0x40044078) I/O configuration for pin P0_30 / UART_nRI /SSP1_MOSI / CT32B0_MAT0 / CT16B0_CAP0 /unused */
  __IO uint32_t  PIO0_31;                   /*!< (@ 0x4004407C) I/O configuration for pin P0_31 / UART_nRI /SSP1_MOSI / CT32B1_MAT0 / CT16B1_CAP1 /unused */
  __IO uint32_t  PIO1_0;                    /*!< (@ 0x40044080) I/O configuration for pin P1_0/DCD/SCK0/CT32B1_MAT3/CT16B0_MAT1 */
  __IO uint32_t  PIO1_1;                    /*!< (@ 0x40044084) I/O configuration for pin P1_1/DTR/SSEL0/CT32B1_MAT3/CT16B1_MAT0 */
  __IO uint32_t  PIO1_2;                    /*!< (@ 0x40044088) I/O configuration for pin 1_2/DSR/MISO0/CT16B1_MAT2/CT16B1_MAT1 */
  __IO uint32_t  PIO1_3;                    /*!< (@ 0x4004408C) I/O configuration for pin P1_3/RI/MOSI0/CT16B1_CAP0 */
  __IO uint32_t  PIO1_4;                    /*!< (@ 0x40044090) I/O configuration for pin P1_4/RxD/SSEL1/CT32B0_MAT1/CT32B1_CAP0/CT16B0_CAP1 */
  __IO uint32_t  PIO1_5;                    /*!< (@ 0x40044094) I/O configuration for pin P1_5/TxD/SCK1/CT32B0_MAT2/CT32B1_CAP1/CT16B0_CAP2 */
  __IO uint32_t  PIO1_6;                    /*!< (@ 0x40044098) I/O configuration for pin P1_6/RTS/MOSI1/CT32B0_MAT3/CT32B1_CAP2/CT16B0_MAT0 */
  __IO uint32_t  PIO1_7;                    /*!< (@ 0x4004409C) I/O configuration for pin P1_7/CTS/MOSI0/CT32B1_MAT1/CT16B0_MAT2/CT16B1_CAP2 */
  __IO uint32_t  PIO1_8;                    /*!< (@ 0x400440A0) I/O configuration for pin P1_8/RxD/MISO1/CT32B1_MAT0/CT16B1_MAT1 */
  __IO uint32_t  PIO1_9;                    /*!< (@ 0x400440A4) I/O configuration for pin P1_9/DCD/CT32B1_MAT2/CT16B1_MAT2 */
} LPC_IOCON_Type;


// ------------------------------------------------------------------------------------------------
// -----                                        SYSCON                                        -----
// ------------------------------------------------------------------------------------------------


/**
  * @brief Product name title=UMnnnnn Chapter title=LPC11Axx System configuration Modification date=4/13/2011 Major revision=0 Minor revision=12  (SYSCON)
  */

typedef struct {                            /*!< (@ 0x40048000) SYSCON Structure       */
  __IO uint32_t  SYSMEMREMAP;               /*!< (@ 0x40048000) System memory remap    */
  __IO uint32_t  PRESETCTRL;                /*!< (@ 0x40048004) Peripheral reset control */
  __IO uint32_t  SYSPLLCTRL;                /*!< (@ 0x40048008) System PLL control     */
  __I  uint32_t  SYSPLLSTAT;                /*!< (@ 0x4004800C) System PLL status      */
  __I  uint32_t  RESERVED0[5];
  __IO uint32_t  WDTOSCCTRL;                /*!< (@ 0x40048024) Watchdog oscillator control */
  __IO uint32_t  IRCCTRL;                   /*!< (@ 0x40048028) IRC oscillator control */
  __IO uint32_t  LFOSCCTRL;                 /*!< (@ 0x4004802C) LF oscillator control  */
  __IO uint32_t  SYSRSTSTAT;                /*!< (@ 0x40048030) System reset status register */
  __I  uint32_t  RESERVED1[3];
  __IO uint32_t  SYSPLLCLKSEL;              /*!< (@ 0x40048040) System PLL clock source select */
  __IO uint32_t  SYSPLLCLKUEN;              /*!< (@ 0x40048044) System PLL clock source update enable */
  __I  uint32_t  RESERVED2[10];
  __IO uint32_t  MAINCLKSEL;                /*!< (@ 0x40048070) Main clock source select */
  __IO uint32_t  MAINCLKUEN;                /*!< (@ 0x40048074) Main clock source update enable */
  __IO uint32_t  SYSAHBCLKDIV;              /*!< (@ 0x40048078) System clock divider   */
  __I  uint32_t  RESERVED3;
  __IO uint32_t  SYSAHBCLKCTRL;             /*!< (@ 0x40048080) System clock control   */
  __I  uint32_t  RESERVED4[4];
  __IO uint32_t  SSP0CLKDIV;                /*!< (@ 0x40048094) SSP0 clock divider     */
  __IO uint32_t  UARTCLKDIV;                /*!< (@ 0x40048098) UART clock divider     */
  __IO uint32_t  SSP1CLKDIV;                /*!< (@ 0x4004809C) SSP1 clock divider     */
  __I  uint32_t  RESERVED5[16];
  __IO uint32_t  CLKOUTSEL;                 /*!< (@ 0x400480E0) CLKOUT clock source select */
  __IO uint32_t  CLKOUTUEN;                 /*!< (@ 0x400480E4) CLKOUT clock source update enable */
  __IO uint32_t  CLKOUTDIV;                 /*!< (@ 0x400480E8) CLKOUT clock divider   */
  __I  uint32_t  RESERVED6[5];
  __I  uint32_t  PIOPORCAP0;                /*!< (@ 0x40048100) POR captured PIO status 0 */
  __I  uint32_t  PIOPORCAP1;                /*!< (@ 0x40048104) POR captured PIO status 1 */
  __I  uint32_t  RESERVED7[18];
  __IO uint32_t  BODR;                      /*!< (@ 0x40048150) Brown-Out Detect       */
  __I  uint32_t  RESERVED8;
  __IO uint32_t  SYSTCKCAL;                 /*!< (@ 0x40048158) System tick counter calibration */
  __I  uint32_t  RESERVED9[6];
  __IO uint32_t  NMISRC;                    /*!< (@ 0x40048174) NMI Source Control     */
    union{ 
      __IO   uint32_t  PINSEL[8];           /*!< (@ 0x40048178) Pin Select Control     */
           struct{
         __IO  uint32_t PINSEL0;  
         __IO  uint32_t PINSEL1;
         __IO  uint32_t PINSEL2;  
         __IO  uint32_t PINSEL3;
         __IO  uint32_t PINSEL4;  
         __IO  uint32_t PINSEL5;
         __IO  uint32_t PINSEL6;  
         __IO  uint32_t PINSEL7;    
        };
    };
  __I  uint32_t  RESERVED10[40];
  __IO uint32_t  PDRUNCFG;                  /*!< (@ 0x40048238) Power configuration register */
  __I  uint32_t  RESERVED11[110];
  __I  uint32_t  DEVICE_ID;                 /*!< (@ 0x400483F4) Device ID              */
} LPC_SYSCON_Type;


// ------------------------------------------------------------------------------------------------
// -----                                     GPIO_PIN_INT                                     -----
// ------------------------------------------------------------------------------------------------


/**
  * @brief Product name title=UM10462 Chapter title=LPC11U1x GPIO Modification date=3/17/2011 Major revision=0 Minor revision=3  (GPIO_PIN_INT)
  */

typedef struct {                            /*!< (@ 0x4004C000) GPIO_PIN_INT Structure */
  __IO uint32_t  ISEL;                      /*!< (@ 0x4004C000) Pin Interrupt Mode register */
  __IO uint32_t  IENR;                      /*!< (@ 0x4004C004) Pin Interrupt Enable (Rising) register */
  __O  uint32_t  SIENR;                     /*!< (@ 0x4004C008) Set Pin Interrupt Enable (Rising) register */
  __O  uint32_t  CIENR;                     /*!< (@ 0x4004C00C) Clear Pin Interrupt Enable (Rising) register */
  __IO uint32_t  IENF;                      /*!< (@ 0x4004C010) Pin Interrupt Enable Falling Edge / Active Level register */
  __O  uint32_t  SIENF;                     /*!< (@ 0x4004C014) Set Pin Interrupt Enable Falling Edge / Active Level register */
  __O  uint32_t  CIENF;                     /*!< (@ 0x4004C018) Clear Pin Interrupt Enable Falling Edge / Active Level address */
  __IO uint32_t  RISE;                      /*!< (@ 0x4004C01C) Pin Interrupt Rising Edge register */
  __IO uint32_t  FALL;                      /*!< (@ 0x4004C020) Pin Interrupt Falling Edge register */
  __IO uint32_t  IST;                       /*!< (@ 0x4004C024) Pin Interrupt Status register */
} LPC_GPIO_PIN_INT_Type;


// ------------------------------------------------------------------------------------------------
// -----                                    GPIO_GROUP_INT0                                   -----
// ------------------------------------------------------------------------------------------------


/**
  * @brief Product name title=UM10462 Chapter title=LPC11U1x GPIO Modification date=3/17/2011 Major revision=0 Minor revision=3  (GPIO_GROUP_INT0)
  */
typedef struct { 
  __IO   uint32_t  CTRL; /*!< (@ 0x000) GPIO grouped interrupt control register*/
   __I  uint32_t  RESERVED0[7];
    union{ 
      __IO   uint32_t  PORT_POL[2]; /*!< (@ 0x020) GPIO grouped interrupt port 0 polarity register*/
           struct{
         __IO  uint32_t PORT_POL0 ;  
         __IO  uint32_t PORT_POL1 ;  
        };
    };
  __I  uint32_t  RESERVED1[6];
    union{ 
      __IO   uint32_t  PORT_ENA[2]; /*!< (@ 0x040) GPIO grouped interrupt port 0/1 enable register*/
           struct{
         __IO  uint32_t PORT_ENA0 ;  
         __IO  uint32_t PORT_ENA1 ;  
        };
    };
 } LPC_GPIO_GROUP_INT_Type; 

// ------------------------------------------------------------------------------------------------
// -----                                       GPIO_PORT                                      -----
// ------------------------------------------------------------------------------------------------

/**
  * @brief Product name title=UM10462 Chapter title=LPC11U1x GPIO Modification date=3/17/2011 Major revision=0 Minor revision=3  (GPIO_PORT)
  */
typedef struct { 
  __IO   uint8_t   B0[32]; /*!< (@ 0x0000) Byte pin registers port 0; pins PIO0_0 to PIO0_31*/
  __IO   uint8_t   B1[10]; /*!< (@ 0x0020) Byte pin registers port 1*/
  __I    uint8_t   RESERVED0[4054];
  __IO   uint32_t  W0[32]; /*!< (@ 0x1000) Word pin registers port 0*/
  __IO   uint32_t  W1[10]; /*!< (@ 0x1080) Word pin registers port 1*/
  __I    uint32_t  RESERVED1[982];
  __IO   uint32_t  DIR[2]; /*!< (@ 0x2000) Direction registers port 0/1*/
  __I    uint32_t  RESERVED2[30];
  __IO   uint32_t  MASK[2]; /*!< (@ 0x2080) Mask register port 0/1*/
  __I    uint32_t  RESERVED3[30];
  __IO   uint32_t  PIN[2]; /*!< (@ 0x2100) Portpin register port 0*/
  __I    uint32_t  RESERVED4[30]; 
  __IO   uint32_t  MPIN[2]; /*!< (@ 0x2180) Masked port register port 0/1*/
  __I    uint32_t  RESERVED5[30];
  __IO   uint32_t  SET[2]; /*!< (@ 0x2200) Write: Set register for port 0/1  Read: output bits for port 0/1*/
  __I    uint32_t  RESERVED6[30];
  __O    uint32_t  CLR[2]; /*!< (@ 0x2280) Clear port 0/1*/
  __I    uint32_t  RESERVED7[30];
  __O    uint32_t  NOT[2]; /*!< (@ 0x2300) Toggle port 0/1*/
 } LPC_GPIO_PORT_Type; 

/********************************************
** End of section using anonymous unions   **
*********************************************/

#if defined(__ARMCC_VERSION)
  #pragma pop
#elif defined(__CWCC__)
  #pragma pop
#elif defined(__GNUC__)
  /* leave anonymous unions enabled */
#elif defined(__IAR_SYSTEMS_ICC__)
  #pragma pop
#else
  #error Not supported compiler type
#endif


/******************************************************************************/
/*                         Peripheral memory map                              */
/******************************************************************************/
/* Base addresses                                                             */
#define LPC_RAM_BASE          (0x10000000)
#define LPC_APB0_BASE         (0x40000000)
#define LPC_AHB_BASE          (0x50000000)

/* APB0 peripherals                                                           */
#define LPC_I2C_BASE          (LPC_APB0_BASE + 0x00000)
#define LPC_WWDT_BASE         (LPC_APB0_BASE + 0x04000)
#define LPC_USART_BASE        (LPC_APB0_BASE + 0x08000)
#define LPC_CT16B0_BASE       (LPC_APB0_BASE + 0x0C000)
#define LPC_CT16B1_BASE       (LPC_APB0_BASE + 0x10000)
#define LPC_CT32B0_BASE       (LPC_APB0_BASE + 0x14000)
#define LPC_CT32B1_BASE       (LPC_APB0_BASE + 0x18000)
#define LPC_ADC_BASE          (LPC_APB0_BASE + 0x1C000)
#define LPC_DAC_BASE          (LPC_APB0_BASE + 0x24000)
#define LPC_CMP_BASE          (LPC_APB0_BASE + 0x28000)
#define LPC_SSP0_BASE         (LPC_APB0_BASE + 0x40000)
#define LPC_IOCON_BASE        (LPC_APB0_BASE + 0x44000)
#define LPC_SYSCON_BASE       (LPC_APB0_BASE + 0x48000)
#define LPC_SSP1_BASE         (LPC_APB0_BASE + 0x58000)


/* AHB peripherals                                                            */
#define LPC_EEPROM_BASE           (LPC_FMC_BASE  + 0x00080)      
#define LPC_FMC_BASE              (LPC_APB0_BASE + 0x3C000)      
#define LPC_GPIO_PIN_INT_BASE     (LPC_APB0_BASE + 0x4C000)      
#define LPC_GPIO_GROUP_INT0_BASE  (LPC_APB0_BASE + 0x5C000)      
#define LPC_GPIO_GROUP_INT1_BASE  (LPC_APB0_BASE + 0x60000)      
#define LPC_GPIO_PORT_BASE        (LPC_AHB_BASE  + 0x00000)


// ------------------------------------------------------------------------------------------------
// -----                                Peripheral declaration                                -----
// ------------------------------------------------------------------------------------------------

#define LPC_I2C                   ((LPC_I2C_Type            *) LPC_I2C_BASE)
#define LPC_WWDT                  ((LPC_WWDT_Type           *) LPC_WWDT_BASE)
#define LPC_USART                 ((LPC_USART_Type          *) LPC_USART_BASE)
#define LPC_CT16B0                ((LPC_CT16B0_Type         *) LPC_CT16B0_BASE)
#define LPC_CT16B1                ((LPC_CT16B0_Type         *) LPC_CT16B1_BASE)
#define LPC_CT32B0                ((LPC_CT32B0_Type         *) LPC_CT32B0_BASE)
#define LPC_CT32B1                ((LPC_CT32B0_Type         *) LPC_CT32B1_BASE)
#define LPC_ADC                   ((LPC_ADC_Type            *) LPC_ADC_BASE)
#define LPC_DAC                   ((LPC_DAC_Type            *) LPC_DAC_BASE)
#define LPC_CMP                   ((LPC_CMP_Type            *) LPC_CMP_BASE)
#define LPC_FMC                   ((LPC_FMC_Type            *) LPC_FMC_BASE)
#define LPC_SSP0                  ((LPC_SSP0_Type           *) LPC_SSP0_BASE)
#define LPC_IOCON                 ((LPC_IOCON_Type          *) LPC_IOCON_BASE)
#define LPC_SYSCON                ((LPC_SYSCON_Type         *) LPC_SYSCON_BASE)
#define LPC_GPIO_PIN_INT          ((LPC_GPIO_PIN_INT_Type   *) LPC_GPIO_PIN_INT_BASE)
#define LPC_SSP1                  ((LPC_SSP0_Type           *) LPC_SSP1_BASE)
#define LPC_GPIO_GROUP_INT0       ((LPC_GPIO_GROUP_INT_Type *) LPC_GPIO_GROUP_INT0_BASE)
#define LPC_GPIO_GROUP_INT1       ((LPC_GPIO_GROUP_INT_Type *) LPC_GPIO_GROUP_INT1_BASE)
#define LPC_GPIO_PORT             ((LPC_GPIO_PORT_Type      *) LPC_GPIO_PORT_BASE)


/** @} */ /* End of group Device_Peripheral_Registers */
/** @} */ /* End of group LPC11Axx */
/** @} */ /* End of group (null) */

#ifdef __cplusplus
}
#endif 


#endif  // __LPC11Axx_H__

