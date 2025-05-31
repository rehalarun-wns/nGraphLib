#ifndef BFS_H
#define BFS_H

#include <unordered_set>
#include <queue>
#include <vector>
#include <string>

#include "algorithms/abstract_algo.h"

namespace Graph
{
    template <typename GraphT>
    class BFS : public IAlgorithm<GraphT, std::vector<typename GraphT::VertexTy>>
    {
    public:
        using OutputT = std::vector<typename GraphT::VertexTy>;
        OutputT run(GraphT &graph, typename GraphT::VertexTy start_vertex) override
        {
            OutputT visited_order;
            std::unordered_set<typename GraphT::VertexTy> visited;
            std::queue<typename GraphT::VertexTy> queue;
            queue.push(start_vertex);
            visited.insert(start_vertex);
            while (!queue.empty())
            {
                auto current = queue.front();
                queue.pop();
                visited_order.push_back(current);
                for (const auto &neighbor : graph.GetNeighbors(current))
                {
                    if (!visited.count(neighbor))
                    {
                        visited.insert(neighbor);
                        queue.push(neighbor);
                    }
                }
            }
            return visited_order;
        }
        std::string name() const override { return "BFS"; }
    };
} // namespace Graph

#endif // DFS_H