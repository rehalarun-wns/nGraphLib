add_library(graphs INTERFACE)

target_include_directories(graphs
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

add_subdirectory(tests)