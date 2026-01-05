cmake_minimum_required(VERSION 3.16)
project(DataStructuresAlgorithms C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

option(ENABLE_COVERAGE "Enable coverage" OFF)

# =============================
# Coverage
# =============================
if(ENABLE_COVERAGE)
    message(STATUS "Coverage enabled")
    add_compile_options(--coverage -O0 -g)
    add_link_options(--coverage)
endif()

# =============================
# CUnit
# =============================
find_library(CUNIT_LIB cunit REQUIRED)
include(CTest)
enable_testing()

# =============================
# Core library
# =============================
file(GLOB_RECURSE CORE_SOURCES
    src/data_structures/*.c
    src/algorithms/*.c
    src/utils/common_math.c
    src/utils/error_reporter.c
    src/utils/result_code.c
    src/utils/internal/*.c
)

add_library(core STATIC ${CORE_SOURCES})

target_include_directories(core
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include
    PRIVATE
        ${PROJECT_SOURCE_DIR}/src
)

# =============================
# Tests
# =============================
file(GLOB_RECURSE TEST_SOURCES
    src/**/*_test.c
    src/**/test/*.c
)

add_executable(run_tests
    ${TEST_SOURCES}
    src/test_runner.c
)

target_link_libraries(run_tests
    core
    ${CUNIT_LIB}
)

add_test(NAME all_tests COMMAND run_tests)

