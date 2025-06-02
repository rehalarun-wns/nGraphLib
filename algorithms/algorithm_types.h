#ifndef ALGORITHM_TYPES_H
#define ALGORITHM_TYPES_H

namespace Graph
{
    enum class AlgorithmType
    {
        DFS_Ty,             // Depth-First Search
        BFS_Ty,             // Breadth-First Search
        GetComponents_Ty,   // Get Connected Components
        Collapse1dChains_Ty // Collapse 1D Chains
    };

} // namespace Graph

#endif // ALGORITHM_TYPES_H