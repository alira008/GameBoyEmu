cmake_minimum_required(VERSION 3.24)

# Place targets in bin/ or lib/ for all build configurations
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(GameBoyEmu CXX)
add_subdirectory(GameBoyEmu.Core)

add_executable(GameBoyEmulator src/main.cpp)

target_compile_options(GameBoyEmulator PRIVATE -Wall -Wextra -pedantic -Wno-unused-parameter
    -Wstrict-prototypes -Wshadow -Wconversion -Wvla
    -Wdouble-promotion
    -Wmissing-noreturn
    -Wmissing-format-attribute
    -Wmissing-prototypes
    -fsigned-char)

target_link_libraries(GameBoyEmulator PRIVATE GameBoyEmuCore)
