enable_testing()

add_executable(graphs_algo_tests
    test_main.cpp
    test_dfs.cpp
    test_bfs.cpp
    test_get_components.cpp
)

target_link_libraries(graphs_algo_tests
    PRIVATE
        algorithms
        gtest
)

add_test(NAME GraphsAlgoTests COMMAND graphs_algo_tests)