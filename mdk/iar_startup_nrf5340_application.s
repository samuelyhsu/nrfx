; Copyright (c) 2009-2021 ARM Limited. All rights reserved.
; 
;     SPDX-License-Identifier: Apache-2.0
; 
; Licensed under the Apache License, Version 2.0 (the License); you may
; not use this file except in compliance with the License.
; You may obtain a copy of the License at
; 
;     www.apache.org/licenses/LICENSE-2.0
; 
; Unless required by applicable law or agreed to in writing, software
; distributed under the License is distributed on an AS IS BASIS, WITHOUT
; WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
; See the License for the specific language governing permissions and
; limitations under the License.
; 
; NOTICE: This file has been modified by Nordic Semiconductor ASA.

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

        MODULE  ?cstartup

#if defined(__STARTUP_CONFIG)

        #include "startup_config.h"

        #ifndef __STARTUP_CONFIG_STACK_ALIGNEMENT
        #define __STARTUP_CONFIG_STACK_ALIGNEMENT 3
        #endif
        
        SECTION CSTACK:DATA:NOROOT(__STARTUP_CONFIG_STACK_ALIGNEMENT)
        DS8 __STARTUP_CONFIG_STACK_SIZE

        SECTION HEAP:DATA:NOROOT(3)
        DS8 __STARTUP_CONFIG_HEAP_SIZE

#else

        ;; Stack size default : Defined in *.icf (linker file). Can be modified inside EW.
        ;; Heap size default : Defined in *.icf (linker file). Can be modified inside EW.

        ;; Forward declaration of sections.
        SECTION CSTACK:DATA:NOROOT(3)

#endif


        SECTION .intvec:CODE:NOROOT(2)

        EXTERN  __iar_program_start
        EXTERN  SystemInit
        PUBLIC  __vector_table
        PUBLIC  __Vectors
        PUBLIC  __Vectors_End
        PUBLIC  __Vectors_Size

        DATA

__vector_table
        DCD     sfe(CSTACK)
        DCD     Reset_Handler
        DCD     NMI_Handler
        DCD     HardFault_Handler
        DCD     MemoryManagement_Handler
        DCD     BusFault_Handler
        DCD     UsageFault_Handler
        DCD     SecureFault_Handler
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     SVC_Handler
        DCD     DebugMon_Handler
        DCD     0                         ; Reserved
        DCD     PendSV_Handler
        DCD     SysTick_Handler

        ; External Interrupts
        DCD     FPU_IRQHandler
        DCD     CACHE_IRQHandler
        DCD     0                         ; Reserved
        DCD     SPU_IRQHandler
        DCD     0                         ; Reserved
        DCD     CLOCK_POWER_IRQHandler
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     SERIAL0_IRQHandler
        DCD     SERIAL1_IRQHandler
        DCD     SPIM4_IRQHandler
        DCD     SERIAL2_IRQHandler
        DCD     SERIAL3_IRQHandler
        DCD     GPIOTE0_IRQHandler
        DCD     SAADC_IRQHandler
        DCD     TIMER0_IRQHandler
        DCD     TIMER1_IRQHandler
        DCD     TIMER2_IRQHandler
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     RTC0_IRQHandler
        DCD     RTC1_IRQHandler
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     WDT0_IRQHandler
        DCD     WDT1_IRQHandler
        DCD     COMP_LPCOMP_IRQHandler
        DCD     EGU0_IRQHandler
        DCD     EGU1_IRQHandler
        DCD     EGU2_IRQHandler
        DCD     EGU3_IRQHandler
        DCD     EGU4_IRQHandler
        DCD     EGU5_IRQHandler
        DCD     PWM0_IRQHandler
        DCD     PWM1_IRQHandler
        DCD     PWM2_IRQHandler
        DCD     PWM3_IRQHandler
        DCD     0                         ; Reserved
        DCD     PDM0_IRQHandler
        DCD     0                         ; Reserved
        DCD     I2S0_IRQHandler
        DCD     0                         ; Reserved
        DCD     IPC_IRQHandler
        DCD     QSPI_IRQHandler
        DCD     0                         ; Reserved
        DCD     NFCT_IRQHandler
        DCD     0                         ; Reserved
        DCD     GPIOTE1_IRQHandler
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     QDEC0_IRQHandler
        DCD     QDEC1_IRQHandler
        DCD     0                         ; Reserved
        DCD     USBD_IRQHandler
        DCD     USBREGULATOR_IRQHandler
        DCD     0                         ; Reserved
        DCD     KMU_IRQHandler
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     CRYPTOCELL_IRQHandler
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved

__Vectors_End
__Vectors                           EQU   __vector_table
__Vectors_Size                      EQU   __Vectors_End - __Vectors


; Default handlers.
        THUMB

        PUBWEAK Reset_Handler
        SECTION .text:CODE:REORDER:NOROOT(2)
Reset_Handler

        LDR     R0, =SystemInit
        BLX     R0
        LDR     R0, =__iar_program_start
        BX      R0

        ; Dummy exception handlers


        PUBWEAK NMI_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
NMI_Handler
        B .

        PUBWEAK HardFault_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
HardFault_Handler
        B .

        PUBWEAK MemoryManagement_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
MemoryManagement_Handler
        B .

        PUBWEAK BusFault_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
BusFault_Handler
        B .

        PUBWEAK UsageFault_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
UsageFault_Handler
        B .

        PUBWEAK SecureFault_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
SecureFault_Handler
        B .

        PUBWEAK SVC_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
SVC_Handler
        B .

        PUBWEAK DebugMon_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
DebugMon_Handler
        B .

        PUBWEAK PendSV_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
PendSV_Handler
        B .

        PUBWEAK SysTick_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
SysTick_Handler
        B .


       ; Dummy interrupt handlers

        PUBWEAK  FPU_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
FPU_IRQHandler
        B .

        PUBWEAK  CACHE_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
CACHE_IRQHandler
        B .

        PUBWEAK  SPU_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
SPU_IRQHandler
        B .

        PUBWEAK  CLOCK_POWER_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
CLOCK_POWER_IRQHandler
        B .

        PUBWEAK  SERIAL0_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
SERIAL0_IRQHandler
        B .

        PUBWEAK  SERIAL1_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
SERIAL1_IRQHandler
        B .

        PUBWEAK  SPIM4_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
SPIM4_IRQHandler
        B .

        PUBWEAK  SERIAL2_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
SERIAL2_IRQHandler
        B .

        PUBWEAK  SERIAL3_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
SERIAL3_IRQHandler
        B .

        PUBWEAK  GPIOTE0_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
GPIOTE0_IRQHandler
        B .

        PUBWEAK  SAADC_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
SAADC_IRQHandler
        B .

        PUBWEAK  TIMER0_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
TIMER0_IRQHandler
        B .

        PUBWEAK  TIMER1_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
TIMER1_IRQHandler
        B .

        PUBWEAK  TIMER2_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
TIMER2_IRQHandler
        B .

        PUBWEAK  RTC0_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
RTC0_IRQHandler
        B .

        PUBWEAK  RTC1_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
RTC1_IRQHandler
        B .

        PUBWEAK  WDT0_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
WDT0_IRQHandler
        B .

        PUBWEAK  WDT1_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
WDT1_IRQHandler
        B .

        PUBWEAK  COMP_LPCOMP_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
COMP_LPCOMP_IRQHandler
        B .

        PUBWEAK  EGU0_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
EGU0_IRQHandler
        B .

        PUBWEAK  EGU1_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
EGU1_IRQHandler
        B .

        PUBWEAK  EGU2_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
EGU2_IRQHandler
        B .

        PUBWEAK  EGU3_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
EGU3_IRQHandler
        B .

        PUBWEAK  EGU4_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
EGU4_IRQHandler
        B .

        PUBWEAK  EGU5_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
EGU5_IRQHandler
        B .

        PUBWEAK  PWM0_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
PWM0_IRQHandler
        B .

        PUBWEAK  PWM1_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
PWM1_IRQHandler
        B .

        PUBWEAK  PWM2_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
PWM2_IRQHandler
        B .

        PUBWEAK  PWM3_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
PWM3_IRQHandler
        B .

        PUBWEAK  PDM0_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
PDM0_IRQHandler
        B .

        PUBWEAK  I2S0_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
I2S0_IRQHandler
        B .

        PUBWEAK  IPC_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
IPC_IRQHandler
        B .

        PUBWEAK  QSPI_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
QSPI_IRQHandler
        B .

        PUBWEAK  NFCT_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
NFCT_IRQHandler
        B .

        PUBWEAK  GPIOTE1_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
GPIOTE1_IRQHandler
        B .

        PUBWEAK  QDEC0_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
QDEC0_IRQHandler
        B .

        PUBWEAK  QDEC1_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
QDEC1_IRQHandler
        B .

        PUBWEAK  USBD_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
USBD_IRQHandler
        B .

        PUBWEAK  USBREGULATOR_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
USBREGULATOR_IRQHandler
        B .

        PUBWEAK  KMU_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
KMU_IRQHandler
        B .

        PUBWEAK  CRYPTOCELL_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
CRYPTOCELL_IRQHandler
        B .

        END
