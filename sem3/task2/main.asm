
section .text
global _start

%include "lib.inc"
_start:
    mov  rdi, 0x123456789
    call print_hex
    call exit