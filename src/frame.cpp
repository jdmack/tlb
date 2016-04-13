#include "frame.h"
#include <string>
#include <sstream>


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
    x_      = x;
    y_      = y;
    width_  = width;
    height_ = height;
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

bool Frame::containsPoint(double x, double y)
{
    if((x < (x_- (width_ / 2))) || (x > (x_+ (width_ / 2)))) {
        return false;
    }
    else if((y < (y_- (width_ / 2))) || (y > (y_+ (height_ / 2)))) {
        return false;
    }

    return true;
}

std::string Frame::toString()
{
    std::stringstream ss;
    ss << "Frame(" << x_ << "," << y_ << "," << width_ << "," << height_ << ")";
    return ss.str();
}
