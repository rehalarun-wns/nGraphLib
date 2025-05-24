#!/bin/bash
set -e

echo "Installing system dependencies..."

sudo apt-get update
sudo apt-get install -y cmake g++ ninja-build

# Install GoogleTest if needed (for system-wide, but usually CMake FetchContent is preferred)
# sudo apt-get install -y libgtest-dev

echo "All dependencies installed."
