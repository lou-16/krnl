cmake_minimum_required(VERSION 3.16)
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)
project(krnl C ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "--target=i686-elf -ffreestanding -nostdlib -fno-pic -fno-omit-frame-pointer -fno-pie")
set(CMAKE_ASM_NASM_OBJECT_FORMAT elf32)
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_POSITION_INDEPENDENT_CODE OFF)

enable_language(ASM_NASM)

# Apple Specific Build.
if(APPLE)
    message(STATUS "Configuring macOS Host")
    find_program(LLD ld.lld REQUIRED)
    set(CMAKE_LINKER ${LLD})
    set(CMAKE_OSX_ARCHITECTURES "")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fno-integrated-as")
endif()
if(NOT APPLE)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -m32")
endif()

# Define objcopy explicitly if it's not set
if(NOT APPLE)
#find_program(CMAKE_OBJCOPY objcopy REQUIRED)
endif()

add_subdirectory(kernel)

add_executable(kernel.elf ${BOOT_SRC} ${KERNEL_SRC} ${DRIVER_SRC})
set_target_properties(kernel.elf PROPERTIES LINKER_LANGUAGE C)


target_include_directories(kernel.elf PRIVATE kernel/)

set_target_properties(kernel.elf PROPERTIES
    LINK_FLAGS "-T ${CMAKE_SOURCE_DIR}/linker.ld -nostdlib "
)

if(NOT APPLE)
add_custom_command(
    TARGET kernel.elf POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O binary kernel.elf kernel.bin
    COMMAND echo "[+] Converting to an ELF binary\n\n\n"
)
endif()