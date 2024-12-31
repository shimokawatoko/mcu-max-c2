cmake_minimum_required(VERSION 3.16.0)

project(mcu-max-uci)

set(CMAKE_C_STANDARD 99)

add_executable(mcu-max-uci 
   main.c
   mcumax_board.c 
   mcumax_core.c
   mcumax_fen.c
   mcumax_search.c
)