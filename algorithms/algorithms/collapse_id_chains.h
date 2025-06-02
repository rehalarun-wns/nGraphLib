#ifndef COLLAPSE_1D_CHAINS_H
#define COLLAPSE_1D_CHAINS_H

#include "algorithms/abstract_algo.h"

namespace Graph
{
    template <typename GraphT, typename OutputT>
    class Collapse1dChains : public IAlgorithm<GraphT, OutputT>
    {
        static_assert(std::is_same_v<OutputT, GraphT>,
                      "Collapse1dChains output type must be 'Graph Type'");

    public:
        OutputT run(GraphT &graph, typename GraphT::VertexTy start_vertex) override
        {
            if (graph.IsDirected())
                throw std::runtime_error("Collapse1dChains algorithm is not applicable for directed graphs.");
            if (graph.IsEmpty())
                return graph; // Return empty graph if it is empty

            GraphT collapsed_graph;
            std::vector<typename GraphT::VertexTy> heigher_degree_vertices;
            for (const auto &vertex : graph.GetVertices())
            {
                if (graph.GetDegree(vertex) > 2)
                    heigher_degree_vertices.push_back(vertex);
            }
            if (heigher_degree_vertices.empty())
            {

                return graph;
            }
        }
        std::string name() const override { return "GetComponents"; }
        std::string output_type() const override { return "GraphT"; }
    };

} // namespace Graph

#endif // COMPONENTS_H