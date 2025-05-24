#!/bin/bash
set -e

BUILD_TYPE=${1:-Debug}
BUILD_DIR="build/linux/${BUILD_TYPE,,}"

echo "Configuring and building in $BUILD_TYPE mode..."

cmake -S . -B "$BUILD_DIR" -DCMAKE_BUILD_TYPE="$BUILD_TYPE"
cmake --build "$BUILD_DIR" -- -j$(nproc)

echo "Build complete."
