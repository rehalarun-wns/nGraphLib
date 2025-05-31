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
template <typename _VertexTy, typename _WeightTy = double, typename _Hash = std::hash<_VertexTy>, bool _UsePMR = false>
class BaseGraph
{
public:
    using VertexTy = _VertexTy;
    using WeightT = _WeightTy;
    using HashTy = _Hash;

protected:
    // Define the adjacency list type based on whether a polymorphic memory resource (PMR) is used.
    using MapType = std::conditional_t<
        _UsePMR,
        std::pmr::unordered_map<VertexTy, std::pmr::unordered_map<VertexTy, WeightT, HashTy>, HashTy>,
        std::unordered_map<VertexTy, std::unordered_map<VertexTy, WeightT, HashTy>, HashTy>>;

    MapType adjacencyList;                              // Stores the graph edges
    std::pmr::monotonic_buffer_resource bufferResource; // Adaptive buffer for PMR allocation
    HashTy hashFunction;

public:
    // Constructor allows optional use of a custom memory resource and dynamically allocates buffer size.
    explicit BaseGraph(size_t estimatedVertices = 100,
                       size_t estimatedEdges = 200,
                       std::pmr::memory_resource *resource = std::pmr::get_default_resource(),
                       HashTy hashFunc = HashTy{})
        : bufferResource(estimatedVertices * sizeof(VertexTy) + estimatedEdges * sizeof(WeightT)),
          hashFunction(hashFunc)
    {
        if constexpr (_UsePMR)
        {
            adjacencyList = MapType(0, hashFunc, resource ? resource : std::pmr::get_default_resource());
        }
        else
        {
            adjacencyList = MapType(0, hashFunc);
        }
    }

    virtual ~BaseGraph() = default; // Virtual destructor for proper cleanup in derived classes

    // Pure virtual functions to be implemented in derived classes
    virtual void RemoveEdge(const VertexTy &from, const VertexTy &to) = 0;
    virtual void RemoveVertex(const VertexTy &vertex) = 0;
    virtual void AddEdge(const VertexTy &from, const VertexTy &to, std::optional<WeightT> weight = std::nullopt) = 0;
    virtual void AddEdges(const std::vector<std::tuple<VertexTy, VertexTy, WeightT>> &edges) = 0;

    // implemented methods
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

    [[nodiscard]] std::vector<VertexTy> GetNeighbors(const VertexTy &vertex) const
    {
        auto it = adjacencyList.find(vertex);
        if (it != adjacencyList.end())
        {
            std::vector<VertexTy> neighbors;
            neighbors.reserve(it->second.size());
            for (const auto &neighbor : it->second)
            {
                neighbors.push_back(neighbor.first);
            }
            return neighbors;
        }
        throw std::runtime_error("Vertex does not exist");
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