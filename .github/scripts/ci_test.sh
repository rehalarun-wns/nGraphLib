#!/bin/bash
set -e

BUILD_TYPE=${1:-Debug}
BUILD_DIR="build/linux/${BUILD_TYPE,,}"

echo "Running tests in $BUILD_TYPE mode..."

cd "$BUILD_DIR"
ctest --output-on-failure --parallel $(nproc)
