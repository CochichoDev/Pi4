.section ".text"
.globl wait
.globl get_cur_sp
.globl get_base_sp
.globl get_stack_size

wait:
    sub x0, x0, #1
    cbnz x0, wait
    ret

get_cur_sp:
    mov x0, sp
    ret

get_base_sp:
    ldr x0, =__stack_start
    ret

get_stack_size:
    bl get_cur_sp
    mov x1, x0
    bl get_base_sp
    sub x0, x1, x0
    ret

