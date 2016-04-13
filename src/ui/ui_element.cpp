#include "SDL2/SDL.h"
#include "ui/uiElement.h"
#include "point.h"
#include "util/logger.h"
#include "gfx/renderer.h"
#include "game.h"


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
    Renderer * renderer = Game::instance()->renderer();
    SDL_Rect offset = { position_.x(), position_.y(), width_, height_ };
    renderer->renderTextureFrame(texture_, frame, &offset);
}

bool UIElement::toggle()
{
    visible_ = !visible_;
    return visible_;
}

void UIElement::update()
{

}

bool UIElement::click(Point point)
{
    return false;
    if(containsPoint(point)) {
        return true;
    }
    else {
        return false;
    }
}

bool UIElement::containsPoint(Point point)
{
    if((point.x() < position_.x()) || (point.x() > position_.x() + width_)) {
        return false;
    }
    else if((point.y() < position_.y()) || (point.y() > position_.y() + height_)) {
        return false;
    }

    return true;
}
bool UIElement::loadTexture(std::string artAsset)
{
    artAsset_ = artAsset;
    Renderer * renderer = Game::instance()->renderer();

    texture_ = renderer->loadTexture(artAsset_);
    if(texture_ == nullptr) {
        return false;
    }

    SDL_QueryTexture(texture_, NULL, NULL, &width_, &height_);


    return true;
}
