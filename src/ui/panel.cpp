#include "ui/panel.h"
#include "point.h"
#include "util/logger.h"

Panel::Panel()
{

}

Panel::Panel(Renderer * renderer)
{
    position_ = Point(0, 0);
    width_ = 0;
    height_ = 0;

    color_ = { 0, 0, 0, 255 };
    texture_ = nullptr;
    renderer_ = renderer;
    visible_ = true;
}

Panel::~Panel()
{
    SDL_DestroyTexture(texture_);
}


void Panel::render()
{
    // Draw background rectangle
    SDL_SetRenderDrawBlendMode(renderer_->renderer(), SDL_BLENDMODE_BLEND);
    SDL_Rect frame = { (int)position_.x(), (int)position_.y(), width_, height_ };
    SDL_SetRenderDrawColor(renderer_->renderer(), color_.r, color_.g, color_.b, color_.a);
    SDL_RenderFillRect(renderer_->renderer(), &frame);

    // Render debug frame
    //SDL_Rect offset = { x_position_, y_position_, surface->w, surface->h };
    //texture_ = SDL_CreateTextureFromSurface(renderer_->renderer(), surface);
    //if(texture_ == nullptr) {
    //    Logger::write(Logger::ss << "Panel Texture: " << SDL_GetError());
    //}
    //else {
    //    renderer_->render_texture(texture_, &offset, nullptr);
   // }
    //SDL_FreeSurface(surface);
}

bool Panel::toggle()
{
    visible_ = !visible_;
    return visible_;
}
