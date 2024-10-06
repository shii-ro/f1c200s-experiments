cmake_minimum_required(VERSION 3.12)

# Include the toolchain file
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/arm-gcc-toolchain.cmake)

# Set the project name and the C standard
project(f1c200s-hello-world C)

# Add the executable
add_executable(${PROJECT_NAME} main.c)

# Ensure path to arm-none-eabi-size
set(TOOLCHAIN_PATH "C:/ARM-GNU-Toolchain/bin")
set(CMAKE_SIZE "${TOOLCHAIN_PATH}/arm-none-eabi-size")

# Custom command to create a binary file from the ELF file
add_custom_command(
    OUTPUT "${CMAKE_BINARY_DIR}/${PROJECT_NAME}.bin"
    COMMAND ${CMAKE_OBJCOPY} -O binary "${CMAKE_BINARY_DIR}/${PROJECT_NAME}.elf" "${CMAKE_BINARY_DIR}/${PROJECT_NAME}.bin"
    DEPENDS "${CMAKE_BINARY_DIR}/${PROJECT_NAME}.elf"
    COMMENT "Generating binary file from ELF"
)

# Custom target to build the binary
add_custom_target(
    bin ALL DEPENDS "${CMAKE_BINARY_DIR}/${PROJECT_NAME}.bin"
)

add_subdirectory(${CMAKE_SOURCE_DIR}/f1c200s)
target_link_libraries(f1c200s-hello-world PRIVATE f1c200s)
# Ensure the binary is built after the ELF executable
add_dependencies(bin ${PROJECT_NAME})