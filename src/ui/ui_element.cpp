#include "SDL2/SDL.h"
#include "ui/ui_element.h"
#include "point.h"
#include "util/logger.h"
#include "renderer.h"
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
    renderer->render_texture_frame(texture_, frame, &offset);
}

bool UIElement::toggle()
{
    visible_ = !visible_;
    return visible_;
}

void UIElement::update()
{

}

