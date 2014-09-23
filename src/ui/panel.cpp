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


void Panel::add_element(UIElement * element)
{
    elements_.push_back(element);
}

void Panel::render(Frame * frame)
{
    if(frame_ != nullptr) {
        frame_->set_parent(frame);
    }
    UIElement::render(frame);
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

bool Panel::load_texture(std::string art_asset)
{
    bool load_result = UIElement::load_texture(art_asset);
    frame_ = new Frame(position_.x(), position_.y(), width_, height_);
    return load_result;
}

void Panel::set_position(Point point)
{
    UIElement::set_position(point);
    frame_->set_x(position_.x());
    frame_->set_y(position_.y());
}
