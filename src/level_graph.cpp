#include "level_graph.h"
#include "level_node.h"

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

void LevelGraph::render()
{
    for(std::list<LevelNode *>::iterator it = nodes_.begin(); it != nodes_.end(); ++it) {
        (*it)->render();
    }
}
