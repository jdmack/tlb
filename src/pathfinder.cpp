
#include <list>

#include "pathfinder.h"
#include "grid_node.h"

Pathfinder::Pathfinder()
{
}

std::list<GridNode *> * Pathfinder::run(GridNode * start_node, GridNode * end_node)
{
    return new std::list<GridNode *>();
}

Pathfinder::~Pathfinder()
{

}
