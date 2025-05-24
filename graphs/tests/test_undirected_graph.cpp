#include <gtest/gtest.h>
#include "../undirected_graph.h"

TEST(UndirectedGraphTest, AddAndCountEdges)
{
    UndirectedGraph<int> g;
    g.AddEdge(1, 2);
    g.AddEdge(2, 3);

    EXPECT_EQ(g.GetNumOfVertices(), 3); // Only vertices with outgoing edges are counted
    EXPECT_EQ(g.GetNumOfEdges(), 2);    // Each undirected edge is stored twice
}

TEST(UndirectedGraphTest, RemoveEdge)
{
    UndirectedGraph<int> g;
    g.AddEdge(1, 2);
    g.RemoveEdge(1, 2);

    EXPECT_EQ(g.GetNumOfEdges(), 0);
}

TEST(UndirectedGraphTest, RemoveVertex)
{
    UndirectedGraph<int> g;
    g.AddEdge(1, 2);
    g.AddEdge(2, 3);
    g.RemoveVertex(2);

    EXPECT_EQ(g.GetNumOfVertices(), 2);
    EXPECT_EQ(g.GetNumOfEdges(), 0);
}