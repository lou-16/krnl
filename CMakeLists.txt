cmake_minimum_required(VERSION 3.16)
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)
project(krnl C ASM)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_FLAGS "-ffreestanding -nostdlib -fno-pic -fno-omit-frame-pointer -fno-pie -g -O0 -mno-red-zone -mcmodel=kernel -nostartfiles -nodefaultlibs -fno-stack-protector")
set(CMAKE_ASM_NASM_OBJECT_FORMAT elf64)
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_POSITION_INDEPENDENT_CODE OFF)

enable_language(ASM_NASM)

# Apple Specific Build.
if(APPLE)
    message(STATUS "Configuring macOS Host")
    find_program(LLD ld.lld REQUIRED)
    set(CMAKE_LINKER ${LLD})
    set(CMAKE_OSX_ARCHITECTURES "")
    # TODO: Modify this for OSX
    #set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fno-integrated-as --target=i686-elf")
endif()

# Define objcopy explicitly if it's not set
if(NOT APPLE)
#find_program(CMAKE_OBJCOPY objcopy REQUIRED)
endif()

add_executable(kernel.elf)
set_target_properties(kernel.elf PROPERTIES LINKER_LANGUAGE C
    LINK_FLAGS "-T ${CMAKE_SOURCE_DIR}/linker.ld -nostdlib -nostartfiles -nodefaultlibs -no-pie"
)

add_library(kernel_objs OBJECT)
add_subdirectory(kernel)

target_include_directories(kernel.elf PRIVATE kernel/)

target_link_libraries(kernel.elf PRIVATE kernel_objs)

if(NOT APPLE)
add_custom_command(
    TARGET kernel.elf POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O binary kernel.elf kernel.bin
    COMMAND echo "[+] Converting to an ELF binary\n\n\n"
)
endif()