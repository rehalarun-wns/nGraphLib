#ifndef ALGORITHM_FACTORY_H
#define ALGORITHM_FACTORY_H

#include "algorithm_types.h"
#include "algorithms/abstract_algo.h"
#include "algorithms/dfs.h"
#include "algorithms/bfs.h"

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
                return std::make_unique<DFS<GraphT>>();
            case AlgorithmType::BFS_Ty:
                return std::make_unique<BFS<GraphT>>();
            default:
                return nullptr;
            }
        }
    };
}

#endif // ALGORITHM_FACTORY_H
