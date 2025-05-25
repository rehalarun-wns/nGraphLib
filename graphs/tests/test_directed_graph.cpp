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
    g.RemoveEdge(1, 2); // Should not crash or throw
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
    g.RemoveVertex(1); // Should not crash or throw
    EXPECT_EQ(g.GetNumOfVertices(), 0);
    EXPECT_EQ(g.GetNumOfEdges(), 0);
}

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