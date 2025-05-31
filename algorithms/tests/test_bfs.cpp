#include <gtest/gtest.h>
#include "algorithm_factory.h"
#include "directed_graph.h"
#include "undirected_graph.h"

using GraphTypes = ::testing::Types<
    DirectedGraph<int>,
    UndirectedGraph<int>>;

template <typename GraphT>
class BFSTest : public ::testing::Test
{
public:
    using GraphType = GraphT;
};

TYPED_TEST_SUITE(BFSTest, GraphTypes);

TYPED_TEST(BFSTest, VisitsAllReachableVertices)
{
    typename TestFixture::GraphType g;
    g.AddEdge(1, 2);
    g.AddEdge(2, 3);
    g.AddEdge(3, 4);
    g.AddEdge(1, 5);

    auto bfs = Graph::AlgorithmFactory<typename TestFixture::GraphType, std::vector<int>>::create(Graph::AlgorithmType::BFS_Ty);
    ASSERT_TRUE(bfs != nullptr);
    auto visited_order = bfs->run(g, 1);

    for (int i = 1; i <= 5; ++i)
    {
        EXPECT_TRUE(std::find(visited_order.begin(), visited_order.end(), i) != visited_order.end())
            << "Vertex " << i << " was not visited";
    }
}

TYPED_TEST(BFSTest, HandlesDisconnectedGraph)
{
    typename TestFixture::GraphType g;
    g.AddEdge(1, 2);
    g.AddEdge(3, 4);

    auto bfs = Graph::AlgorithmFactory<typename TestFixture::GraphType, std::vector<int>>::create(Graph::AlgorithmType::BFS_Ty);
    ASSERT_TRUE(bfs != nullptr);
    auto visited_order = bfs->run(g, 1);

    EXPECT_EQ(visited_order.size(), 2);
    EXPECT_TRUE(std::find(visited_order.begin(), visited_order.end(), 1) != visited_order.end());
    EXPECT_TRUE(std::find(visited_order.begin(), visited_order.end(), 2) != visited_order.end());
}

TYPED_TEST(BFSTest, HandlesEmptyGraph)
{
    typename TestFixture::GraphType g;

    auto bfs = Graph::AlgorithmFactory<typename TestFixture::GraphType, std::vector<int>>::create(Graph::AlgorithmType::BFS_Ty);
    ASSERT_TRUE(bfs != nullptr);
    EXPECT_THROW(bfs->run(g, 1), std::runtime_error);
}

TYPED_TEST(BFSTest, HandlesSingleVertexGraph)
{
    typename TestFixture::GraphType g;
    g.AddEdge(1, 1); // Self-loop

    auto bfs = Graph::AlgorithmFactory<typename TestFixture::GraphType, std::vector<int>>::create(Graph::AlgorithmType::BFS_Ty);
    ASSERT_TRUE(bfs != nullptr);
    auto visited_order = bfs->run(g, 1);

    EXPECT_EQ(visited_order.size(), 1);
    EXPECT_EQ(visited_order[0], 1);
}

TYPED_TEST(BFSTest, HandlesGraphWithSelfLoops)
{
    typename TestFixture::GraphType g;
    g.AddEdge(1, 2);
    g.AddEdge(2, 2); // Self-loop
    g.AddEdge(2, 3);

    auto bfs = Graph::AlgorithmFactory<typename TestFixture::GraphType, std::vector<int>>::create(Graph::AlgorithmType::BFS_Ty);
    ASSERT_TRUE(bfs != nullptr);
    auto visited_order = bfs->run(g, 1);

    EXPECT_EQ(visited_order.size(), 3);
    EXPECT_TRUE(std::find(visited_order.begin(), visited_order.end(), 1) != visited_order.end());
    EXPECT_TRUE(std::find(visited_order.begin(), visited_order.end(), 2) != visited_order.end());
    EXPECT_TRUE(std::find(visited_order.begin(), visited_order.end(), 3) != visited_order.end());
}

TYPED_TEST(BFSTest, HandlesGraphWithMultipleEdges)
{
    typename TestFixture::GraphType g;
    g.AddEdge(1, 2);
    g.AddEdge(1, 2); // Duplicate edge
    g.AddEdge(2, 3);
    g.AddEdge(3, 4);
    g.AddEdge(4, 5);
    g.AddEdge(5, 1); // Cycle

    auto bfs = Graph::AlgorithmFactory<typename TestFixture::GraphType, std::vector<int>>::create(Graph::AlgorithmType::BFS_Ty);
    ASSERT_TRUE(bfs != nullptr);
    auto visited_order = bfs->run(g, 1);

    EXPECT_EQ(visited_order.size(), 5);
    for (int i = 1; i <= 5; ++i)
    {
        EXPECT_TRUE(std::find(visited_order.begin(), visited_order.end(), i) != visited_order.end())
            << "Vertex " << i << " was not visited";
    }
}