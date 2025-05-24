#ifndef _UNDIRECTED_GRAPH_H_
#define _UNDIRECTED_GRAPH_H_

#include "private/base_graph.h"
#include <optional>
#include <tuple>
#include <vector>

// UndirectedGraph: Inherits from BaseGraph and implements undirected edge logic.
template <typename VertexTy, typename WeightT = double, typename HashTy = std::hash<VertexTy>, bool UsePMR = false>
class UndirectedGraph : public BaseGraph<VertexTy, WeightT, HashTy, UsePMR>
{
    using Base = BaseGraph<VertexTy, WeightT, HashTy, UsePMR>;
    using Base::adjacencyList;
    using Base::hashFunction;

public:
    using Base::Base; // Inherit constructors

    void AddEdge(const VertexTy &from, const VertexTy &to, std::optional<WeightT> weight = std::nullopt) override;
    void AddEdges(const std::vector<std::tuple<VertexTy, VertexTy, WeightT>> &edges) override;
    void RemoveEdge(const VertexTy &from, const VertexTy &to) override;
    void RemoveVertex(const VertexTy &vertex) override;

    [[nodiscard]] size_t GetNumOfEdges() const;
};

// --- Implementation ---
template <typename VertexTy, typename WeightT, typename HashTy, bool UsePMR>
void UndirectedGraph<VertexTy, WeightT, HashTy, UsePMR>::AddEdge(const VertexTy &from, const VertexTy &to, std::optional<WeightT> weight)
{
    if (!weight)
        weight = static_cast<WeightT>(1);
    this->adjacencyList[from][to] = *weight;
    this->adjacencyList[to][from] = *weight; // Add the reverse edge for undirected graph
}

template <typename VertexTy, typename WeightT, typename HashTy, bool UsePMR>
void UndirectedGraph<VertexTy, WeightT, HashTy, UsePMR>::AddEdges(const std::vector<std::tuple<VertexTy, VertexTy, WeightT>> &edges)
{
    for (const auto &[from, to, weight] : edges)
    {
        this->adjacencyList[from][to] = weight;
        this->adjacencyList[to][from] = weight; // Add the reverse edge for undirected graph
    }
}

template <typename VertexTy, typename WeightT, typename HashTy, bool UsePMR>
void UndirectedGraph<VertexTy, WeightT, HashTy, UsePMR>::RemoveEdge(const VertexTy &from, const VertexTy &to)
{
    auto it = this->adjacencyList.find(from);
    if (it != this->adjacencyList.end())
    {
        it->second.erase(to);
        if (it->second.empty())
            this->adjacencyList.erase(it);
    }

    // Remove the reverse edge
    it = this->adjacencyList.find(to);
    if (it != this->adjacencyList.end())
    {
        it->second.erase(from);
        if (it->second.empty())
            this->adjacencyList.erase(it);
    }
}

template <typename VertexTy, typename WeightT, typename HashTy, bool UsePMR>
void UndirectedGraph<VertexTy, WeightT, HashTy, UsePMR>::RemoveVertex(const VertexTy &vertex)
{
    // Remove all edges connected to the vertex
    this->adjacencyList.erase(vertex);

    // Remove all edges from other vertices to this vertex
    for (auto &pair : this->adjacencyList)
    {
        pair.second.erase(vertex);
    }
}

template <typename VertexTy, typename WeightT, typename HashTy, bool UsePMR>
size_t UndirectedGraph<VertexTy, WeightT, HashTy, UsePMR>::GetNumOfEdges() const
{
    size_t num_of_directed_edges = this->GetNumOfDirectedEdges();
    assert(num_of_directed_edges % 2 == 0);
    return num_of_directed_edges / 2.0;
}

#endif // _UNDIRECTED_GRAPH_H_