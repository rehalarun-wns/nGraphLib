#include "fixtures.h"
#include "params.h"

TEST_F(DirectedGraphIntTest, CountVertices)
{
    EXPECT_EQ(g.GetNumOfVertices(), 20);
}

TEST_F(DirectedGraphIntTest, CountEdges)
{
    EXPECT_EQ(g.GetNumOfEdges(), 45);
}

TEST_F(DirectedGraphIntTest, RemoveEdge)
{
    g.RemoveEdge(1, 2);
    EXPECT_EQ(g.GetNumOfEdges(), 44);
    g.RemoveEdge(1, 3);
    EXPECT_EQ(g.GetNumOfEdges(), 43);
    g.RemoveEdge(3, 1);
    EXPECT_EQ(g.GetNumOfEdges(), 42);
}

TEST(EmptyGraphOperation, RemoveEdgeFromEmptyGraph)
{
    DirectedGraph<int> g;
    EXPECT_THROW(g.RemoveEdge(1, 2), std::runtime_error);
    EXPECT_EQ(g.GetNumOfVertices(), 0);
    EXPECT_EQ(g.GetNumOfEdges(), 0);
}

TEST_F(DirectedGraphIntTest, RemoveVertex)
{
    g.RemoveVertex(2);
    EXPECT_EQ(g.GetNumOfVertices(), 19);
    EXPECT_EQ(g.GetNumOfEdges(), 41);
    g.RemoveVertex(1);
    EXPECT_EQ(g.GetNumOfVertices(), 18);
    EXPECT_EQ(g.GetNumOfEdges(), 36);
}

TEST_F(DirectedGraphIntTest, RemoveVertexFromEmptyGraph)
{
    DirectedGraph<int> g;
    EXPECT_THROW(g.RemoveVertex(1), std::runtime_error);
    EXPECT_EQ(g.GetNumOfVertices(), 0);
    EXPECT_EQ(g.GetNumOfEdges(), 0);
}

struct EdgeWeightParam
{
    int from;
    int to;
    double expected_weight;
    bool expect_throw;
};

class DirectedGraphEdgeWeightTest : public DirectedGraphIntTest, public ::testing::WithParamInterface<EdgeWeightParam>
{
};

TEST_P(DirectedGraphEdgeWeightTest, GetEdgeWeight)
{
    const auto &param = GetParam();
    if (param.expect_throw)
    {
        EXPECT_THROW(g.GetEdgeWeight(param.from, param.to), std::runtime_error);
    }
    else
    {
        EXPECT_EQ(g.GetEdgeWeight(param.from, param.to), param.expected_weight);
    }
}

INSTANTIATE_TEST_SUITE_P(
    EdgeWeightCases,
    DirectedGraphEdgeWeightTest,
    ::testing::Values(
        EdgeWeightParam{1, 2, 1.0, false},
        EdgeWeightParam{3, 1, 2.0, false},
        EdgeWeightParam{1, 3, 2.5, false},
        EdgeWeightParam{2, 4, 1.2, false},
        EdgeWeightParam{12, 18, -2.8, false},
        EdgeWeightParam{8, 20, 0.0, true}, // Edge does not exist
        EdgeWeightParam{18, 1, 0.0, true}  // Edge does not exist
        ));

TEST(AddTests, AddEdge)
{
    DirectedGraph<int> g;
    g.AddEdge(1, 2, 1.0);
    EXPECT_EQ(g.GetNumOfVertices(), 2);
    EXPECT_EQ(g.GetNumOfEdges(), 1);
    g.AddEdge(2, 3, 2.5);
    EXPECT_EQ(g.GetNumOfVertices(), 3);
    EXPECT_EQ(g.GetNumOfEdges(), 2);
}

TEST_P(DirectedGraphParamTest, AddSingleEdge)
{
    DirectedGraph<int> g;
    auto param = GetParam();
    g.AddEdge(param.from, param.to, 1.0);
    EXPECT_EQ(g.GetNumOfVertices(), 2);
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