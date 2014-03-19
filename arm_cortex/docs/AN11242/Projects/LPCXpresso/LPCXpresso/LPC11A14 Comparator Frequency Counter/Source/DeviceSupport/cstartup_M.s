/**************************************************
 *
 * Part one of the system initialization code, contains low-level
 * initialization, plain thumb variant.
 *
 * Copyright 2011 IAR Systems. All rights reserved.
 *
 * $Revision: 47021 $
 *
 **************************************************/

;
; The modules in this file are included in the libraries, and may be replaced
; by any user-defined modules that define the PUBLIC symbol _program_start or
; a user defined start symbol.
; To override the cstartup defined in the library, simply add your modified
; version to the workbench project.
;
; The vector table is normally located at address 0.
; When debugging in RAM, it can be located in RAM, aligned to at least 2^6.
; The name "__vector_table" has special meaning for C-SPY:
; it is where the SP start value is found, and the NVIC vector
; table register (VTOR) is initialized to this address if != 0.
;
; Cortex-M version
;

        MODULE  ?cstartup

        ;; Forward declaration of sections.
        SECTION CSTACK:DATA:NOROOT(3)

        SECTION .intvec:CODE:NOROOT(2)

        EXTERN  __iar_program_start

        PUBLIC  __vector_table
        PUBLIC  __vector_table_0x1c
        DATA


__vector_table
                DCD     sfe(CSTACK)                 ; Top of Stack
                DCD     __iar_program_start         ; Reset Handler
                DCD     NMI_Handler                 ; NMI Handler
                DCD     HardFault_Handler           ; Hard Fault Handler
                DCD     MemManage_Handler           ; MPU Fault Handler
                DCD     BusFault_Handler            ; Bus Fault Handler
                DCD     UsageFault_Handler          ; Usage Fault Handler
__vector_table_0x1c
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     SVC_Handler               ; SVCall Handler
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     PendSV_Handler            ; PendSV Handler
                DCD     SysTick_Handler           ; SysTick Handler

                ; External Interrupts
                DCD     GPIO0_IRQHandler      ; All GPIO pin can be routed to FLEX_INTx
                DCD     GPIO1_IRQHandler          
                DCD     GPIO2_IRQHandler                       
                DCD     GPIO3_IRQHandler                         
                DCD     GPIO4_IRQHandler                        
                DCD     GPIO5_IRQHandler
                DCD     GPIO6_IRQHandler
                DCD     GPIO7_IRQHandler                       
                DCD     GROUP0_IRQHandler                         
                DCD     GROUP1_IRQHandler         ; PIO0 (0:7)              
                DCD     AComparator_IRQHandler    ; Analog Comparator
                DCD     DAC_IRQHandler
                DCD     Reserved_IRQHandler       
                DCD     Reserved_IRQHandler                       
                DCD     SSP1_IRQHandler           ; SSP1               
                DCD     I2C_IRQHandler            ; I2C
                DCD     TIMER16_B0_IRQHandler     ; 16-bit Timer0
                DCD     TIMER16_B1_IRQHandler     ; 16-bit Timer1
                DCD     TIMER32_B0_IRQHandler     ; 32-bit Timer0
                DCD     TIMER32_B1_IRQHandler     ; 32-bit Timer1
                DCD     SSP0_IRQHandler           ; SSP0
                DCD     UART_IRQHandler           ; UART
                DCD     Reserved_IRQHandler       ; 
                DCD     Reserved_IRQHandler       ; 
                DCD     ADC_IRQHandler            ; A/D Converter
                DCD     WDT_IRQHandler            ; Watchdog timer
                DCD     BOD_IRQHandler            ; Brown Out Detect
                DCD     FMC_IRQHandler            ; Flash Memory Controller
                DCD     Reserved_IRQHandler       ; Reserved
                DCD     Reserved_IRQHandler       ; Reserved
                DCD     Reserved_IRQHandler       ; 
                DCD     Reserved_IRQHandler       ; Reserved


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; Default interrupt handlers.
;;
        THUMB
        SECTION .text:CODE:REORDER:NOROOT(1)
        PUBWEAK NMI_Handler
        PUBWEAK HardFault_Handler
        PUBWEAK MemManage_Handler
        PUBWEAK BusFault_Handler
        PUBWEAK UsageFault_Handler
        PUBWEAK SVC_Handler
        PUBWEAK DebugMon_Handler
        PUBWEAK PendSV_Handler
        PUBWEAK SysTick_Handler
        PUBWEAK GPIO0_IRQHandler
        PUBWEAK GPIO1_IRQHandler
        PUBWEAK GPIO2_IRQHandler
        PUBWEAK GPIO3_IRQHandler
        PUBWEAK GPIO4_IRQHandler
        PUBWEAK GPIO5_IRQHandler
        PUBWEAK GPIO6_IRQHandler
        PUBWEAK GPIO7_IRQHandler
        PUBWEAK GROUP0_IRQHandler
        PUBWEAK GROUP1_IRQHandler
        PUBWEAK AComparator_IRQHandler
        PUBWEAK DAC_IRQHandler
        PUBWEAK SSP1_IRQHandler
        PUBWEAK I2C_IRQHandler
        PUBWEAK TIMER16_B0_IRQHandler
        PUBWEAK TIMER16_B1_IRQHandler
        PUBWEAK TIMER32_B0_IRQHandler
        PUBWEAK TIMER32_B1_IRQHandler
        PUBWEAK SSP0_IRQHandler
        PUBWEAK UART_IRQHandler
        PUBWEAK ADC_IRQHandler
        PUBWEAK WDT_IRQHandler
        PUBWEAK BOD_IRQHandler
        PUBWEAK FMC_IRQHandler
        PUBWEAK Reserved_IRQHandler

NMI_Handler
HardFault_Handler
MemManage_Handler
BusFault_Handler
UsageFault_Handler
SVC_Handler
DebugMon_Handler
PendSV_Handler
SysTick_Handler
GPIO0_IRQHandler
GPIO1_IRQHandler
GPIO2_IRQHandler
GPIO3_IRQHandler
GPIO4_IRQHandler
GPIO5_IRQHandler
GPIO6_IRQHandler
GPIO7_IRQHandler
GROUP0_IRQHandler
GROUP1_IRQHandler
AComparator_IRQHandler
DAC_IRQHandler
SSP1_IRQHandler
I2C_IRQHandler
TIMER16_B0_IRQHandler
TIMER16_B1_IRQHandler
TIMER32_B0_IRQHandler
TIMER32_B1_IRQHandler
SSP0_IRQHandler
UART_IRQHandler
ADC_IRQHandler
WDT_IRQHandler
BOD_IRQHandler
FMC_IRQHandler
Reserved_IRQHandler
Default_Handler:
        B Default_Handler
        
        SECTION .crp:CODE:ROOT(2)
        DATA
/* Code Read Protection
NO_ISP  0x4E697370 -  Prevents sampling of pin PIO0_1 for entering ISP mode
CRP1    0x12345678 - Write to RAM command cannot access RAM below 0x10000300.
                   - Copy RAM to flash command can not write to Sector 0.
                   - Erase command can erase Sector 0 only when all sectors
                     are selected for erase.
                   - Compare command is disabled.
                   - Read Memory command is disabled.
CRP2    0x87654321 - Read Memory is disabled.
                   - Write to RAM is disabled.
                   - "Go" command is disabled.
                   - Copy RAM to flash is disabled.
                   - Compare is disabled.
CRP3    0x43218765 - Access to chip via the SWD pins is disabled. ISP entry
                     by pulling PIO0_1 LOW is disabled if a valid user code is
                     present in flash sector 0.
Caution: If CRP3 is selected, no future factory testing can be
performed on the device.
*/
	DCD	0xFFFFFFFF

        END
