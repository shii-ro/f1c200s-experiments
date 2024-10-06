cmake_minimum_required(VERSION 3.12)

# Project name
project(F1C200S C)

# Create a library for the F1C200S
add_library(f1c200s STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/uart/uart.c
    ${CMAKE_CURRENT_SOURCE_DIR}/gpio/gpio.c
)

# Add include directories
target_include_directories(f1c200s PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/uart
    ${CMAKE_CURRENT_SOURCE_DIR}/gpio
)