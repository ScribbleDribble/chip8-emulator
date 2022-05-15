 cmake_minimum_required(VERSION 3.10)
 
project(chip8_proj)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${CMAKE_BINARY_DIR})

set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -Wextra")
set(SOURCE_FILES display.h decode.h specifications.h main.c display.c decode.c helpers.c)

add_executable(chip8 ${SOURCE_FILES})
target_link_libraries(chip8 ${SDL2_LIBRARIES})    
