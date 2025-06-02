#ifndef DFS_H
#define DFS_H

#include <unordered_set>
#include <stack>
#include <vector>
#include <string>
#include "algorithms/abstract_algo.h"

namespace Graph
{
    template <typename GraphT, typename OutputT>
    class DFS : public IAlgorithm<GraphT, OutputT>
    {
        static_assert(std::is_same_v<OutputT, std::vector<typename GraphT::VertexTy>>,
                      "DFS output type must be std::vector<VertexTy>");

    public:
        OutputT run(GraphT &graph, typename GraphT::VertexTy start_vertex) override
        {
            OutputT visited_order;
            std::unordered_set<typename GraphT::VertexTy> visited;
            std::stack<typename GraphT::VertexTy> stack;
            stack.push(start_vertex);

            while (!stack.empty())
            {
                auto current = stack.top();
                stack.pop();
                if (visited.count(current))
                    continue;
                visited.insert(current);
                visited_order.push_back(current);
                for (const auto &neighbor : graph.GetNeighbors(current))
                {
                    auto neighbor_vertex = neighbor.first;
                    if (!visited.count(neighbor_vertex))
                    {
                        stack.push(neighbor_vertex);
                    }
                }
            }
            return visited_order;
        }
        std::string name() const override { return "DFS"; }
        std::string output_type() const override { return "std::vector<VertexTy>"; }
    };
}

#endif // DFS_H