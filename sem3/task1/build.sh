#!/bin/bash

# Assemble the program
nasm -f elf64 -o declare_str.o declare_str.asm

# Link the object file to create the executable
ld -o declare_str declare_str.o

# Check the exit status to see if the commands were successful
if [ $? -eq 0 ]; then
    echo "Build successful."
else
    echo "Build failed."
fi
