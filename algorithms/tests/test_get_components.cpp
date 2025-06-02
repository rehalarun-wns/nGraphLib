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
class ComponentsTest : public ::testing::Test
{
public:
    using GraphType = GraphT;
};

TYPED_TEST_SUITE(ComponentsTest, GraphTypes);

TYPED_TEST(ComponentsTest, SingleComponent)
{
    typename TestFixture::GraphType g;
    g.AddEdge(0, 1);
    g.AddEdge(1, 2);
    g.AddEdge(3, 1);

    auto algo = Graph::AlgorithmFactory<typename TestFixture::GraphType, Graph::AlgorithmType::GetComponents_Ty>::create();
    ASSERT_TRUE(algo != nullptr);

    if (g.IsDirected())
    {
        EXPECT_THROW(algo->run(g, 1), std::runtime_error);
    }
    else
    {
        auto components = algo->run(g, 1);
        // There should be only one component
        ASSERT_EQ(components.size(), 1);
        auto vertices = components[0].GetVertices();
        EXPECT_EQ(vertices.size(), 4);
        for (int v = 0; v < 4; ++v)
        {
            EXPECT_TRUE(std::find(vertices.begin(), vertices.end(), v) != vertices.end());
        }
    }
}

TYPED_TEST(ComponentsTest, TwoComponents)
{
    typename TestFixture::GraphType g;
    g.AddEdge(0, 1);
    g.AddEdge(1, 2);
    g.AddEdge(1, 3);
    g.AddEdge(4, 5);
    g.AddEdge(5, 6);
    g.AddEdge(6, 7);
    g.AddEdge(4, 7);
    g.AddEdge(8, 7);

    auto algo = Graph::AlgorithmFactory<typename TestFixture::GraphType, Graph::AlgorithmType::GetComponents_Ty>::create();

    ASSERT_TRUE(algo != nullptr);
    if (g.IsDirected())
    {
        EXPECT_THROW(algo->run(g, 1), std::runtime_error);
    }
    else
    {
        auto components = algo->run(g, 1);
        // There should be two components
        ASSERT_EQ(components.size(), 2);

        auto comp1_vertices = components[0].GetVertices();
        auto comp2_vertices = components[1].GetVertices();

        EXPECT_EQ(comp1_vertices.size(), 4);
        EXPECT_EQ(comp2_vertices.size(), 5);

        for (int v = 0; v < 4; ++v)
        {
            EXPECT_TRUE(std::find(comp1_vertices.begin(), comp1_vertices.end(), v) != comp1_vertices.end());
        }
        for (int v = 4; v < 9; ++v)
        {
            EXPECT_TRUE(std::find(comp2_vertices.begin(), comp2_vertices.end(), v) != comp2_vertices.end());
        }
    }
}