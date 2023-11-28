cmake_minimum_required(VERSION 3.10)

project(2-2 VERSION 1.0)

# Specify the C standard
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED True)

add_executable(task1 task1.c)
add_executable(task2 task2.c)
add_executable(task3 task3.c)
add_executable(task4 task4.c)
add_executable(task5 task5.c utils.c)
add_executable(task6 task6.c utils.c)
