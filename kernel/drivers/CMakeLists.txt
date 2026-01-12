#add_subdirectory(bga)
add_subdirectory(vga)
add_subdirectory(ps2)
add_subdirectory(pic)
add_subdirectory(pit)
add_subdirectory(gpu)

set(DRIVER_SRC ${DRIVER_SRC} PARENT_SCOPE)

