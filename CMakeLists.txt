 cmake_minimum_required(VERSION 3.10)
 
project(chip8_proj)
# Link runTests with what we want to test and the GTest and pthread library
add_executable(chip8 main.c vm.c display.c decode.c)
