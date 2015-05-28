#include "level_node.h"

LevelNode::LevelNode()
{

}

void LevelNode::add_adjacent(LevelNode * node)
{
    adjacent_.push_back(node);
}
