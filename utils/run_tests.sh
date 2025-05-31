#!/bin/bash

GREEN='\033[0;32m'
RED='\033[0;31m'
BLUE='\033[0;34m'
NC='\033[0m'

VERBOSE=0
JOBS=$(nproc)

SCRIPT_DIR="$(dirname "$(realpath "$0")")"
PROJECT_ROOT="$(realpath "$SCRIPT_DIR/..")"
BUILD_DIR="$PROJECT_ROOT/build/linux/debug"
LOG_FILE="$BUILD_DIR/test.log"

usage() {
    echo "Usage: $0 [-v] [-j <num_jobs>]"
    echo "  -v          Enable verbose output"
    echo "  -j <num>    Number of parallel jobs for testing (default: auto-detected)"
    exit 1
}

while [[ "$#" -gt 0 ]]; do
    case "$1" in
    -v | --verbose) VERBOSE=1 ;;
    -j | --jobs)
        shift
        if [[ "$1" =~ ^[0-9]+$ ]]; then
            JOBS="$1"
        else
            echo -e "${RED}Error: Invalid argument for -j. Expected a number.${NC}"
            usage
        fi
        ;;
    *)
        echo -e "${RED}Error: Unknown option $1${NC}"
        usage
        ;;
    esac
    shift
done

if [ ! -d "$BUILD_DIR" ]; then
    echo -e "${RED}Error: Build directory not found at $BUILD_DIR.${NC}"
    echo "Run './build.sh' first."
    exit 1
fi

cd "$BUILD_DIR" || exit 1

# Find all test binaries ending with _tests
TEST_BINS=$(find . -type f -executable -name "*_tests")

if [[ -z "$TEST_BINS" ]]; then
    echo -e "${RED}No test binaries found in $BUILD_DIR.${NC}"
    exit 1
fi

# Truncate log file at start
>"$LOG_FILE"

ALL_PASS=1
for TEST_BIN in $TEST_BINS; do
    echo -e "${BLUE}Running $TEST_BIN with GoogleTest output...${NC}"
    if [[ "$VERBOSE" -eq 1 ]]; then
        "$TEST_BIN" --gtest_color=yes | tee -a "$LOG_FILE"
    else
        "$TEST_BIN" --gtest_color=no >>"$LOG_FILE"
    fi
    if [[ ${PIPESTATUS[0]} -ne 0 ]]; then
        ALL_PASS=0
    fi
done

if [[ $ALL_PASS -eq 1 ]]; then
    echo -e "${GREEN}✅ All tests passed! Log saved to $LOG_FILE${NC}"
else
    echo -e "${RED}❌ Some tests failed. See $LOG_FILE for details.${NC}"
    exit 1
fi
