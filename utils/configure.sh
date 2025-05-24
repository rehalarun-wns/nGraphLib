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

# Get the absolute path of the script's directory
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

# Default to Debug mode
BUILD_TYPE="Debug"
BUILD_DIR="$SCRIPT_DIR/../build/linux/debug"
SOURCE_DIR="$SCRIPT_DIR/.."
LOG_DIR="$BUILD_DIR"
VERBOSE=0

# Parse arguments
while [[ $# -gt 0 ]]; do
    case $1 in
    -r | --release)
        BUILD_TYPE="Release"
        BUILD_DIR="$SCRIPT_DIR/../build/linux/release"
        shift
        ;;
    -d | --debug)
        BUILD_TYPE="Debug"
        BUILD_DIR="$SCRIPT_DIR/../build/linux/debug"
        shift
        ;;
    --help | -h)
        echo "Usage: ./configure.sh [-r|--release] [-d|--debug] [-v|--verbose] [--help]"
        echo "  -r, --release   - Configure the project in Release mode"
        echo "  -d, --debug     - Configure the project in Debug mode (default)"
        echo "  -v, --verbose   - Enable verbose output"
        echo "  --help, -h      - Show this help message"
        exit 0
        ;;
    -v | --verbose)
        VERBOSE=1
        shift
        ;;
    *)
        echo -e "${RED}Unknown argument: $1${NC}"
        exit 1
        ;;
    esac
done

# create the build directory
mkdir -p "$BUILD_DIR"

# Log file path
LOG_FILE="$BUILD_DIR/configure.log"

echo -e "$(timestamp) ${BLUE}Configuring project from ${SCRIPT_DIR} in ${BUILD_TYPE} mode...${NC}" | tee -a "$LOG_FILE"

# Run CMake with the specified build type
if [[ $VERBOSE -eq 1 ]]; then
    cmake -S "$SOURCE_DIR" -B "$BUILD_DIR" -DCMAKE_BUILD_TYPE="$BUILD_TYPE" | tee -a "$LOG_FILE"
else
    cmake -S "$SOURCE_DIR" -B "$BUILD_DIR" -DCMAKE_BUILD_TYPE="$BUILD_TYPE" >>"$LOG_FILE" 2>&1
fi

echo -e "$(timestamp) ${GREEN}Configuration completed successfully in $BUILD_DIR.${NC}" | tee -a "$LOG_FILE"
