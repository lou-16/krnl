cmake_minimum_required(VERSION 3.16)
project(krnl C ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "-m32 -ffreestanding -nostdlib -fno-pic")
set(CMAKE_ASM_NASM_OBJECT_FORMAT elf32)

set(CMAKE_POSITION_INDEPENDENT_CODE OFF)

enable_language(ASM_NASM)

# Define objcopy explicitly if it's not set
find_program(CMAKE_OBJCOPY objcopy REQUIRED)

add_subdirectory(boot)
add_subdirectory(kernel)
add_subdirectory(drivers)

add_executable(kernel.elf ${BOOT_SRC} ${KERNEL_SRC} ${DRIVER_SRC})
set_target_properties(kernel.elf PROPERTIES LINKER_LANGUAGE C)

set_target_properties(kernel.elf PROPERTIES
    LINK_FLAGS "-T ${CMAKE_SOURCE_DIR}/linker.ld -nostdlib"
)

add_custom_command(
    TARGET kernel.elf POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O binary kernel.elf kernel.bin
    COMMAND echo "[+] Converting to an ELF binary\n\n\n"
)