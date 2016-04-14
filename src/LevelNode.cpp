#include "LevelNode.h"
#include "gfx/Graphic.h"
#include "Frame.h"


LevelNode::LevelNode()
{
    position_ = Point(0, 0);
    width_ = 0;
    height_ = 0;

    graphic_ = nullptr;
}

void LevelNode::addAdjacent(LevelNode * node)
{
    adjacent_.push_back(node);
}

void LevelNode::render(Frame * frame)
{
    if(graphic_ != nullptr) {
        graphic_->render(frame);
    }
}
