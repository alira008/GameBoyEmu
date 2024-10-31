cmake_minimum_required(VERSION 3.24)

# Place targets in bin/ or lib/ for all build configurations
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(GameBoyEmu CXX)

add_subdirectory(thirdparty)

add_executable(GameBoyEmulator src/main.cpp src/core/cpu.cpp
                               src/core/memory.cpp src/core/registers.cpp src/core/disassembly.cpp)
target_include_directories(GameBoyEmulator PUBLIC include)

target_link_libraries(GameBoyEmulator PRIVATE raylib raygui)

target_compile_options(
  GameBoyEmulator
  PRIVATE -Wall
          -Wextra
          -pedantic
          -Wno-unused-parameter
          -Wstrict-prototypes
          -Wshadow
          -Wconversion
          -Wvla
          -Wdouble-promotion
          -Wmissing-noreturn
          -Wmissing-format-attribute
          -Wmissing-prototypes
          -fsigned-char
          -Wno-gnu-anonymous-struct
          -Wno-nested-anon-types)
