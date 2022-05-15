project(tests)
cmake_minimum_required(VERSION 3.10)
# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_library(decode ../decode.c)

add_executable(decode_tests ../decode.c decode_tests.cpp ../display.c ../display.h ../helpers.c)

target_link_libraries(decode_tests decode ${GTEST_LIBRARIES} pthread)
