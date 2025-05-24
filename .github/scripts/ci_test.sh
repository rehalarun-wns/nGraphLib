#!/bin/bash
set -e

BUILD_TYPE=${1:-Debug}
BUILD_DIR="build/linux/${BUILD_TYPE,,}"

echo "Running tests in $BUILD_TYPE mode..."

cd "$BUILD_DIR"
# Find the test binary (assuming it's named graphs_tests)
TEST_BIN=$(find . -type f -executable -name "graphs_tests" | head -n 1)

if [[ -z "$TEST_BIN" ]]; then
    echo "Error: Test binary 'graphs_tests' not found in $BUILD_DIR."
    exit 1
fi

"$TEST_BIN" --gtest_color=yes
