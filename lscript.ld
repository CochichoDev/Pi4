SECTIONS
{
.text.boot : {
    *(.text.boot)
}
.text : {
    *(.text)
    *(*.text)
}
. = ALIGN(0x8);
.bss (NOLOAD) : {
    __bss_start = .;
    *(.bss)
    *(*.bss)
    . = ALIGN(0x8);
    __bss_end = .;
}
. = ALIGN(0x8);
.data : {
    *(.data)
    *(*.data)
}
. = ALIGN(0x8);
.stack (NOLOAD) : {
    __stack_start = .;
    . += 0x100;
    __stack_end = .;
}
}
