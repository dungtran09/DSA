#!/usr/bin/env bash
set -e

BUILD_DIR=build
COVERAGE_DIR=coverage

cd $BUILD_DIR

# Capture coverage
lcov --capture --directory . --output-file coverage.info

# Remove test & system files
lcov --remove coverage.info \
    '*/test/*' \
    '*_test.c' \
    '*_test_case.c' \
    '*/CMakeFiles/*' \
    '/usr/*' \
    --output-file coverage.filtered.info

# Generate HTML
genhtml coverage.filtered.info --output-directory ../$COVERAGE_DIR

echo "Coverage report generated at $COVERAGE

