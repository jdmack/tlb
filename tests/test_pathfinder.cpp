
#include <gtest/gtest.h>
#include "pathfinder.h"
#include "grid.h"
#include "grid_node.h"

TEST(Pathfinder,Basic)
{

    Grid grid(1,1);
    Pathfinder pathfinder(&grid);

    GridNode * start_node = grid.node(0,0);
    GridNode * end_node = grid.node(0,0);

    std::list<GridNode *> * moves;
    moves = pathfinder.run(start_node, end_node);

}

TEST(Pathfinder,Path)
{

    Grid grid(3,3);
    Pathfinder pathfinder(&grid);

    for (int r = 0; r < 3; r++)
        for (int c = 0; c < 3; c++)
            EXPECT_TRUE (grid.node(r,c)->walkable());

    GridNode * start_node = grid.node(0,0);
    GridNode * end_node = grid.node(2,0);

    std::list<GridNode *> * moves;
    moves = pathfinder.run(start_node, end_node);
    EXPECT_EQ (moves->size(), 3);

}

TEST(Pathfinder,DiagPath)
{

    Grid grid(3,3);
    Pathfinder pathfinder(&grid);

    for (int r = 0; r < 3; r++)
        for (int c = 0; c < 3; c++)
            EXPECT_TRUE (grid.node(r,c)->walkable());

    GridNode * start_node = grid.node(0,0);
    GridNode * end_node = grid.node(2,2);

    std::list<GridNode *> * moves;
    moves = pathfinder.run(start_node, end_node);
    EXPECT_EQ (moves->size(), 3);

}

