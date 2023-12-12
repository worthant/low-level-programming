cmake_minimum_required(VERSION 3.10)

add_executable(task2 task2.c)

# Setting compiler options
target_compile_options(task2 PRIVATE -fno-stack-protector -z execstack -no-pie -g)
