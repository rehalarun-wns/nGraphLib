#include <gtest/gtest.h>
#include "../directed_graph.h"
#include "../undirected_graph.h"

const std::vector<std::tuple<int, int, double>> edges{
    {1, 2, 1.0},
    {1, 3, 2.5},
    {2, 4, 1.2},
    {2, 5, 2.8},
    {3, 1, 2.0},
    {3, 6, 3.3},
    {4, 2, 4.0},
    {4, 7, 2.1},
    {4, 8, 1.5},
    {5, 6, 0.9},
    {5, 9, 1.6},
    {6, 3, 1.8},
    {6, 10, 2.4},
    {7, 4, 3.3},
    {7, 8, 1.1},
    {7, 11, 2.9},
    {7, 12, 1.7},
    {7, 1, 3.2},
    {8, 5, 2.6},
    {8, 13, 2.2},
    {9, 6, 2.9},
    {9, 14, 1.0},
    {10, 1, 3.7},
    {10, 15, 1.5},
    {10, 16, 2.2},
    {10, 20, 2.2},
    {11, 8, 2.3},
    {11, 17, 1.7},
    {12, 9, 2.1},
    {12, 18, -2.8},
    {13, 10, 1.9},
    {13, 19, 2.6},
    {14, 12, 1.2},
    {14, 20, -2.5},
    {15, 13, 1.8},
    {15, 16, 2.0},
    {15, 17, -1.3},
    {16, 14, 2.7},
    {16, 18, 1.3},
    {17, 15, 2.4},
    {17, 19, 1.6},
    {19, 17, 2.8},
    {19, 20, 1.9},
    {20, 18, 2.5},
    {20, 1, 3.2}};

// Fixture for DirectedGraph<int>
class DirectedGraphIntTest : public ::testing::Test
{
protected:
    DirectedGraph<int> g;

private:
    // Graph structure:
    // 1  -> 2 (1.0), 3 (2.5)
    // 2  -> 4 (1.2), 5 (2.8)
    // 3  -> 1 (2.0), 6 (3.3)
    // 4  -> 2 (4.0), 7 (2.1), 8 (1.5)
    // 5  -> 6 (0.9), 9 (1.6)
    // 6  -> 3 (1.8), 10 (2.4)
    // 7  -> 4 (3.3), 8 (1.1), 11 (2.9), 12 (1.7), 1 (3.2)
    // 8  -> 5 (2.6), 13 (2.2)
    // 9  -> 6 (2.9), 14 (1.0)
    // 10 -> 1 (3.7), 15 (1.5), 16 (2.2), 20 (2.2)
    // 11 -> 8 (2.3), 17 (1.7)
    // 12 -> 9 (2.1), 18 (2.8)
    // 13 -> 10 (1.9), 19 (2.6)
    // 14 -> 12 (1.2), 20 (2.5)
    // 15 -> 13 (1.8), 16 (2.0), 17 (1.3)
    // 16 -> 14 (2.7), 18 (1.3)
    // 17 -> 15 (2.4), 19 (1.6)
    // 18 ->
    // 19 -> 17 (2.8), 20 (1.9)
    // 20 -> 18 (2.5), 1 (3.2), 2 (1.4)
    // Contains 20 vertices and  edges with weights.

    void SetUp() override
    {
        g.AddEdges(edges);
    };

    void TearDown() override
    {
        g.clear();
    }
};

// Fixture for UndirectedGraph<int>
class UndirectedGraphIntTest : public ::testing::Test
{
protected:
    UndirectedGraph<int> g;

private:
    void SetUp() override
    {
        // remove repated reverse edges
        std::vector<std::tuple<int, int, double>> undirected_edges;
        std::set<std::pair<int, int>> seen;
        for (const auto &[from, to, weight] : edges)
        {
            auto edge = std::minmax(from, to);
            if (seen.insert(edge).second)
            {
                undirected_edges.emplace_back(edge.first, edge.second, weight);
            }
        }
        g.AddEdges(undirected_edges);
    };
    void TearDown() override
    {
        g.clear();
    }
};