cmake_minimum_required(VERSION 3.16)
project(nGraphLib LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable testing
include(CTest)

# Add subdirectories
add_subdirectory(graphs)

# Add other components as needed
# add_subdirectory(algorithms)
# add_subdirectory(examples)
# add_subdirectory(benchmarks)