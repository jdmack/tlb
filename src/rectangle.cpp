#include "rectangle.h"
#include "SDL2/SDL.h"

Rectangle::Rectangle()
{
    x_      = 0;
    y_      = 0;
    width_  = 0;
    height_ = 0;
    
    sdl_rect_ = new SDL_Rect;
    sdl_rect_->x = 0;
    sdl_rect_->y = 0;
    sdl_rect_->w = 0;
    sdl_rect_->h = 0;
}

Rectangle::Rectangle(int x, int y, int width, int height)
{
    x_      = 0;
    y_      = 0;
    width_  = 0;
    height_ = 0;
    
    sdl_rect_ = new SDL_Rect;
    sdl_rect_->x = x_;
    sdl_rect_->y = y_;
    sdl_rect_->w = width_;
    sdl_rect_->h = height_;
}

void Rectangle::set_sdl_rect()
{
    sdl_rect_->x = x_;
    sdl_rect_->y = y_;
    sdl_rect_->w = width_;
    sdl_rect_->h = height_;
}

void Rectangle::set_sdl_rect(int x, int y, int width, int height)
{
    x_      = x;
    y_      = y;
    width_  = width;
    height_ = height;
    
    sdl_rect_->x = x_;
    sdl_rect_->y = y_;
    sdl_rect_->w = width_;
    sdl_rect_->h = height_;


}
