#include <gtest/gtest.h>
#include "../directed_graph.h"

// Fixture for DirectedGraph<int>
class DirectedGraphIntTest : public ::testing::Test
{
protected:
    DirectedGraph<int> g;

    void SetUp() override
    {
        // Optional: common setup for each test
    }

    void TearDown() override
    {
        // Optional: cleanup after each test
    }
};

TEST_F(DirectedGraphIntTest, AddAndCountVerticesAndEdges)
{
    g.AddEdge(1, 2);
    g.AddEdge(2, 3);

    EXPECT_EQ(g.GetNumOfVertices(), 2); // Only vertices with outgoing edges are counted
    EXPECT_EQ(g.GetNumOfEdges(), 2);
}

TEST_F(DirectedGraphIntTest, RemoveEdge)
{
    g.AddEdge(1, 2);
    g.RemoveEdge(1, 2);

    EXPECT_EQ(g.GetNumOfEdges(), 0);
}

TEST_F(DirectedGraphIntTest, RemoveVertex)
{
    g.AddEdge(1, 2);
    g.AddEdge(2, 3);
    g.RemoveVertex(2);

    EXPECT_EQ(g.GetNumOfVertices(), 1);
    EXPECT_EQ(g.GetNumOfEdges(), 0);
}

// Parameterized test for edge addition
struct EdgeParam
{
    int from;
    int to;
};

class DirectedGraphParamTest : public ::testing::TestWithParam<EdgeParam>
{
};

TEST_P(DirectedGraphParamTest, AddSingleEdge)
{
    DirectedGraph<int> g;
    auto param = GetParam();
    g.AddEdge(param.from, param.to);

    EXPECT_EQ(g.GetNumOfVertices(), 1);
    EXPECT_EQ(g.GetNumOfEdges(), 1);
}

INSTANTIATE_TEST_SUITE_P(
    EdgeCases,
    DirectedGraphParamTest,
    ::testing::Values(
        EdgeParam{1, 2},
        EdgeParam{2, 3},
        EdgeParam{-1, 0},
        EdgeParam{100, 200}));