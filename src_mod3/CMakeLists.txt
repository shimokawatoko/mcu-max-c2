# CMakeLists.txt

cmake_minimum_required(VERSION 3.10)

# Project name
project(mcu_max_chess_engine LANGUAGES C)

# Set C standard
set(CMAKE_C_STANDARD 99)

# Add the executable target
add_executable(mcu_max
    main.c
    mcumax_constants.c
    mcumax_types.c
    mcumax_api.c
    mcumax_init.c
    mcumax_engine_core.c
    mcumax_helpers.c
)

# Include directories
target_include_directories(mcu_max PRIVATE ${CMAKE_SOURCE_DIR})
