add_library(GameBoyEmuCore INTERFACE)
target_include_directories(GameBoyEmuCore INTERFACE include)
target_compile_options(GameBoyEmuCore INTERFACE -Wno-gnu-anonymous-struct  -Wno-nested-anon-types)
