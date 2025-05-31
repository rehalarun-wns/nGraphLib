#include <gtest/gtest.h>
#include "algorithm_factory.h"
#include "directed_graph.h"
#include <sstream>

TEST(DFSTest, VisitsAllReachableVertices)
{
    DirectedGraph<int> g{};
    g.AddEdge(1, 2);
    g.AddEdge(2, 3);
    g.AddEdge(3, 4);
    g.AddEdge(1, 5);

    auto dfs = Graph::AlgorithmFactory<DirectedGraph<int>, std::vector<int>>::create(Graph::AlgorithmType::DFS_Ty);
    ASSERT_TRUE(dfs != nullptr);
    auto visited_order = dfs->run(g, 1);
    // visited orderr should contain all vertices
    for (int i = 1; i <= 5; ++i)
    {
        EXPECT_TRUE(std::find(visited_order.begin(), visited_order.end(), i) != visited_order.end())
            << "Vertex " << i << " was not visited";
    }
}

TEST(DFSTest, HandlesDisconnectedGraph)
{
    DirectedGraph<int> g{};
    g.AddEdge(1, 2);
    g.AddEdge(3, 4);

    auto dfs = Graph::AlgorithmFactory<DirectedGraph<int>, std::vector<int>>::create(Graph::AlgorithmType::DFS_Ty);
    ASSERT_TRUE(dfs != nullptr);
    auto visited_order = dfs->run(g, 1);

    // Only vertices 1 and 2 should be visited
    EXPECT_EQ(visited_order.size(), 2);
    EXPECT_TRUE(std::find(visited_order.begin(), visited_order.end(), 1) != visited_order.end());
    EXPECT_TRUE(std::find(visited_order.begin(), visited_order.end(), 2) != visited_order.end());
}

TEST(DFSTest, HandlesEmptyGraph)
{
    DirectedGraph<int> g{};

    auto dfs = Graph::AlgorithmFactory<DirectedGraph<int>, std::vector<int>>::create(Graph::AlgorithmType::DFS_Ty);
    ASSERT_TRUE(dfs != nullptr);
    // No vertices should be visited
    EXPECT_THROW(dfs->run(g, 1), std::runtime_error);
}

TEST(DFSTest, HandlesSingleVertexGraph)
{
    DirectedGraph<int> g{};
    g.AddEdge(1, 1); // Self-loop

    auto dfs = Graph::AlgorithmFactory<DirectedGraph<int>, std::vector<int>>::create(Graph::AlgorithmType::DFS_Ty);
    ASSERT_TRUE(dfs != nullptr);
    auto visited_order = dfs->run(g, 1);

    // Only vertex 1 should be visited
    EXPECT_EQ(visited_order.size(), 1);
    EXPECT_EQ(visited_order[0], 1);
}

TEST(DFSTest, HandlesGraphWithSelfLoops)
{
    DirectedGraph<int> g{};
    g.AddEdge(1, 2);
    g.AddEdge(2, 2); // Self-loop
    g.AddEdge(2, 3);

    auto dfs = Graph::AlgorithmFactory<DirectedGraph<int>, std::vector<int>>::create(Graph::AlgorithmType::DFS_Ty);
    ASSERT_TRUE(dfs != nullptr);
    auto visited_order = dfs->run(g, 1);

    // All reachable vertices should be visited
    EXPECT_EQ(visited_order.size(), 3);
    EXPECT_TRUE(std::find(visited_order.begin(), visited_order.end(), 1) != visited_order.end());
    EXPECT_TRUE(std::find(visited_order.begin(), visited_order.end(), 2) != visited_order.end());
    EXPECT_TRUE(std::find(visited_order.begin(), visited_order.end(), 3) != visited_order.end());
}

TEST(DFSTest, HandlesGraphWithMultipleEdges)
{
    DirectedGraph<int> g{};
    g.AddEdge(1, 2);
    g.AddEdge(1, 2); // Duplicate edge
    g.AddEdge(2, 3);
    g.AddEdge(3, 4);
    g.AddEdge(4, 5);
    g.AddEdge(5, 1); // Cycle

    auto dfs = Graph::AlgorithmFactory<DirectedGraph<int>, std::vector<int>>::create(Graph::AlgorithmType::DFS_Ty);
    ASSERT_TRUE(dfs != nullptr);
    auto visited_order = dfs->run(g, 1);

    // All reachable vertices should be visited
    EXPECT_EQ(visited_order.size(), 5);
    for (int i = 1; i <= 5; ++i)
    {
        EXPECT_TRUE(std::find(visited_order.begin(), visited_order.end(), i) != visited_order.end())
            << "Vertex " << i << " was not visited";
    }
}