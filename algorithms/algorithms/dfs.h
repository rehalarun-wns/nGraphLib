#ifndef DFS_H
#define DFS_H

#include <unordered_set>
#include <stack>
#include <iostream>

#include "algorithms/abstract_algo.h"

namespace Graph
{
    template <typename GraphT>
    class DFS : public IAlgorithm<GraphT, std::vector<typename GraphT::VertexTy>>
    {
    public:
        using OutputT = std::vector<typename GraphT::VertexTy>;
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
                    if (!visited.count(neighbor))
                    {
                        stack.push(neighbor);
                    }
                }
            }
            return visited_order;
        }
        std::string name() const override { return "DFS"; }
    };
}

#endif // DFS_H