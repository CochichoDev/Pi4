.section .vectors, "ax"

.globl _vtable
.globl rst_addr

_vtable:
    .set VBAR, _vtable
    .org VBAR
    b _sync_exception

    .org (VBAR+0x80)
    b _irq_exception

    .org (VBAR+0x100)
    b _fiq_exception

    .org (VBAR+0x180)
    b _serror_exception

    .org (VBAR+0x200)
    b _sync_exception

    .org (VBAR+0x280)
    b _irq_exception

    .org (VBAR+0x300)
    b _fiq_exception

    .org (VBAR+0x380)
    b _serror_exception

    .org (VBAR+0x400)
    b _sync_exception

    .org (VBAR+0x480)
    b _irq_exception

    .org (VBAR+0x500)
    b _fiq_exception

    .org (VBAR+0x580)
    b _serror_exception

    .org (VBAR+0x600)
    b _sync_exception

    .org (VBAR+0x680)
    b _irq_exception

    .org (VBAR+0x700)
    b _fiq_exception

    .org (VBAR+0x780)
    b _serror_exception

.align 0x8
rst_addr:
    .quad   proc_hang
    .quad   proc_hang
    .quad   proc_hang
    .quad   proc_hang

