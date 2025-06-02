#ifndef ALGORITHM_FACTORY_H
#define ALGORITHM_FACTORY_H

#include "algorithm_types.h"
#include "algorithms/abstract_algo.h"
#include "algorithms/dfs.h"
#include "algorithms/bfs.h"
#include "algorithms/components.h"
#include <type_traits>
#include <memory>

namespace Graph
{
    // Traits to map AlgorithmType to output type
    template <typename GraphT, AlgorithmType AlgoTy>
    struct AlgorithmOutputType;

    template <typename GraphT>
    struct AlgorithmOutputType<GraphT, AlgorithmType::DFS_Ty>
    {
        using type = std::vector<typename GraphT::VertexTy>;
    };

    template <typename GraphT>
    struct AlgorithmOutputType<GraphT, AlgorithmType::BFS_Ty>
    {
        using type = std::vector<typename GraphT::VertexTy>;
    };

    template <typename GraphT>
    struct AlgorithmOutputType<GraphT, AlgorithmType::GetComponents_Ty>
    {
        using type = std::vector<GraphT>;
    };

    template <typename GraphT, AlgorithmType type>
    class AlgorithmFactory
    {
    public:
        using OutputT = typename AlgorithmOutputType<GraphT, type>::type;

        static std::unique_ptr<IAlgorithm<GraphT, OutputT>> create()
        {
            if constexpr (type == AlgorithmType::DFS_Ty)
            {
                return std::make_unique<DFS<GraphT, OutputT>>();
            }
            else if constexpr (type == AlgorithmType::BFS_Ty)
            {
                return std::make_unique<BFS<GraphT, OutputT>>();
            }
            else if constexpr (type == AlgorithmType::GetComponents_Ty)
            {
                return std::make_unique<GetComponents<GraphT, OutputT>>();
            }
            else
            {
                return nullptr;
            }
        }
    };
}

#endif // ALGORITHM_FACTORY_H