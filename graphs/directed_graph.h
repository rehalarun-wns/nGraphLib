#ifndef _DIRECTED_GRAPH_H_
#define _DIRECTED_GRAPH_H_

#include "private/base_graph.h"
#include <optional>
#include <tuple>
#include <vector>

// DirectedGraph: Inherits from BaseGraph and implements directed edge logic.
template <typename VertexTy, typename WeightT = double, typename HashTy = std::hash<VertexTy>, bool UsePMR = false>
class DirectedGraph : public BaseGraph<VertexTy, WeightT, HashTy, UsePMR>
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
void DirectedGraph<VertexTy, WeightT, HashTy, UsePMR>::AddEdge(const VertexTy &from, const VertexTy &to, std::optional<WeightT> weight)
{
    if (!weight)
        weight = static_cast<WeightT>(1);
    this->adjacencyList[from][to] = *weight;
}

template <typename VertexTy, typename WeightT, typename HashTy, bool UsePMR>
void DirectedGraph<VertexTy, WeightT, HashTy, UsePMR>::AddEdges(const std::vector<std::tuple<VertexTy, VertexTy, WeightT>> &edges)
{
    for (const auto &[from, to, weight] : edges)
    {
        this->adjacencyList[from][to] = weight;
    }
}

template <typename VertexTy, typename WeightT, typename HashTy, bool UsePMR>
void DirectedGraph<VertexTy, WeightT, HashTy, UsePMR>::RemoveEdge(const VertexTy &from, const VertexTy &to)
{
    auto it = this->adjacencyList.find(from);
    if (it != this->adjacencyList.end())
    {
        it->second.erase(to);
        if (it->second.empty())
            this->adjacencyList.erase(it);
    }
}

template <typename VertexTy, typename WeightT, typename HashTy, bool UsePMR>
void DirectedGraph<VertexTy, WeightT, HashTy, UsePMR>::RemoveVertex(const VertexTy &vertex)
{
    // Remove all outgoing edges
    this->adjacencyList.erase(vertex);

    // Remove all incoming edges
    for (auto &pair : this->adjacencyList)
    {
        pair.second.erase(vertex);
    }
}

template <typename VertexTy, typename WeightT, typename HashTy, bool UsePMR>
size_t DirectedGraph<VertexTy, WeightT, HashTy, UsePMR>::GetNumOfEdges() const
{
    return this->GetNumOfDirectedEdges();
}

#endif // _DIRECTED_GRAPH_H_