cmake_minimum_required(VERSION 3.16)

project(ReCreations LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# === Source discovery ===
set(SRC_DIR src)
file(GLOB_RECURSE PROJECT_SOURCES
    "${SRC_DIR}/*.cpp" "${SRC_DIR}/*/*.cpp" "${SRC_DIR}/*/*/*.cpp"
    "${SRC_DIR}/*.hpp" "${SRC_DIR}/*/*.hpp" "${SRC_DIR}/*/*/*.hpp"
)
set(MAIN_FILE main.cpp)

add_executable(main ${MAIN_FILE} ${PROJECT_SOURCES})

# # === Include directories ===
# target_include_directories(main PUBLIC
#     ${SRC_DIR}
#     ${SRC_DIR}/memory
#     ${SRC_DIR}/os
#     ${SRC_DIR}/utilities
#     ${SRC_DIR}/vector
#     ${SRC_DIR}/result
# )

# === Optional: math library on Linux ===
target_link_libraries(main PRIVATE m)

# ============================================================
#                     COMPILER DETECTION
# ============================================================

set(COMMON_WARNINGS
    -Wall -Wextra -Wpedantic
    -Wshadow -Wconversion -Wformat=2
    -Wnull-dereference
)

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    message(STATUS "Compiler: GCC")
    set(EXTRA_WARNINGS
        -Wduplicated-cond
        -Wduplicated-branches
        -Wlogical-op
    )
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    message(STATUS "Compiler: Clang")
    set(EXTRA_WARNINGS
        -Wold-style-cast
        -Wnull-dereference
    )
else()
    message(WARNING "Unknown compiler. Only basic warnings will be used.")
    set(EXTRA_WARNINGS "")
endif()

target_compile_options(main PRIVATE ${COMMON_WARNINGS} ${EXTRA_WARNINGS})

# === Optional -Werror ===
option(ENABLE_WERROR "Treat warnings as errors" OFF)
if (ENABLE_WERROR)
    target_compile_options(main PRIVATE -Werror)
endif()

# ============================================================
#                     DEBUG BUILD (Safe Mode)
# ============================================================

# Debug flags: sanitize + debugging + no LTO
target_compile_options(main PRIVATE
    $<$<CONFIG:Debug>:
        -Og                     # good balance for sanitizer + debugger
        -g
        -fno-omit-frame-pointer
        -fstack-protector-strong
        -D_FORTIFY_SOURCE=2
        -fsanitize=address,undefined
    >
)
target_link_options(main PRIVATE
    $<$<CONFIG:Debug>:
        -fsanitize=address,undefined
        -fno-lto
    >
)

# ============================================================
#                     RELEASE BUILD (Optimized)
# ============================================================

target_compile_options(main PRIVATE
    $<$<CONFIG:Release>:
        -O3 -march=native
        -DNDEBUG
        -fstack-protector-strong
        -D_FORTIFY_SOURCE=2
        -flto
    >
)

target_link_options(main PRIVATE
    $<$<CONFIG:Release>:
        -flto
    >
)

# ============================================================
#           OPTIONAL: Enable ThreadSanitizer build
# ============================================================

option(ENABLE_TSAN "Enable ThreadSanitizer build (mutually exclusive with ASan)" OFF)
if (ENABLE_TSAN)
    message(STATUS "ThreadSanitizer enabled")
    target_compile_options(main PRIVATE -fsanitize=thread -O1 -g -fno-omit-frame-pointer)
    target_link_options(main PRIVATE -fsanitize=thread)
endif()
