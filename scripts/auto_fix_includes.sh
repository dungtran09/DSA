#!/usr/bin/env bash
set -e

ROOT_DIR=$(git rev-parse --show-toplevel)
SRC_DIR="$ROOT_DIR/src"
TEST_DIR="$ROOT_DIR/tests"

echo "🔧 Auto-fixing #include paths (safe mode)..."

fix_file() {
  local file="$1"

  # remove leading relative paths before include/
  sed -i 's@#include[[:space:]]*".*/include/@#include "@g' "$file"

  # normalize data_structures
  sed -i 's@#include[[:space:]]*".*/data_structures/@#include "data_structures/@g' "$file"

  # normalize algorithms
  sed -i 's@#include[[:space:]]*".*/algorithms/@#include "algorithms/@g' "$file"

  # utils headers (flat)
  sed -i 's@#include[[:space:]]*"common_math.h"@#include "utils/common_math.h"@g' "$file"
  sed -i 's@#include[[:space:]]*"comparators.h"@#include "utils/comparators.h"@g' "$file"
  sed -i 's@#include[[:space:]]*"error_reporter.h"@#include "utils/error_reporter.h"@g' "$file"
  sed -i 's@#include[[:space:]]*"result_code.h"@#include "utils/result_code.h"@g' "$file"
  sed -i 's@#include[[:space:]]*"test_helpers.h"@#include "utils/test_helpers.h"@g' "$file"
}

export -f fix_file

find "$SRC_DIR" "$TEST_DIR" \
  -type f \( -name "*.c" -o -name "*.h" \) \
  -print0 | xargs -0 -n1 bash -c 'fix_file "$0"'

echo "✅ Includes fixed (safe mode)."

