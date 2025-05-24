#!/bin/bash
set -e

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[0;33m'
BLUE='\033[0;34m'
NC='\033[0m'

timestamp() {
    date +"%Y-%m-%d %H:%M:%S"
}

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

BUILD_TYPE="Debug"
BUILD_DIR="$SCRIPT_DIR/../build/linux/debug"
CLEAN_ALL=0

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
    -a | --all)
        CLEAN_ALL=1
        shift
        ;;
    --help | -h)
        echo "Usage: ./clean.sh [-r|--release] [-d|--debug] [-a|--all] [--help]"
        echo "  -r, --release   - Clean the Release build directory"
        echo "  -d, --debug     - Clean the Debug build directory (default)"
        echo "  -a, --all       - Clean both Debug and Release build directories"
        echo "  --help, -h      - Show this help message"
        exit 0
        ;;
    *)
        echo -e "${RED}Unknown argument: $1${NC}"
        exit 1
        ;;
    esac
done

if [[ $CLEAN_ALL -eq 1 ]]; then
    for DIR in "$SCRIPT_DIR/../build/linux/debug" "$SCRIPT_DIR/../build/linux/release"; do
        DIR=$(realpath "$DIR")
        echo -e "$(timestamp) ${BLUE}Attempting to clean: $DIR${NC}"
        if [ -d "$DIR" ]; then
            rm -rf "$DIR"
            echo -e "$(timestamp) ${GREEN}Cleaned $DIR successfully.${NC}"
        else
            echo -e "$(timestamp) ${YELLOW}Warning: Build directory $DIR does not exist.${NC}"
        fi
    done
    exit 0
fi

BUILD_DIR=$(realpath "$BUILD_DIR")
echo -e "$(timestamp) ${BLUE}Attempting to clean: $BUILD_DIR${NC}"
if [ ! -d "$BUILD_DIR" ]; then
    echo -e "$(timestamp) ${YELLOW}Warning: Build directory $BUILD_DIR does not exist.${NC}"
    exit 0
fi

rm -rf "$BUILD_DIR"
echo -e "$(timestamp) ${GREEN}Build directory cleaned successfully: $BUILD_DIR${NC}"
