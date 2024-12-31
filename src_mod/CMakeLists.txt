cmake_minimum_required(VERSION 3.16.0)

project(mcu-max-uci)

set(CMAKE_C_STANDARD 99)

add_executable(mcu-max-uci 
   main.c
   src/mcumax_board.c 
   src/mcumax_core.c
   src/mcumax_fen.c
   src/mcumax_search.c
)

target_include_directories(mcu-max-uci PRIVATE src_mod)