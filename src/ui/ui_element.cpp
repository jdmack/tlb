#include "ui/ui_element.h"
#include "point.h"
#include "util/logger.h"

UIElement::UIElement()
{
    position_ = Point(0, 0);
    width_ = 0;
    height_ = 0;
    visible_ = true;

    texture_ = nullptr;
}

UIElement::~UIElement()
{
    SDL_DestroyTexture(texture_);
}


void UIElement::render(Frame * frame)
{

}

bool UIElement::toggle()
{
    visible_ = !visible_;
    return visible_;
}

void UIElement::update()
{

}

