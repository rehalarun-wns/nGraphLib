add_library(algorithms INTERFACE)

target_include_directories(algorithms
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../graphs>
)

add_subdirectory(tests)
