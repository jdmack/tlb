#include "level_graph.h"

LevelGraph::LevelGraph()
{

}

LevelGraph::~LevelGraph()
{

}

void LevelGraph::add_node(LevelNode * node)
{
    nodes_.push_back(node);
}
