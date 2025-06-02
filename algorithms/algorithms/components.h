#ifndef COMPONENTS_H
#define COMPONENTS_H

#include <vector>
#include <unordered_map>
#include <stack>
#include "algorithms/abstract_algo.h"

namespace Graph
{
    template <typename GraphT, typename OutputT>
    class GetComponents : public IAlgorithm<GraphT, OutputT>
    {
        static_assert(std::is_same_v<OutputT, std::vector<GraphT>>,
                      "GetComponents output type must be std::vector<GraphT>");

    public:
        OutputT run(GraphT &graph, typename GraphT::VertexTy start_vertex) override
        {
            if (graph.IsDirected())
                throw std::runtime_error("GetComponents algorithm is not applicable for directed graphs.");

            OutputT components;
            const unsigned num_vertices = graph.GetNumOfVertices();
            if (num_vertices == 0)
                return components; // Return empty components if graph is empty

            const std::vector<typename GraphT::VertexTy> vertices = graph.GetVertices();
            std::unordered_map<typename GraphT::VertexTy, bool, typename GraphT::HashTy> visited;
            std::unordered_map<typename GraphT::VertexTy, bool, typename GraphT::HashTy> not_visited;
            bool contains_start = false;
            for (const auto &vertex : vertices)
            {
                if (vertex == start_vertex)
                    contains_start = true;
                visited[vertex] = false;
                not_visited[vertex] = true; // Initialize all vertices as not visited
            }
            if (!contains_start)
                throw std::runtime_error("Start vertex does not exist in the graph.");

            while (not_visited.size() > 0)
            {
                GraphT component;
                std::stack<typename GraphT::VertexTy> stack;
                stack.push(start_vertex);

                while (!stack.empty())
                {
                    auto current = stack.top();
                    stack.pop();
                    if (visited[current])
                        continue;
                    visited[current] = true;
                    not_visited.erase(current);
                    const auto neighbors = graph.GetNeighbors(current);
                    for (const auto &neighbor : neighbors)
                    {
                        if (!visited[neighbor.first])
                        {
                            component.AddEdge(current, neighbor.first, neighbor.second);
                            stack.push(neighbor.first);
                        }
                    }
                }
                if (not_visited.size() > 0)
                    start_vertex = not_visited.begin()->first; // Get a new start vertex from not_visited
                components.push_back(std::move(component));
            }
            return components;
        }
        std::string name() const override { return "GetComponents"; }
        std::string output_type() const override { return "std::vector<GraphT>"; }
    };

} // namespace Graph

#endif // COMPONENTS_H