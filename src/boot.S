.section ".text.boot", "x"
.globl _start
_start:
    mrs x0, CurrentEL
    and x0, x0, #0xF
    lsr x0, x0, #2
    cmp x0, #0x3
    bne proc_hang

    ldr x0, =_vtable
    msr VBAR_EL3, x0

    ldr x0, =__bss_start
    ldr x1, =__bss_end
    cmp x1, x0
    beq bss_end
bss_loop:
    str xzr, [x0], #64
    cmp x0, x1
    bne bss_loop
    
bss_end:
    ldr x0, =__stack_end
    mov sp, x0

    bl main

proc_hang:
    /* wait for event */
    wfe
    b proc_hang

