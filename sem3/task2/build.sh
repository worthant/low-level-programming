#!/bin/bash

# Компилируем lib.asm в объектный файл lib.o
nasm -f elf64 -o lib.o lib.asm

# Компилируем main.asm в объектный файл main.o
nasm -f elf64 -o main.o main.asm

# Линкуем lib.o и main.o в исполняемый файл program
ld -o program lib.o main.o

# Проверяем, успешно ли прошла компиляция и линковка
if [ $? -eq 0 ]; then
    echo "Сборка успешно завершена."
else
    echo "Ошибка при сборке."
fi
