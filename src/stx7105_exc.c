#include "stx7105.h"

#define __WEAK     __attribute__((weak))
#define __IRQ      __attribute__((interrupt_handler))
#define __WEAK_IRQ __attribute__((weak, interrupt_handler))

typedef enum {
    EXP_TYPE_TRAP = 0x160,
} expevt_type_t;

typedef enum {
    INT_TYPE_TMU_TNUI0  = 0x400,
    INT_TYPE_TMU_TNUI1  = 0x420,
    INT_TYPE_TMU_TNUI2  = 0x440,
    INT_TYPE_TMU_TICPI2 = 0x460,
} intevt_type_t;

typedef enum {
    TRA_TYPE_SYSCALL = 34,
} tra_type_t;


__WEAK int tuni0_handler(void) {
    /* Does nothing */
    return 0;
}

__WEAK int syscall_handler(uint32_t p1, uint32_t p2, uint32_t p3, uint32_t p4) {
    return 0;
}

__WEAK int trap_handler(uint32_t p1, uint32_t p2, uint32_t p3, uint32_t p4) {
    tra_type_t tra = CSR->TRA;

    switch (tra) {
        case TRA_TYPE_SYSCALL:
            return syscall_handler(p1, p2, p3, p4);
            break;
        default:
            break;
    }

    return 0;
}

__WEAK_IRQ int general_exc_handler(uint32_t p1, uint32_t p2, uint32_t p3, uint32_t p4) {
    expevt_type_t expevt = CSR->EXPEVT;
    switch (expevt) {
        case EXP_TYPE_TRAP:
            return trap_handler(p1, p2, p3, p4);
            break;
        default:
            break;
    }

    return 0;
}

__WEAK_IRQ int general_int_handler(void) {
    intevt_type_t intevt = CSR->INTEVT;
    switch (intevt) {
        case INT_TYPE_TMU_TNUI0:
            return tuni0_handler();
            break;
        default:
            break;
    }
    return 0;
}