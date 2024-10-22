add_library(GameBoyEmuCore STATIC src/cpu.cpp src/registers.cpp src/memory.cpp)
target_include_directories(GameBoyEmuCore PUBLIC include)
target_compile_options(GameBoyEmuCore PUBLIC -Wno-gnu-anonymous-struct
                                             -Wno-nested-anon-types)
