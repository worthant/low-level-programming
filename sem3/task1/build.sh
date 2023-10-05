#!/bin/bash

# Preprocess the program
nasm -e declare_str.asm

# Check the exit status to see if the commands were successful
if [ $? -eq 0 ]; then
    echo "Preprocess successful."
else
    echo "Preprocess failed."
fi
