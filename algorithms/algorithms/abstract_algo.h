#ifndef ABSTRACT_ALGORITHM_H
#define ABSTRACT_ALGORITHM_H
#include <string>

namespace Graph
{
    template <typename GraphT, typename OutputT>
    class IAlgorithm
    {
    public:
        virtual ~IAlgorithm() = default;
        virtual OutputT run(GraphT &graph, typename GraphT::VertexTy start_vertex) = 0;
        virtual std::string name() const = 0;
    };
} // namespace nGraphAlgo

#endif // ABSTRACT_ALGORITHM_H