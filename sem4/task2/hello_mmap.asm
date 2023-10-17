; hello_mmap.asm
%define O_RDONLY 0 
%define PROT_READ 0x1
%define MAP_PRIVATE 0x2

%define SYS_WRITE 1
%define SYS_OPEN 2
%define SYS_CLOSE 3
%define SYS_FSTAT 5
%define SYS_MMAP 9
%define SYS_MUNMAP 11

%define FD_STDOUT 1



section .data
    ; This is the file name. You are free to change it.
    fname: db 'hello.txt', 0

section .text
global _start

; use exit system call to shut down correctly
exit:
    mov  rax, 60
    xor  rdi, rdi
    syscall

; These functions are used to print a null terminated string
; rdi holds a string pointer
print_string:
    push rdi
    call string_length
    pop  rsi
    mov  rdx, rax 
    mov  rax, SYS_WRITE
    mov  rdi, FD_STDOUT
    syscall
    ret

string_length:
    xor  rax, rax
.loop:
    cmp  byte [rdi+rax], 0
    je   .end 
    inc  rax
    jmp .loop 
.end:
    ret

; This function is used to print a substring with given length
; rdi holds a string pointer
; rsi holds a substring length
print_substring:
    mov  rdx, rsi 
    mov  rsi, rdi
    mov  rax, SYS_WRITE
    mov  rdi, FD_STDOUT
    syscall
    ret

_start:
	push r12	;fd
	push r13	;buf
	push r14	;addr

    ; Вызовите open и откройте fname в режиме read only.
    mov  rax, SYS_OPEN
    mov  rdi, fname
    mov  rsi, O_RDONLY
    mov  rdx, 0
    syscall

	mov r12, rax			; Сохраняем файловый дескриптор

	sub rsp, 144			; Выделяем место на стеке согласно ABI
	mov r13, rsp			; указатель на буфер

    ; Вызываем fstat
	mov rdi, r12			; файловый дескриптор
	mov rsi, r13			; указатель на буфер
    mov rax, SYS_FSTAT		; номер системного вызова FSTAT
    syscall

    ; Отображаем файл в память
	xor rdi, rdi                 ; пусть OS выберет адрес
	mov rsi, [r13 + 48]		     ; stat + offset
    mov rdx, PROT_READ           ; права доступа
    mov r10, MAP_PRIVATE         ; приватное отображение
    xor r9, r9                   ; смещение на 0
	mov r8, r12			         ; дескриптор файла
    mov rax, SYS_MMAP            ; номер системного вызова mmap
	syscall

	mov r14, rax			     ; Сохраняем адрес, который вернула mmap

    ; Проверим на ошибки
    cmp rax, -1
    je exit

    ; Используем функцию print_substring
	mov rdi, r14			; адрес
	mov rsi, [r13 + 48]		; длина страницы
	call print_substring

    ; Вызываем munmap для освобождения отображенной области памяти
	mov rdi, r14			; адрес
	mov rsi, [r13 + 48]		; длина страницы
	mov rax, SYS_MUNMAP		; системный вызов munmap
	syscall

	mov rdi, r12			; дескриптор файла
	mov rax, SYS_CLOSE		; закрываем :)
	syscall

	add rsp, 144            ; восстанавливаем стэк
	pop r14
	pop r13
	pop r12

    call exit
