#include "level_node.h"
#include "gfx/graphic.h"

LevelNode::LevelNode()
{
    position_ = Point(0, 0);
    width_ = 0;
    height_ = 0;

    graphic_ = nullptr;
}

void LevelNode::add_adjacent(LevelNode * node)
{
    adjacent_.push_back(node);
}

void LevelNode::render()
{
    if(graphic_ != nullptr) {
        graphic_->render();
    }
}
