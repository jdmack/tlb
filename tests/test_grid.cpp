
#include <gtest/gtest.h>
#include "grid.h"
#include "grid_node.h"

TEST(Grid,Basic)
{
    Grid grid(1,1);

    EXPECT_EQ (grid.rows(), 1);
    EXPECT_EQ (grid.columns(), 1);
}

TEST(Grid,Mutate)
{
    Grid grid(3,5);

    EXPECT_EQ (grid.rows(), 3);
    EXPECT_EQ (grid.columns(), 5);

    grid.rows(7);
    EXPECT_EQ (grid.rows(), 7);

    grid.columns(8);
    EXPECT_EQ (grid.columns(), 8);
}

TEST(Grid,Walkable)
{
    Grid grid(10,10);

    for (int r = 0; r < 10; r++)
        for (int c = 0; c < 10; c++)
            EXPECT_TRUE (grid.node(r,c)->walkable());
}

