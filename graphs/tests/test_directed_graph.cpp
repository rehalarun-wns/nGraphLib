#include <gtest/gtest.h>
#include "../directed_graph.h"

TEST(DirectedGraphTest, AddAndCountVerticesAndEdges)
{
    DirectedGraph<int> g;
    g.AddEdge(1, 2);
    g.AddEdge(2, 3);

    EXPECT_EQ(g.GetNumOfVertices(), 2); // Only vertices with outgoing edges are counted
    EXPECT_EQ(g.GetNumOfEdges(), 2);
}

TEST(DirectedGraphTest, RemoveEdge)
{
    DirectedGraph<int> g;
    g.AddEdge(1, 2);
    g.RemoveEdge(1, 2);

    EXPECT_EQ(g.GetNumOfEdges(), 0);
}

TEST(DirectedGraphTest, RemoveVertex)
{
    DirectedGraph<int> g;
    g.AddEdge(1, 2);
    g.AddEdge(2, 3);
    g.RemoveVertex(2);

    EXPECT_EQ(g.GetNumOfVertices(), 1);
    EXPECT_EQ(g.GetNumOfEdges(), 0);
}