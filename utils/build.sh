#!/bin/bash

set -e

# Define colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[0;33m'
BLUE='\033[0;34m'
NC='\033[0m'

# Timestamp function
timestamp() {
    date +"%Y-%m-%d %H:%M:%S"
}

# Function to show help
show_help() {
    echo "Usage: ./build.sh [-r|--release] [-d|--debug] [-v|--verbose] [-c|--clean] [--help]"
    echo "  -r, --release   - Build the project in Release mode"
    echo "  -d, --debug     - Build the project in Debug mode (default)"
    echo "  -v, --verbose   - Enable verbose output"
    echo "  -c, --clean     - Clean the build directory before building"
    echo "  --help          - Show this help message"
    exit 0
}

# Check for required tools
if ! command -v cmake &>/dev/null; then
    echo -e "${RED}❌ Error: cmake is not installed.${NC}"
    exit 1
fi

# Get the absolute path of the script's directory
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

# Default to Debug mode if no argument is given
BUILD_TYPE="Debug"
BUILD_DIR="$SCRIPT_DIR/../build/linux/debug"
LOG_DIR="$BUILD_DIR"
VERBOSE=0
CLEAN_BUILD=0

# Parse arguments
CONFIGURE_ARGS=()
BUILD_TYPE_SET=0
while [[ $# -gt 0 ]]; do
    case $1 in
    -r | --release)
        BUILD_TYPE="Release"
        BUILD_DIR="$SCRIPT_DIR/../build/linux/release"
        LOG_DIR="$BUILD_DIR"
        CONFIGURE_ARGS=("-r")
        BUILD_TYPE_SET=1
        shift
        ;;
    -d | --debug)
        BUILD_TYPE="Debug"
        BUILD_DIR="$SCRIPT_DIR/../build/linux/debug"
        LOG_DIR="$BUILD_DIR"
        CONFIGURE_ARGS=("-d")
        BUILD_TYPE_SET=1
        shift
        ;;
    -c | --clean)
        CLEAN_BUILD=1
        shift
        ;;
    -v | --verbose)
        VERBOSE=1
        shift
        ;;
    --help)
        show_help
        ;;
    *)
        echo -e "${RED}Unknown argument: $1${NC}"
        show_help
        ;;
    esac
done

# Clean build directory if requested
if [[ $CLEAN_BUILD -eq 1 ]]; then
    echo -e "${BLUE}Cleaning build directory: $BUILD_DIR${NC}"
    rm -rf "$BUILD_DIR"
fi

# If no build type was set, default to debug
if [[ $BUILD_TYPE_SET -eq 0 ]]; then
    CONFIGURE_ARGS=("-d")
fi

# Ensure LOG_DIR is always set
LOG_DIR="$BUILD_DIR"

# Ensure the build directory exists
if [[ ! -d "$BUILD_DIR" ]]; then
    echo -e "${BLUE}⚙️  Build directory '$BUILD_DIR' does not exist. Running configure.sh with options: ${CONFIGURE_ARGS[*]}...${NC}"
    if [[ -f "$SCRIPT_DIR/configure.sh" ]]; then
        bash "$SCRIPT_DIR/configure.sh" "${CONFIGURE_ARGS[@]}"
    else
        echo -e "${RED}❌ Error: configure.sh not found in project root.${NC}"
        exit 1
    fi
fi

echo -e "${BLUE}🔨 Building project in $BUILD_TYPE mode (using $(nproc) CPU cores)...${NC}"
CMD="cmake --build \"$BUILD_DIR\" -- -j $(nproc)"

# Run the build command
if [[ $VERBOSE -eq 1 ]]; then
    echo "Running: $CMD"
    eval "$CMD" | tee "$LOG_DIR/build.log"
else
    eval "$CMD" >"$LOG_DIR/build.log" 2>&1
fi

# Check for errors in the build process
if [[ $? -ne 0 ]]; then
    echo -e "${RED}❌ Build failed! Check the log file at '$LOG_DIR/build.log' for details.${NC}"
    exit 1
fi

echo -e "${GREEN}✅ Build complete! Logs saved in '$LOG_DIR/build.log'.${NC}"
