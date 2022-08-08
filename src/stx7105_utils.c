#include "stx7105.h"

/* Private */
#include "stx7105_utils.h"

volatile uint8_t s_tmu_flag = 0U;

void init_led(PIO_TypeDef *gpiox, uint8_t pin, uint8_t init_value) {
    gpiox->CLR_PC0 = 1 << pin;
    gpiox->SET_PC1 = 1 << pin;
    gpiox->CLR_PC2 = 1 << pin;

    set_led(gpiox, pin, init_value);
}

void set_led(PIO_TypeDef *gpiox, uint8_t pin, uint8_t val) {
    if (val) {
        gpiox->SET_POUT = (1 << pin);

    } else {
        gpiox->CLR_POUT = (1 << pin);
    }
}

void delay_ms(uint32_t msec) {
    /* Initialize TMU and count to zero */
    /* TMU clock is from Peripheral clock, approx. 66MHz */
    /* Prescale to 66kHz for convenience (TMUs can only divide by max. 1024) */

    uint32_t reload_value = msec * 66 - 1;

    TMU->TSTR &= ~TMU_TSTR_STR0_Msk;       /* Stop counter */
    TMU->TCR0  = 0x04U | TMU_TCR_UNIE_Msk; /* 1024 prescale, enable interrupt */
    TMU->TCNT0 = reload_value;             /* 66kHz */
    TMU->TCOR0 = reload_value;             /* Reload register */
    TMU->TSTR |= TMU_TSTR_STR0_Msk;        /* Start counter */

    INTC->IPRA &= ~INTC_IPRA_IPR_TMU0_Msk;
    INTC->IPRA |= (1U << INTC_IPRA_IPR_TMU0_Pos); /* Interrupt priority 1 */

    /* Wait until underflow occurs */
    while(s_tmu_flag != 1) {
        asm("sleep");
    }

    s_tmu_flag = 0U;

    TMU->TSTR &= ~TMU_TSTR_STR0_Msk; /* Stop counter */
}

int tuni0_handler(void) {
    s_tmu_flag = 1U;
    TMU->TCR0 &= ~(TMU_TCR_UNF_Msk);

    return 0;
}