cmake_minimum_required(VERSION 3.16)

project(DataStructuresAlgorithms C)

# =============================
# C Standard
# =============================

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# =============================
# Options
# =============================

option(ENABLE_COVERAGE "Enable coverage" OFF)

# =============================
# CUnit
# =============================

find_library(CUNIT_LIB cunit REQUIRED)
include(CTest)
enable_testing()

# =============================
# Core sources
# =============================

set(CORE_SOURCES
# ===== Data Structures =====
src/data_structures/array/array.c
# src/data_structures/array/array_algo.c

# ===== Algorithms =====
# src/algorithms/...

# ===== Utils =====
src/utils/common_math.c
src/utils/error_reporter.c
src/utils/result_code.c
# src/utils/internal/...
)

# =============================
# Core library
# =============================

add_library(core STATIC ${CORE_SOURCES})

target_include_directories(core
PUBLIC
${PROJECT_SOURCE_DIR}/include
PRIVATE
${PROJECT_SOURCE_DIR}/src
)

# Warnings (important)

target_compile_options(core PRIVATE
-Wall
-Wextra
-Werror
)

# Coverage (only apply to core)

if(ENABLE_COVERAGE)
message(STATUS "Coverage enabled")
target_compile_options(core PRIVATE --coverage -O0 -g)
target_link_options(core PRIVATE --coverage)
endif()

# =============================
# Tests
# =============================

file(GLOB_RECURSE TEST_SOURCES
src/**/*_test.c
src/**/test/*.c
)
set(TEST_SOURCES
    tests/array/test_array_create.c
    tests/array/test_array_destroy.c
)

add_executable(run_tests
    ${TEST_SOURCES}
    tests/test_runner.c
    src/utils/test/malloc_test_wrapper.c
)

target_include_directories(run_tests PRIVATE
    ${PROJECT_SOURCE_DIR}/include
)

# malloc wrapper (debug / test)

target_link_options(run_tests PRIVATE
-Wl,--wrap=malloc
-Wl,--wrap=calloc
-Wl,--wrap=realloc
-Wl,--wrap=free
)

target_link_libraries(run_tests
core
# ${CUNIT_LIB}
)

# Test only use punlic API

target_include_directories(run_tests
PRIVATE
${PROJECT_SOURCE_DIR}/include
)

add_test(NAME all_tests COMMAND run_tests)

