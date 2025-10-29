# Minimum required version of CMake
cmake_minimum_required(VERSION 3.10)

# Project name and language
project(MyCProject C)

# Set a standard for C (optional but recommended)
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED True)

# Define the source directory
set(SRC_DIR src)

# --- Collect Source Files ---
# Recursively find all C source files
file(GLOB_RECURSE PROJECT_SOURCES
    "${SRC_DIR}/*.c"
    "${SRC_DIR}/*/*.c"
    "${SRC_DIR}/*/*/*.c"
)

# You must explicitly add main.c since it's at the root of the project
set(MAIN_FILE main.c)

# --- Create Executable ---
# STEP 1: Define the executable target first!
add_executable(main ${MAIN_FILE} ${PROJECT_SOURCES})

target_link_libraries(main PRIVATE m)

target_include_directories(main PUBLIC
    ${SRC_DIR}
    ${SRC_DIR}/converters/*
    ${SRC_DIR}/io/*
    ${SRC_DIR}/utilities/*
    
)