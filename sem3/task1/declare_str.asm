; Задание 1 Напишите многострочный макрос, чтобы он выделял в памяти строку из своих аргументов, 
; разделенную запятыми. Например при передаче аргументов hello, another и world в результате 
; в памяти была выделена строка hello, another, world.

%macro declare_str 1-*  ; define macro, take at least 1 arg (can be more)
    %rep %0             ; repeat following block (number of args passed) times
        db %1           ; declare byte (db) - init it with first arg
        db ", "         ; declare another byte - init it with comma and whitespace (to separate strings)
    %rotate 1           ; rotate args by 1 pos (3 -> 2, 2 -> 1, ...)
    %endrep             ; end %rep block
    db 0                ; declare byte - init it with 0 (null-terminator)
%endmacro               ; end of the macro

section .data
    str: declare_str "hello", "another", "world"