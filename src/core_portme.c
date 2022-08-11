/*
Copyright 2018 Embedded Microprocessor Benchmark Consortium (EEMBC)

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

Original Author: Shay Gal-on
*/

#include <stdio.h>
#include <stdlib.h>

#include "coremark.h"
#include "stx7105.h"

#define SYSTEM_CONFIG34 (0xFE001188U) /* PIO4 */
#define SYSTEM_CONFIG7  (0xFE00111CU) /* RXSEL */
#define CONSOLE_ASC     ASC2

#if VALIDATION_RUN
volatile ee_s32 seed1_volatile = 0x3415;
volatile ee_s32 seed2_volatile = 0x3415;
volatile ee_s32 seed3_volatile = 0x66;
#endif
#if PERFORMANCE_RUN
volatile ee_s32 seed1_volatile = 0x0;
volatile ee_s32 seed2_volatile = 0x0;
volatile ee_s32 seed3_volatile = 0x66;
#endif
#if PROFILE_RUN
volatile ee_s32 seed1_volatile = 0x8;
volatile ee_s32 seed2_volatile = 0x8;
volatile ee_s32 seed3_volatile = 0x8;
#endif
volatile ee_s32 seed4_volatile = ITERATIONS;
volatile ee_s32 seed5_volatile = 0;
/* Porting : Timing functions
        How to capture time and convert to seconds must be ported to whatever is
   supported by the platform. e.g. Read value from on board RTC, read value from
   cpu clock cycles performance counter etc. Sample implementation for standard
   time.h and windows.h definitions included.
*/

#define EE_TICKS_PER_SEC (100000000.0 / 1024.0)

/** Define Host specific (POSIX), or target specific global time variables. */
static uint32_t start_time_val, stop_time_val;

/* Function : start_time
        This function will be called right before starting the timed portion of
   the benchmark.

        Implementation may be capturing a system timer (as implemented in the
   example code) or zeroing some system parameters - e.g. setting the cpu clocks
   cycles to 0.
*/
void start_time(void) {
    uint32_t reload_value = 0xFFFFFFF;

    start_time_val = reload_value;

    TMU->TSTR &= ~TMU_TSTR_STR0_Msk; /* Stop counter */
    TMU->TCR0  = 0x04U;              /* 1024 prescale */
    TMU->TCNT0 = reload_value;       /* 100kHz */
    TMU->TCOR0 = reload_value;       /* Reload register */
    TMU->TSTR |= TMU_TSTR_STR0_Msk;  /* Start counter */
}
/* Function : stop_time
        This function will be called right after ending the timed portion of the
   benchmark.

        Implementation may be capturing a system timer (as implemented in the
   example code) or other system parameters - e.g. reading the current value of
   cpu cycles counter.
*/
void stop_time(void) {
    TMU->TSTR &= ~TMU_TSTR_STR0_Msk; /* Stop counter */
    stop_time_val = TMU->TCNT0;
}
/* Function : get_time
        Return an abstract "ticks" number that signifies time on the system.

        Actual value returned may be cpu cycles, milliseconds or any other
   value, as long as it can be converted to seconds by <time_in_secs>. This
   methodology is taken to accommodate any hardware or simulated platform. The
   sample implementation returns millisecs by default, and the resolution is
   controlled by <TIMER_RES_DIVIDER>
*/
CORE_TICKS get_time(void) {
    return start_time_val - stop_time_val;
}
/* Function : time_in_secs
        Convert the value returned by get_time to seconds.

        The <secs_ret> type is used to accommodate systems with no support for
   floating point. Default implementation implemented by the EE_TICKS_PER_SEC
   macro above.
*/
secs_ret time_in_secs(CORE_TICKS ticks) {
    secs_ret retval = ((secs_ret)ticks) / (secs_ret)EE_TICKS_PER_SEC;
    return retval;
}

ee_u32 default_num_contexts = 1;

static void uart_init(void) {
    PIO4->CLR_PC0 = 1U; /* PC = 110, AFOUT, PP */
    PIO4->SET_PC1 = 1U;
    PIO4->SET_PC2 = 1U;

    *(uint32_t *)SYSTEM_CONFIG34 = 0x00000100UL;    /* BIT[8,0] = 10, AF 3 */
    *(uint32_t *)SYSTEM_CONFIG7 &= ~(0x00000006UL); /* BIT[2:1], UART2 RX SEL */

    CONSOLE_ASC->CTRL     = 0x1509UL; /* 8N1, RX enable, FIFO enable, Baud mode 1 */
    CONSOLE_ASC->BAUDRATE = 0x04B8UL; /* 115200 in baud mode 1, assuming Fcomm=100MHz */
    CONSOLE_ASC->TX_RST   = 0x01UL;   /* Reset TX FIFO, any value OK */
    CONSOLE_ASC->RX_RST   = 0x01UL;   /* Reset RX FIFO, any value OK */
    CONSOLE_ASC->CTRL     = 0x1589UL; /* 8N1, RX enable, FIFO enable, Baud mode 1 */
}

/* Function : portable_init
        Target specific initialization code
        Test for some common mistakes.
*/
void portable_init(core_portable *p, int *argc, char *argv[]) {
    (void)argc;  // prevent unused warning
    (void)argv;  // prevent unused warning

    uart_init();

    if (sizeof(ee_ptr_int) != sizeof(ee_u8 *)) {
        ee_printf(
            "ERROR! Please define ee_ptr_int to a type that holds a "
            "pointer!\r\n");
    }
    if (sizeof(ee_u32) != 4) {
        ee_printf("ERROR! Please define ee_u32 to a 32b unsigned type!\r\n");
    }
    p->portable_id = 1;
}
/* Function : portable_fini
        Target specific final code
*/
void portable_fini(core_portable *p) {
    p->portable_id = 0;
}
