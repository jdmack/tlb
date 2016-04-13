#include <vector>
#include "ui/panel.h"
#include "point.h"
#include "util/logger.h"
#include "frame.h"

Panel::Panel()
{
    position_ = Point(0, 0);
    width_ = 0;
    height_ = 0;

    texture_ = nullptr;
    visible_ = true;
    frame_ = nullptr;
}

Panel::~Panel()
{
    SDL_DestroyTexture(texture_);
}


void Panel::addElement(UIElement * element)
{
    elements_.pushBack(element);
}

void Panel::render(Frame * frame)
{
    if(frame_ != nullptr) {
        frame_->setParent(frame);
    }
    UIElement::render(frame);
    for(std::vector<UIElement *>::iterator elementIterator = elements_.begin(); elementIterator != elements_.end(); ++elementIterator) {
        (*elementIterator)->render(frame_);
    }
}

void Panel::update()
{
    for(std::vector<UIElement *>::iterator elementIterator = elements_.begin(); elementIterator != elements_.end(); ++elementIterator) {
        (*elementIterator)->update();
    }
}

bool Panel::loadTexture(std::string artAsset)
{
    bool loadResult = UIElement::loadTexture(artAsset);
    frame_ = new Frame(position_.x(), position_.y(), width_, height_);
    return loadResult;
}

void Panel::setPosition(Point point)
{
    UIElement::setPosition(point);
    frame_->setX(position_.x());
    frame_->setY(position_.y());
}
