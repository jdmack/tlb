
#include <gtest/gtest.h>
#include "grid_node.h"

TEST(GridNode,Basic)
{
    GridNode n(0,0);
    EXPECT_EQ (n.row(), 0);
    EXPECT_EQ (n.column(), 0);

    GridNode n2(1,2);
    EXPECT_EQ (n2.row(), 1);
    EXPECT_EQ (n2.column(), 2);
}

TEST(GridNode,Mutate)
{
    GridNode node(5,7);
    EXPECT_EQ (node.row(), 5);
    EXPECT_EQ (node.column(), 7);

    EXPECT_TRUE (node.walkable());
    node.set_walkable(false);
    EXPECT_FALSE (node.walkable());
    node.set_walkable(true);
    EXPECT_TRUE (node.walkable());
}

