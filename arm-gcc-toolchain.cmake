# arm-gcc-toolchain.cmake
# Specify the cross-compilation toolchain

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)

set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")

# Path to your ARM GCC toolchain
set(TOOLCHAIN_PREFIX                arm-none-eabi-)
set(TOOLCHAIN_PATH "C:/ARM-GNU-Toolchain/bin")

set(CMAKE_C_COMPILER                ${TOOLCHAIN_PREFIX}gcc)
set(CMAKE_ASM_COMPILER              ${CMAKE_C_COMPILER})
set(CMAKE_CXX_COMPILER              ${TOOLCHAIN_PREFIX}g++)
set(CMAKE_LINKER                    ${TOOLCHAIN_PREFIX}g++)
set(CMAKE_OBJCOPY                   ${TOOLCHAIN_PREFIX}objcopy)
set(CMAKE_SIZE                      ${TOOLCHAIN_PREFIX}size)

set(CMAKE_EXECUTABLE_SUFFIX_ASM     ".elf")
set(CMAKE_EXECUTABLE_SUFFIX_C       ".elf")
set(CMAKE_EXECUTABLE_SUFFIX_CXX     ".elf")

# Specify the compiler
set(CMAKE_C_COMPILER ${TOOLCHAIN_PATH}/arm-none-eabi-gcc.exe)
set(CMAKE_CXX_COMPILER ${TOOLCHAIN_PATH}/arm-none-eabi-g++.exe)
set(CMAKE_ASM_COMPILER ${TOOLCHAIN_PATH}/arm-none-eabi-as.exe)

# Ensure path to arm-none-eabi-size
set(CMAKE_SIZE "${TOOLCHAIN_PATH}/arm-gnu-eabi-size")

# Compiler flags
set(CMAKE_C_FLAGS "-mcpu=arm926ej-s -O0 -ffreestanding -nostdlib")

# Path to the linker script
set(LINKER_SCRIPT_PATH ${CMAKE_SOURCE_DIR}/F1C200S_DRAM.ld)

# Pass the linker script to the compiler
set(CMAKE_EXE_LINKER_FLAGS "-T${LINKER_SCRIPT_PATH} -nostartfiles -Wl,-Map=output.map")
