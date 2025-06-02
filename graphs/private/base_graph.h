#ifndef _GRAPHBASE_H_
#define _GRAPHBASE_H_

#include <algorithm>
#include <iostream>
#include <execution>
#include <memory_resource>
#include <unordered_map>
#include <optional>
#include <tuple>
#include <vector>

// Base class for Graph representation using an adjacency list.
// Supports both directed and undirected graphs using inheritance.
template <typename _VertexTy, typename _WeightTy = double, typename _Hash = std::hash<_VertexTy>>
class BaseGraph
{
public:
    using VertexTy = _VertexTy;
    using WeightT = _WeightTy;
    using HashTy = _Hash;

protected:
    using MapType =
        std::unordered_map<VertexTy, std::unordered_map<VertexTy, WeightT, HashTy>, HashTy>;

    MapType adjacencyList; // Stores the graph edges
    HashTy hashFunction;

public:
    // Constructor allows optional use of a custom memory resource and dynamically allocates buffer size.
    explicit BaseGraph(size_t estimatedVertices = 100,
                       size_t estimatedEdges = 200,
                       HashTy hashFunc = HashTy{})
        : hashFunction(hashFunc), adjacencyList(MapType(0, hashFunc))
    {
    }

    virtual ~BaseGraph() = default; // Virtual destructor for proper cleanup in derived classes

    // Pure virtual functions to be implemented in derived classes
    virtual void RemoveEdge(const VertexTy &from, const VertexTy &to) = 0;
    virtual void RemoveVertex(const VertexTy &vertex) = 0;
    virtual void AddEdge(const VertexTy &from, const VertexTy &to, std::optional<WeightT> weight = std::nullopt) = 0;
    virtual void AddEdges(const std::vector<std::tuple<VertexTy, VertexTy, WeightT>> &edges) = 0;
    virtual bool IsDirected() const = 0;

    // implemented methods
    [[nodiscard]] std::vector<VertexTy> GetVertices() const
    {
        std::vector<VertexTy> vertices;
        vertices.reserve(adjacencyList.size());
        for (const auto &pair : adjacencyList)
        {
            vertices.push_back(pair.first);
        }
        return vertices;
    }

    [[nodiscard]] size_t GetDegree(const VertexTy &vertex) const
    {
        bool does_exist = adjacencyList.contains(vertex);
        if (!does_exist)
            return 0;
        return adjacencyList.at(vertex).size();
    }

    [[nodiscard]] size_t GetNumOfVertices() const
    {
        return adjacencyList.size();
    }

    [[nodiscard]] size_t GetNumOfDirectedEdges() const
    {
        return std::transform_reduce(std::execution::par_unseq, adjacencyList.begin(), adjacencyList.end(), size_t{0},
                                     std::plus<>(),
                                     [](const auto &pair)
                                     { return pair.second.size(); });
    }

    [[nodiacrd]] WeightT GetEdgeWeight(const VertexTy &from, const VertexTy &to) const
    {
        auto it = adjacencyList.find(from);
        if (it != adjacencyList.end())
        {
            auto edgeIt = it->second.find(to);
            if (edgeIt != it->second.end())
            {
                return edgeIt->second;
            }
        }
        throw std::runtime_error("Edge does not exist");
    }

    [[nodiscard]] std::vector<std::pair<VertexTy, WeightT>> GetNeighbors(const VertexTy &vertex) const
    {
        auto it = adjacencyList.find(vertex);
        if (it != adjacencyList.end())
        {
            std::vector<std::pair<VertexTy, WeightT>> neighbors;
            neighbors.reserve(it->second.size());
            for (const auto &neighbor : it->second)
            {
                neighbors.emplace_back(neighbor.first, neighbor.second);
            }
            return neighbors;
        }
        throw std::runtime_error("Vertex does not exist");
    }

    [[nodiscard]] bool IsEmpty() const
    {
        return adjacencyList.empty();
    }

    // Clears the graph by removing all edges and vertices.
    void clear()
    {
        adjacencyList.clear();
    }

    void print() const
    {
        std::cout << "Graph adjacency list:" << std::endl;
        std::cout << "VERTEX" << ": " << "EDGES" << std::endl;
        std::cout << "------------------------" << std::endl;

        for (const auto &pair : adjacencyList)
        {
            std::cout << pair.first << ": ";
            for (const auto &edge : pair.second)
            {
                std::cout << "[" << edge.first << ", " << edge.second << "] ";
            }
            std::cout << std::endl;
        }
        std::cout << "------------------------" << std::endl;
    }
};

#endif // _GRAPHBASE_H_