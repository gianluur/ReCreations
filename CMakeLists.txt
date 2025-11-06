cmake_minimum_required(VERSION 3.10)

# Change project to use C++ instead of C
project(ReCreations LANGUAGES CXX)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Source directories
set(SRC_DIR src)

# Collect all source files recursively (C++ files now)
file(GLOB_RECURSE PROJECT_SOURCES
    "${SRC_DIR}/*.cpp"
    "${SRC_DIR}/*/*.cpp"
    "${SRC_DIR}/*/*/*.cpp"
)

# Main file
set(MAIN_FILE main.cpp)

# Create the executable
add_executable(main ${MAIN_FILE} ${PROJECT_SOURCES})

# Macro for using only recreations
#target_compile_definitions(main PRIVATE RECREATIONS_ONLY)

# Link math library if needed
target_link_libraries(main PRIVATE m)

# Include directories
target_include_directories(main PUBLIC
    ${SRC_DIR}
    ${SRC_DIR}/memory
    ${SRC_DIR}/utilities
)

# Compiler warnings
target_compile_options(main PRIVATE -Wall -Wextra)