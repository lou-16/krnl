add_subdirectory(boot)
add_subdirectory(drivers)
add_subdirectory(sys)
add_subdirectory(arch)

set(KERNEL_SRC ${KERNEL_SRC}
    ${CMAKE_CURRENT_SOURCE_DIR}/kernel.c
    ${CMAKE_CURRENT_SOURCE_DIR}/serial.c
    ${CMAKE_CURRENT_SOURCE_DIR}/kprintf.c
    PARENT_SCOPE
)
set(BOOT_SRC ${BOOT_SRC} PARENT_SCOPE)
set(DRIVER_SRC ${DRIVER_SRC} PARENT_SCOPE)

