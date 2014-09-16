#include "frame.h"

Frame::Frame(Frame * parent)
{
    x_      = 0;
    y_      = 0;
    width_  = 0;
    height_ = 0;
    parent_ = parent;
}

Frame::Frame(int x, int y, int width, int height, Frame * parent)
{
    x_      = 0;
    y_      = 0;
    width_  = 0;
    height_ = 0;
    parent_ = parent;
}

int Frame::x() const
{
    if(parent_ != nullptr) {
        return x_ + parent_->x();
    }
    else {
        return x_;
    }
}

int Frame::y() const
{
    if(parent_ != nullptr) {
        return y_ + parent_->y();
    }
    else {
        return y_;
    }

}
