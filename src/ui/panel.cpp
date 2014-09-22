#include "ui/panel.h"
#include "point.h"
#include "util/logger.h"

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


void Panel::add_element(UIElement * element)
{
    elements_.push_back(element);
}

void Panel::render(Frame * frame)
{
    if(frame_ != nullptr) {
        frame_->set_parent(frame);
    }
    for(std::vector<UIElement *>::iterator element_iterator = elements_.begin(); element_iterator != elements_.end(); ++element_iterator) {
        (*element_iterator)->render(frame_);
    }
}

void Panel::update()
{
    for(std::vector<UIElement *>::iterator element_iterator = elements_.begin(); element_iterator != elements_.end(); ++element_iterator) {
        (*element_iterator)->update();
    }
}
