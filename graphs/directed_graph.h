#ifndef _DIRECTED_GRAPH_H_
#define _DIRECTED_GRAPH_H_

#include "private/base_graph.h"
#include <optional>
#include <tuple>
#include <vector>

// DirectedGraph: Inherits from BaseGraph and implements directed edge logic.
template <typename VertexTy,
          typename WeightT = double,
          typename HashTy = std::hash<VertexTy>>
class DirectedGraph : public BaseGraph<VertexTy, WeightT, HashTy>
{
    using Base = BaseGraph<VertexTy, WeightT, HashTy>;
    using Base::adjacencyList;
    using Base::hashFunction;

public:
    using Base::Base; // Inherit constructors
    void AddEdge(const VertexTy &from,
                 const VertexTy &to,
                 std::optional<WeightT> weight = std::nullopt) override;

    void AddEdges(const std::vector<std::tuple<VertexTy, VertexTy, WeightT>> &edges) override;
    void RemoveEdge(const VertexTy &from, const VertexTy &to) override;
    void RemoveVertex(const VertexTy &vertex) override;
    [[nodiscard]] size_t GetNumOfEdges() const;

    [[nodiscard]] bool IsDirected() const override { return true; }
};

// --- Implementation ---

template <typename VertexTy, typename WeightT, typename HashTy>
void DirectedGraph<VertexTy, WeightT, HashTy>::AddEdge(const VertexTy &from,
                                                       const VertexTy &to,
                                                       std::optional<WeightT> weight)
{
    if (!weight)
        weight = static_cast<WeightT>(1);
    this->adjacencyList[from][to] = *weight;
    // insert an empty map for 'to' if it doesn't exist
    if (!this->adjacencyList.contains(to))
    {
        this->adjacencyList[to] = {};
    }
}

template <typename VertexTy, typename WeightT, typename HashTy>
void DirectedGraph<VertexTy, WeightT, HashTy>::AddEdges(
    const std::vector<std::tuple<VertexTy, VertexTy, WeightT>> &edges)
{
    for (const auto &[from, to, weight] : edges)
    {
        this->AddEdge(from, to, weight);
    }
}

template <typename VertexTy, typename WeightT, typename HashTy>
void DirectedGraph<VertexTy, WeightT, HashTy>::RemoveEdge(const VertexTy &from,
                                                          const VertexTy &to)
{
    auto it = this->adjacencyList.find(from);
    if (it != this->adjacencyList.end())
    {
        it->second.erase(to);
        if (it->second.empty())
            this->adjacencyList.erase(it);
    }
    else
    {
        throw std::runtime_error("Edge does not exist");
    }
}

template <typename VertexTy, typename WeightT, typename HashTy>
void DirectedGraph<VertexTy, WeightT, HashTy>::RemoveVertex(const VertexTy &vertex)
{
    // Check if the vertex exists
    const auto does_vertex_exist = this->adjacencyList.contains(vertex);
    if (!does_vertex_exist)
        throw std::runtime_error("Vertex does not exist");

    // Remove all outgoing edges
    this->adjacencyList.erase(vertex);

    // Remove all incoming edges
    for (auto &pair : this->adjacencyList)
    {
        if (pair.second.contains(vertex))
            pair.second.erase(vertex);
    }
}

template <typename VertexTy, typename WeightT, typename HashTy>
size_t DirectedGraph<VertexTy, WeightT, HashTy>::GetNumOfEdges() const
{
    return this->GetNumOfDirectedEdges();
}

#endif // _DIRECTED_GRAPH_H_