#ifndef _UNDIRECTED_GRAPH_H_
#define _UNDIRECTED_GRAPH_H_

#include "private/base_graph.h"
#include <optional>
#include <tuple>
#include <vector>

// UndirectedGraph: Inherits from BaseGraph and implements undirected edge logic.
template <typename VertexTy, typename WeightT = double, typename HashTy = std::hash<VertexTy>>
class UndirectedGraph : public BaseGraph<VertexTy, WeightT, HashTy>
{
    using Base = BaseGraph<VertexTy, WeightT, HashTy>;
    using Base::adjacencyList;
    using Base::hashFunction;

public:
    using Base::Base; // Inherit constructors

    void AddEdge(const VertexTy &from, const VertexTy &to, std::optional<WeightT> weight = std::nullopt) override;
    void AddEdges(const std::vector<std::tuple<VertexTy, VertexTy, WeightT>> &edges) override;
    void RemoveEdge(const VertexTy &from, const VertexTy &to) override;
    void RemoveVertex(const VertexTy &vertex) override;
    [[nodiscard]] size_t GetNumOfEdges() const;

    [[nodiscard]] bool IsDirected() const override { return false; }
};

// --- Implementation ---
template <typename VertexTy, typename WeightT, typename HashTy>
void UndirectedGraph<VertexTy, WeightT, HashTy>::AddEdge(const VertexTy &from, const VertexTy &to, std::optional<WeightT> weight)
{
    if (!weight)
        weight = static_cast<WeightT>(1);
    this->adjacencyList[from][to] = *weight;
    this->adjacencyList[to][from] = *weight; // Add the reverse edge for undirected graph
}

template <typename VertexTy, typename WeightT, typename HashTy>
void UndirectedGraph<VertexTy, WeightT, HashTy>::AddEdges(const std::vector<std::tuple<VertexTy, VertexTy, WeightT>> &edges)
{
    for (const auto &[from, to, weight] : edges)
    {
        this->adjacencyList[from][to] = weight;
        this->adjacencyList[to][from] = weight; // Add the reverse edge for undirected graph
    }
}

template <typename VertexTy, typename WeightT, typename HashTy>
void UndirectedGraph<VertexTy, WeightT, HashTy>::RemoveEdge(const VertexTy &from, const VertexTy &to)
{
    auto it_from = this->adjacencyList.find(from);
    if (it_from == this->adjacencyList.end() || it_from->second.find(to) == it_from->second.end())
        throw std::runtime_error("Edge does not exist between 'from' and 'to'.");

    auto it_to = this->adjacencyList.find(to);
    if (it_to == this->adjacencyList.end() || it_to->second.find(from) == it_to->second.end())
        throw std::runtime_error("Reverse edge does not exist between 'to' and 'from'.");

    // Remove the edge from 'from' to 'to'
    it_from->second.erase(to);
    if (it_from->second.empty())
        this->adjacencyList.erase(it_from);

    // Remove the reverse edge from 'to' to 'from'
    it_to->second.erase(from);
    if (it_to->second.empty())
        this->adjacencyList.erase(it_to);
}

template <typename VertexTy, typename WeightT, typename HashTy>
void UndirectedGraph<VertexTy, WeightT, HashTy>::RemoveVertex(const VertexTy &vertex)
{
    const auto does_vertex_exist = this->adjacencyList.contains(vertex);
    if (!does_vertex_exist)
        throw std::runtime_error("Vertex does not exist in the graph.");

    // Remove all edges connected to the vertex
    this->adjacencyList.erase(vertex);

    // Remove all edges from other vertices to this vertex
    for (auto &pair : this->adjacencyList)
    {
        if (pair.second.contains(vertex))
            pair.second.erase(vertex);
    }
}

template <typename VertexTy, typename WeightT, typename HashTy>
size_t UndirectedGraph<VertexTy, WeightT, HashTy>::GetNumOfEdges() const
{
    size_t num_of_directed_edges = this->GetNumOfDirectedEdges();
    if (num_of_directed_edges % 2 != 0)
        throw std::runtime_error("The number of directed edges is not even, indicating an inconsistency in the undirected graph.");
    return size_t(num_of_directed_edges / 2.0); // Each undirected edge is counted twice
}

#endif // _UNDIRECTED_GRAPH_H_