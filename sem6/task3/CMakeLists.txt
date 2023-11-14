cmake_minimum_required(VERSION 3.10)

# Set the project name and version
project(VectorProject VERSION 1.0)

# Specify the C standard
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED True)

# Add executable
add_executable(VectorProgram main.c vector.c)
