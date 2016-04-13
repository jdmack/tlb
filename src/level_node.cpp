#include "levelNode.h"
#include "gfx/graphic.h"
#include "frame.h"


LevelNode::LevelNode()
{
    position_ = Point(0, 0);
    width_ = 0;
    height_ = 0;

    graphic_ = nullptr;
}

void LevelNode::addAdjacent(LevelNode * node)
{
    adjacent_.pushBack(node);
}

void LevelNode::render(Frame * frame)
{
    if(graphic_ != nullptr) {
        graphic_->render(frame);
    }
}
