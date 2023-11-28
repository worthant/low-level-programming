cmake_minimum_required(VERSION 3.10)

add_executable(task3 task3.c)
target_compile_options(task3 PRIVATE -fno-stack-protector -z execstack -no-pie -g)
