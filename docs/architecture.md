# Architecture Overview
This repository follows a strict layered architecture inspired by CLRS.

## Directory Layout
include/ Public APIs
src/ Implementations and tests
docs/ Architecture & design documents

## Layers
Algorithms
↓
Data Structures
↓
Utils


### Rules
- Algorithms MAY use data_structures and utils
- Data structures MAY use utils
- Utils MUST NOT depend on higher layers
- Tests may access private/internal headers
- Public headers live ONLY in include/

## Naming Convention
- One data structure per directory
- One public header per module
- Tests named *_test.c
- Test cases separated in *_test_case.c

## Build & Test
- CMake (GNU C11)
- CUnit for unit tests
- ctest for execution
- lcov + genhtml for coverage

## Coverage Policy
- Test code excluded
- Internal helpers excluded
- Only production code counted
