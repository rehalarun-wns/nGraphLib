#ifndef BFS_H
#define BFS_H

#include <unordered_map>
#include <queue>
#include <vector>
#include <string>

#include "algorithms/abstract_algo.h"

namespace Graph
{
    template <typename GraphT, typename OutputT>
    class BFS : public IAlgorithm<GraphT, std::vector<typename GraphT::VertexTy>>
    {
        static_assert(std::is_same_v<OutputT, std::vector<typename GraphT::VertexTy>>,
                      "BFS output type must be std::vector<VertexTy>");

    public:
        OutputT run(GraphT &graph, typename GraphT::VertexTy start_vertex) override
        {
            OutputT visited_order;
            std::unordered_map<typename GraphT::VertexTy, bool, typename GraphT::HashTy> visited;
            std::queue<typename GraphT::VertexTy> queue;
            queue.push(start_vertex);
            visited[start_vertex] = true;
            while (!queue.empty())
            {
                auto current = queue.front();
                queue.pop();
                visited_order.push_back(current);
                for (const auto &neighbor : graph.GetNeighbors(current))
                {
                    auto neighbor_vertex = neighbor.first;
                    if (!visited[neighbor_vertex])
                    {
                        visited[neighbor_vertex] = true;
                        queue.push(neighbor_vertex);
                    }
                }
            }
            return visited_order;
        }
        std::string name() const override { return "BFS"; }
    };
} // namespace Graph

#endif // DFS_H