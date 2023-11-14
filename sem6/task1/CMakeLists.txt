cmake_minimum_required(VERSION 3.10)

# Set the project name and version
project(HeapProject VERSION 1.0)

# Specify the C standard
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED True)

# Add executable
add_executable(HeapProgram heap-0.c)
