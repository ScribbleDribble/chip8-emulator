 cmake_minimum_required(VERSION 3.10)
 
project(chip8_proj)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(SDL2 REQUIRED)
include_directories(chip8 ${SDL2_INCLUDE_DIRS})
include_directories (${CMAKE_BINARY_DIR})


set(SOURCE_FILES display.h decode.h main.c display.c decode.c )

add_executable(chip8 ${SOURCE_FILES})
target_link_libraries(chip8 ${SDL2_LIBRARIES})    
