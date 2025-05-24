enable_testing()

add_executable(graphs_tests
    test_main.cpp
    test_directed_graph.cpp
    test_undirected_graph.cpp
)

target_link_libraries(graphs_tests
    PRIVATE
        graphs
        gtest
)

add_test(NAME GraphsTests COMMAND graphs_tests)