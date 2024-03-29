/**
 ******************************************************************************
 * @file      startup_lpc11xx.c
 * @author    Coocox
 * @version   V1.0
 * @date      12/23/2009
 * @brief     LPC11XX Devices Startup code.
 *            This module performs:
 *                - Set the initial SP
 *                - Set the vector table entries with the exceptions ISR address
 *                - Initialize data and bss
 *                - Setup the microcontroller system.
 *                - Call the application's entry point.
 *******************************************************************************
 */
 

/*----------Stack Configuration-----------------------------------------------*/  
#define STACK_SIZE       0x00000100      /*!< Stack size (in Words)           */
__attribute__ ((section(".stack")))      /*!< Section of Stack                */
unsigned long pulStack[STACK_SIZE];      


/*----------Macro definition--------------------------------------------------*/  
#define WEAK __attribute__ ((weak))           


/*----------Declaration of the default fault handlers-------------------------*/  
/* System exception vector handler */
void WEAK  Reset_Handler(void);
void WEAK  NMI_Handler(void);
void WEAK  HardFault_Handler(void);
void WEAK  MemManage_Handler(void);
void WEAK  BusFault_Handler(void);
void WEAK  UsageFault_Handler(void);
void WEAK  SVC_Handler(void);
void WEAK  DebugMon_Handler(void);
void WEAK  PendSV_Handler(void);
void WEAK  SysTick_Handler(void);
void WEAK  WAKEUP_IRQHandler(void);
void WEAK  CAN_IRQHandler(void); 
void WEAK  SSP1_IRQHandler(void);
void WEAK  I2C_IRQHandler(void);
void WEAK  TIMER16_0_IRQHandler(void);
void WEAK  TIMER16_1_IRQHandler(void);
void WEAK  TIMER32_0_IRQHandler(void);
void WEAK  TIMER32_1_IRQHandler(void);
void WEAK  SSP0_IRQHandler(void);
void WEAK  UART_IRQHandler(void);
void WEAK  USB_IRQHandler(void);
void WEAK  USB_FIQHandler(void);
void WEAK  ADC_IRQHandler(void);
void WEAK  WDT_IRQHandler(void);
void WEAK  BOD_IRQHandler(void);
void WEAK  FMC_IRQHandler(void);
void WEAK  PIOINT3_IRQHandler(void);
void WEAK  PIOINT2_IRQHandler(void);
void WEAK  PIOINT1_IRQHandler(void);
void WEAK  PIOINT0_IRQHandler(void);   


/*----------Symbols defined in linker script----------------------------------*/  
extern unsigned long _sidata;    /*!< Start address for the initialization 
                                      values of the .data section.            */
extern unsigned long _sdata;     /*!< Start address for the .data section     */    
extern unsigned long _edata;     /*!< End address for the .data section       */    
extern unsigned long _sbss;      /*!< Start address for the .bss section      */
extern unsigned long _ebss;      /*!< End address for the .bss section        */      
extern void _eram;               /*!< End address for ram                     */


/*----------Function prototypes-----------------------------------------------*/  
extern int main(void);           /*!< The entry point for the application.    */
extern void SystemInit(void);    /*!< Setup the microcontroller system(CMSIS) */
void Default_Reset_Handler(void);   /*!< Default reset handler                */
static void Default_Handler(void);  /*!< Default exception handler            */


/**
  *@brief The minimal vector table for a Cortex M3.  Note that the proper constructs
  *       must be placed on this to ensure that it ends up at physical address
  *       0x00000000.  
  */
__attribute__ ((section(".isr_vector")))
void (* const g_pfnVectors[])(void) =
{	
  /*----------Core Exceptions------------------------------------------------ */
  (void *)&pulStack[STACK_SIZE-1],     /*!< The initial stack pointer         */  
  Reset_Handler,             /*!< Reset Handler                               */
  NMI_Handler,               /*!< NMI Handler                                 */
  HardFault_Handler,         /*!< Hard Fault Handler                          */ 
  MemManage_Handler,         /*!< MPU Fault Handler                           */ 
  BusFault_Handler,          /*!< Bus Fault Handler                           */
  UsageFault_Handler,        /*!< Usage Fault Handler                         */
  0,0,0,0,                   /*!< Reserved                                    */
  SVC_Handler,               /*!< SVCall Handler                              */
  DebugMon_Handler,          /*!< Debug Monitor Handler                       */
  0,                         /*!< Reserved                                    */
  PendSV_Handler,            /*!< PendSV Handler                              */
  SysTick_Handler,           /*!< SysTick Handler                             */ 
  
  /*----------External Exceptions---------------------------------------------*/                
  WAKEUP_IRQHandler,         /*!< 15 wakeup sources for all the               */
  WAKEUP_IRQHandler,         /*!< I/O pins starting from PIO0 (0:11)          */
  WAKEUP_IRQHandler,         /*!< all 40 are routed to the same ISR           */                   
  WAKEUP_IRQHandler,                         
  WAKEUP_IRQHandler,                        
  WAKEUP_IRQHandler,
  WAKEUP_IRQHandler,
  WAKEUP_IRQHandler,                       
  WAKEUP_IRQHandler,                         
  WAKEUP_IRQHandler,                        
  WAKEUP_IRQHandler,
  WAKEUP_IRQHandler,
  WAKEUP_IRQHandler,         /*!< PIO1 (0:11)                                 */
  CAN_IRQHandler,            /*!< CAN                                         */              
  SSP1_IRQHandler,           /*!< SSP1                                        */       
  I2C_IRQHandler,            /*!< I2C                                         */ 
  TIMER16_0_IRQHandler,      /*!< 16-bit Timer0                               */
  TIMER16_1_IRQHandler,      /*!< 16-bit Timer1                               */
  TIMER32_0_IRQHandler,      /*!< 32-bit Timer0                               */ 
  TIMER32_1_IRQHandler,      /*!< 32-bit Timer1                               */
  SSP0_IRQHandler,           /*!< SSP0                                        */
  UART_IRQHandler,           /*!< UART                                        */
  USB_IRQHandler,            /*!< USB IRQ                                     */
  USB_FIQHandler,            /*!< USB FIQ                                     */
  ADC_IRQHandler,            /*!< A/D Converter                               */
  WDT_IRQHandler,            /*!< Watchdog timer                              */
  BOD_IRQHandler,            /*!< Brown Out Detect                            */
  FMC_IRQHandler,            /*!< IP2111 Flash Memory Controller              */
  PIOINT3_IRQHandler,        /*!< PIO INT3                                    */
  PIOINT2_IRQHandler,        /*!< PIO INT2                                    */
  PIOINT1_IRQHandler,        /*!< PIO INT1                                    */
  PIOINT0_IRQHandler,        /*!< PIO INT0                                    */
};


/**
  * @brief  This is the code that gets called when the processor first
  *         starts execution following a reset event. Only the absolutely
  *         necessary set is performed, after which the application
  *         supplied main() routine is called. 
  * @param  None
  * @retval None
  */
void Default_Reset_Handler(void)
{
  /* Initialize data and bss */
  unsigned long *pulSrc, *pulDest;

  /* Copy the data segment initializers from flash to SRAM */
  pulSrc = &_sidata;

  for(pulDest = &_sdata; pulDest < &_edata; )
  {
    *(pulDest++) = *(pulSrc++);
  }
  
  /* Zero fill the bss segment.  This is done with inline assembly since this
     will clear the value of pulDest if it is not kept in a register. */
  __asm("  ldr     r0, =_sbss\n"
        "  ldr     r1, =_ebss\n"
        "  mov     r2, #0\n"
        "  .thumb_func\n"
        "zero_loop:\n"
        "    cmp     r0, r1\n"
        "    it      lt\n"
        "    strlt   r2, [r0], #4\n"
        "    blt     zero_loop");

  /* Setup the microcontroller system. */
  SystemInit();
	
  /* Call the application's entry point.*/
  main();
}


/**
  *@brief Provide weak aliases for each Exception handler to the Default_Handler. 
  *       As they are weak aliases, any function with the same name will override 
  *       this definition.
  */
#pragma weak Reset_Handler = Default_Handler
#pragma weak NMI_Handler = Default_Handler
#pragma weak HardFault_Handler = Default_Handler
#pragma weak MemManage_Handler = Default_Handler
#pragma weak BusFault_Handler = Default_Handler
#pragma weak UsageFault_Handler = Default_Handler
#pragma weak SVC_Handler = Default_Handler
#pragma weak DebugMon_Handler = Default_Handler
#pragma weak PendSV_Handler = Default_Handler
#pragma weak SysTick_Handler = Default_Handler
#pragma weak WAKEUP_IRQHandler = Default_Handler
#pragma weak CAN_IRQHandler = Default_Handler 
#pragma weak SSP1_IRQHandler = Default_Handler
#pragma weak I2C_IRQHandler = Default_Handler
#pragma weak TIMER16_0_IRQHandler = Default_Handler
#pragma weak TIMER16_1_IRQHandler = Default_Handler
#pragma weak TIMER32_0_IRQHandler = Default_Handler
#pragma weak TIMER32_1_IRQHandler = Default_Handler
#pragma weak SSP0_IRQHandler = Default_Handler
#pragma weak UART_IRQHandler = Default_Handler
#pragma weak USB_IRQHandler = Default_Handler
#pragma weak USB_FIQHandler = Default_Handler
#pragma weak ADC_IRQHandler = Default_Handler
#pragma weak WDT_IRQHandler = Default_Handler
#pragma weak BOD_IRQHandler = Default_Handler
#pragma weak FMC_IRQHandler = Default_Handler
#pragma weak PIOINT3_IRQHandler = Default_Handler
#pragma weak PIOINT2_IRQHandler = Default_Handler
#pragma weak PIOINT1_IRQHandler = Default_Handler
#pragma weak PIOINT0_IRQHandler = Default_Handler      


/**
  * @brief  This is the code that gets called when the processor receives an 
  *         unexpected interrupt.  This simply enters an infinite loop, 
  *         preserving the system state for examination by a debugger.
  * @param  None
  * @retval None  
  */
static void Default_Handler(void) 
{
	/* Go into an infinite loop. */
	while (1) 
	{
	}
}

/*********************** (C) COPYRIGHT 2010 Coocox ************END OF FILE*****/
