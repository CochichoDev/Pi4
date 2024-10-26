.section ".text.boot"
.globl _start
_start:
    mrs x0, MPIDR_EL1
    and x0, x0, #0x3
    cbnz x0, proc_hang
    b master

master: /* entry point of the primary core */
    /* only core 0 starts here */

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

    ldr x0, =0xfe2000e4
    ldr w1, [x0]
    ldr w2, =0xfffffcff
    and w1, w1, w2
    //orr w1, w1, #0x200
    str w1, [x0]
    
    ldr x0, =0xfe200000
    ldr w1, [x0]
    ldr w2, =0xffff8fff
    and w1, w1, w2
    orr w1, w1, #0x1000
    str w1, [x0]

    bl main

proc_hang:
    /* wait for event */
    wfe
    b proc_hang


loop:
    ldr x0, =0xfe20001c
    orr w1, wzr, #0x10
    str w1, [x0]

    ldr x0, =5000000
    bl wait

    ldr x0, =0xfe200028
    orr w1, wzr, #0x10
    str w1, [x0]

    ldr x0, =5000000
    bl wait

    b loop

.section ".text.wait"
.globl wait
wait:
    sub x0, x0, #1
    cbnz x0, wait
    ret

