cmake_minimum_required(VERSION 3.16)
project(krnl C ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "-m32 -ffreestanding -nostdlib -fno-pic -fno-omit-frame-pointer -fno-pie")
set(CMAKE_ASM_NASM_OBJECT_FORMAT elf32)
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_POSITION_INDEPENDENT_CODE OFF)

enable_language(ASM_NASM)

# Define objcopy explicitly if it's not set
find_program(CMAKE_OBJCOPY objcopy REQUIRED)

add_subdirectory(kernel)

add_executable(kernel.elf ${BOOT_SRC} ${KERNEL_SRC} ${DRIVER_SRC})
set_target_properties(kernel.elf PROPERTIES LINKER_LANGUAGE C)


target_include_directories(kernel.elf PRIVATE kernel/)

set_target_properties(kernel.elf PROPERTIES
    LINK_FLAGS "-T ${CMAKE_SOURCE_DIR}/linker.ld -nostdlib "
)


add_custom_command(
    TARGET kernel.elf POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O binary kernel.elf kernel.bin
    COMMAND echo "[+] Converting to an ELF binary\n\n\n"
)