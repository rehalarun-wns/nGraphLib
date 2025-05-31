#!/bin/bash
set -e

BUILD_TYPE=${1:-Debug}
BUILD_DIR="build/linux/${BUILD_TYPE,,}"

echo "Running all test binaries in $BUILD_TYPE mode..."

cd "$BUILD_DIR"

# Find all test binaries ending with _tests
TEST_BINS=$(find . -type f -executable -name "*_tests")

if [[ -z "$TEST_BINS" ]]; then
    echo "Error: No test binaries found in $BUILD_DIR."
    exit 1
fi

ALL_PASS=1
for TEST_BIN in $TEST_BINS; do
    echo "Running $TEST_BIN..."
    "$TEST_BIN" --gtest_color=yes || ALL_PASS=0
done

if [[ $ALL_PASS -eq 1 ]]; then
    echo "✅ All tests passed!"
else
    echo "❌ Some tests failed."
    exit 1
fi
