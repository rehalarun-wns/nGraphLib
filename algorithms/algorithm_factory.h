#ifndef ALGORITHM_FACTORY_H
#define ALGORITHM_FACTORY_H

#include "algorithm_types.h"
#include "algorithms/abstract_algo.h"
#include "algorithms/dfs.h"
#include "algorithms/bfs.h"
#include "algorithms/components.h"
#include <type_traits>

namespace Graph
{
    template <typename GraphT, typename OutputT>
    class AlgorithmFactory
    {
    public:
        static std::unique_ptr<IAlgorithm<GraphT, OutputT>> create(AlgorithmType type)
        {
            switch (type)
            {
            case AlgorithmType::DFS_Ty:
                if constexpr (std::is_same_v<OutputT, std::vector<typename GraphT::VertexTy>>)
                {
                    return std::make_unique<DFS<GraphT, OutputT>>();
                }
                else
                {
                    return nullptr;
                }
            case AlgorithmType::BFS_Ty:
                if constexpr (std::is_same_v<OutputT, std::vector<typename GraphT::VertexTy>>)
                {
                    return std::make_unique<BFS<GraphT, OutputT>>();
                }
                else
                {
                    return nullptr;
                }
            case AlgorithmType::GetComponents_Ty:
                if constexpr (std::is_same_v<OutputT, std::vector<GraphT>>)
                {
                    return std::make_unique<GetComponents<GraphT, OutputT>>();
                }
                else
                {
                    return nullptr;
                }
            default:
                return nullptr;
            }
        }
    };
}

#endif // ALGORITHM_FACTORY_H