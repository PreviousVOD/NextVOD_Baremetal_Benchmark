/*
 * This section is read by bootloader,
 * then the application will be copied according to the contents.
 * !!DO NOT REMOVE!!
 * See SPL project README for details.
 */

    .section .text.vtors, "ax"
_vtors:
    .long _eidata
    .long _start

/*
 * Startup code (CRT0)
 */
    .section .text.init, "ax"
    .global _start

_start:
    mov.l _stack_k, sp /* Setup R15(SP) */

_copy_data:
    mov.l _sidata_k, r0
    mov.l _sdata_k, r1
    mov.l _edata_k, r2

_loop_copy_data:
    mov.l @r0+, r3 /* Load a word to r3 from [sidata], with post-increment of 4 */
    mov.l r3, @r1  /* Store the word in r3 to [sdata] */
    add #4, r1     /* Increment sdata pointer */
    cmp/gt r1, r2  /* r2 greater or equal than r1? */
    bt _loop_copy_data

_zero_bss:
    mov.l _edata_k, r0
    mov.l _end_k, r1
    mov #0, r2

_loop_zero_bss:
    mov.l r2, @r0
    add #4, r0
    cmp/gt r0, r1
    bt _loop_zero_bss

_setup_fpu:
    mov.l _set_fpscr_k, r1
    jsr @r1
    mov #0, r4
    lds r3, fpscr

_setup_irq:
    mov.l _exc_base_k, r0
    ldc r0, vbr

    stc sr, r0 /* Store SR into R0 */
    mov.l _exc_imask_k, r1
    and r1, r0
    ldc r0, sr

    .align 2
_main_entry:
    mov.l _main_k, r0
    jsr @r0
    or r0, r0

    mov.l _exit_loop_k, r0
_exit_loop:
    sleep
    jmp @r0
    nop

    .balign 4
/* libc FPU routine */
_set_fpscr_k:
    .long ___set_fpscr

/* C library consts */
_stack_k:
    .long _stack
_sidata_k:
    .long _sidata
_sdata_k:
    .long _sdata
_edata_k:
    .long _edata
_end_k:
    .long _end

/* Function pointers */
_main_k:
    .long _main /* Same address as main */
_exit_loop_k:
    .long _exit_loop
_exc_base_k:
    .long _exc_base
_exc_imask_k:
    .long 0xEFFFFF0F /* Clear IMASK (SR[7:4]) to 0 and BL bit, enable all exception levels */

/*
 * Exception handlers
 * These handlers are placed at VBR related addresses
 */

    .section .text.exc, "ax"
    .align 4
_exc_base:
    .org 0x100, 0x00
_exc_grnl_vector:
    mov.l _exc_grnl_entry_k, r0
    jmp @r0
    nop

    .align 4
_exc_grnl_entry_k:
    .long _general_exc_handler

_int_base:
    .org 0x600, 0x00
_int_grnl_vector:
    mov.l _int_grnl_entry_k, r0
    jmp @r0
    nop

    .align 4
_int_grnl_entry_k:
    .long _general_int_handler