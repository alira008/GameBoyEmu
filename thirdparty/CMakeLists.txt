add_subdirectory(raylib)

add_library(raygui INTERFACE)
target_include_directories(raygui INTERFACE raygui/src)
