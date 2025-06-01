#include <gtest/gtest.h>
#include "algorithm_factory.h"
#include "directed_graph.h"
#include "undirected_graph.h"
#include <vector>
#include <algorithm>

using GraphTypes = ::testing::Types<
    DirectedGraph<int>,
    UndirectedGraph<int>>;

template <typename GraphT>
class DFSTest : public ::testing::Test
{
public:
    using GraphType = GraphT;
};

TYPED_TEST_SUITE(DFSTest, GraphTypes);

TYPED_TEST(DFSTest, VisitsAllReachableVertices)
{
    typename TestFixture::GraphType g;
    g.AddEdge(1, 2);
    g.AddEdge(2, 3);
    g.AddEdge(3, 4);
    g.AddEdge(1, 5);

    auto dfs = Graph::AlgorithmFactory<typename TestFixture::GraphType, std::vector<int>>::create(Graph::AlgorithmType::DFS_Ty);
    ASSERT_TRUE(dfs != nullptr);
    auto visited_order = dfs->run(g, 1);

    for (int i = 1; i <= 5; ++i)
    {
        EXPECT_TRUE(std::find(visited_order.begin(), visited_order.end(), i) != visited_order.end())
            << "Vertex " << i << " was not visited";
    }
}

TYPED_TEST(DFSTest, HandlesDisconnectedGraph)
{
    typename TestFixture::GraphType g;
    g.AddEdge(1, 2);
    g.AddEdge(3, 4);

    auto dfs = Graph::AlgorithmFactory<typename TestFixture::GraphType, std::vector<int>>::create(Graph::AlgorithmType::DFS_Ty);
    ASSERT_TRUE(dfs != nullptr);
    auto visited_order = dfs->run(g, 1);

    EXPECT_EQ(visited_order.size(), 2);
    EXPECT_TRUE(std::find(visited_order.begin(), visited_order.end(), 1) != visited_order.end());
    EXPECT_TRUE(std::find(visited_order.begin(), visited_order.end(), 2) != visited_order.end());
}

TYPED_TEST(DFSTest, HandlesEmptyGraph)
{
    typename TestFixture::GraphType g;

    auto dfs = Graph::AlgorithmFactory<typename TestFixture::GraphType, std::vector<int>>::create(Graph::AlgorithmType::DFS_Ty);
    ASSERT_TRUE(dfs != nullptr);
    EXPECT_THROW(dfs->run(g, 1), std::runtime_error);
}

TYPED_TEST(DFSTest, HandlesSingleVertexGraph)
{
    typename TestFixture::GraphType g;
    g.AddEdge(1, 1); // Self-loop

    auto dfs = Graph::AlgorithmFactory<typename TestFixture::GraphType, std::vector<int>>::create(Graph::AlgorithmType::DFS_Ty);
    ASSERT_TRUE(dfs != nullptr);
    auto visited_order = dfs->run(g, 1);

    EXPECT_EQ(visited_order.size(), 1);
    EXPECT_EQ(visited_order[0], 1);
}

TYPED_TEST(DFSTest, HandlesGraphWithSelfLoops)
{
    typename TestFixture::GraphType g;
    g.AddEdge(1, 2);
    g.AddEdge(2, 2); // Self-loop
    g.AddEdge(2, 3);

    auto dfs = Graph::AlgorithmFactory<typename TestFixture::GraphType, std::vector<int>>::create(Graph::AlgorithmType::DFS_Ty);
    ASSERT_TRUE(dfs != nullptr);
    auto visited_order = dfs->run(g, 1);

    EXPECT_EQ(visited_order.size(), 3);
    EXPECT_TRUE(std::find(visited_order.begin(), visited_order.end(), 1) != visited_order.end());
    EXPECT_TRUE(std::find(visited_order.begin(), visited_order.end(), 2) != visited_order.end());
    EXPECT_TRUE(std::find(visited_order.begin(), visited_order.end(), 3) != visited_order.end());
}

TYPED_TEST(DFSTest, HandlesGraphWithMultipleEdges)
{
    typename TestFixture::GraphType g;
    g.AddEdge(1, 2);
    g.AddEdge(1, 2); // Duplicate edge
    g.AddEdge(2, 3);
    g.AddEdge(3, 4);
    g.AddEdge(4, 5);
    g.AddEdge(5, 1); // Cycle

    auto dfs = Graph::AlgorithmFactory<typename TestFixture::GraphType, std::vector<int>>::create(Graph::AlgorithmType::DFS_Ty);
    ASSERT_TRUE(dfs != nullptr);
    auto visited_order = dfs->run(g, 1);

    EXPECT_EQ(visited_order.size(), 5);
    for (int i = 1; i <= 5; ++i)
    {
        EXPECT_TRUE(std::find(visited_order.begin(), visited_order.end(), i) != visited_order.end())
            << "Vertex " << i << " was not visited";
    }
}