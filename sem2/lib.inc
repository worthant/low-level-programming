; print_string.asm 
section .data
message: db  'asdkbasdka', 0

section .text
global _start

exit:
    mov  rax, 60       
    syscall

string_length:
    xor rax, rax
    .count:
      cmp byte [rdi+rax], 0
      je .end
      inc rax
      jmp .count
    .end:
      ret

print_string:
  call string_length
  mov  rdx, rax
  mov  rsi, rdi
  mov  rax, 1
  mov  rdi, 1
  syscall
  ret

parse_uint:
  xor rax, rax
  mov rcx, 0
  mov rdx, 0

.loop:
  mov dl, byte[rdi + rcx] ; rdi=50
  sub dl, '0' ; dl = 2 
  cmp dl, 0
  js .out
  cmp dl, 10
  jns .out
  imul rax, 10
  add rax, rdx
  inc rcx
  jmp .loop
  ret

.out:
  mov rdx, rcx
  ret
