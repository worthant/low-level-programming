nasm -felf64 -o hello_mmap.o hello_mmap.asm
ld -o hello_mmap hello_mmap.o
./hello_mmap