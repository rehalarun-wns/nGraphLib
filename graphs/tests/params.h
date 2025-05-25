#ifndef _GRAPHS_TESTS_PARAMS_H_
#include <gtest/gtest.h>

// Parameterized test for edge addition
struct EdgeParam
{
    int from;
    int to;
};

class DirectedGraphParamTest : public ::testing::TestWithParam<EdgeParam>
{
};

class UndirectedGraphParamTest : public ::testing::TestWithParam<EdgeParam>
{
};

#endif // _GRAPHS_TESTS_PARAMS_H_