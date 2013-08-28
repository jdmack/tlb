#include "SDL/SDL.h"
#include "dot.h"
#include "assets.h"
#include "util/logger.h"
#include "screen.h"

Dot::Dot()
{
    art_asset_ = kAssetArtDot;
    x_velocity_ = 0;
    y_velocity_ = 0;

    selectable_ = true;
}

Dot::Dot(double x, double y, double rot) : GameObject(x,y, rot)
{
    art_asset_ = kAssetArtDot;
    x_velocity_ = 0;
    y_velocity_ = 0;

    selectable_ = true;
}

void Dot::handle_input(SDL_Event event)
{
    if(selected_ == true) {
        if(event.type == SDL_KEYDOWN) {
            switch( event.key.keysym.sym) {
                case SDLK_UP:
                    y_velocity_ -= kDotVelocity;
                    break;
                case SDLK_DOWN:
                    y_velocity_ += kDotVelocity;
                    break;
                case SDLK_LEFT:
                    x_velocity_ -= kDotVelocity;
                    break;
                case SDLK_RIGHT:
                    x_velocity_ += kDotVelocity;
                    break;
            }
        }
        else if(event.type == SDL_KEYUP) {
            switch( event.key.keysym.sym) {
                case SDLK_UP:
                    y_velocity_ += kDotVelocity;
                    break;
                case SDLK_DOWN:
                    y_velocity_ -= kDotVelocity;
                    break;
                case SDLK_LEFT:
                    x_velocity_ += kDotVelocity;
                    break;
                case SDLK_RIGHT:
                    x_velocity_ -= kDotVelocity;
                    break;
            }
        }
    }
}

void Dot::update(int delta_ticks)
{
    // Move left/right
    x_position_ += x_velocity_ * (delta_ticks / 1000.f);

    // Check left boundary
    if(x_position_ < 0) {
        x_position_ = 0;
    }
    // Check right boundary
    else if(x_position_ + kDotWidth > kScreenWidth) {
        x_position_ = kScreenWidth - kDotWidth;
    }

    // Move up/down
    y_position_ += y_velocity_ * (delta_ticks / 1000.f);

    // Check top boundary
    if(y_position_ < 0) {
        y_position_ = 0;
    }
    // Check bottom boundary
    else if(y_position_ + kDotHeight > kScreenHeight) {
        y_position_ = kScreenHeight - kDotHeight;
    }
}

bool Dot::contains_point(double x, double y)
{
    Logger::write("Dot::contains_point");
    if((x < x_position_) || (x > (x_position_ + kDotWidth))) {
        return false;
    }
    else if((y < y_position_) || (y > (y_position_ + kDotHeight))) {
        return false;
    }

    return true;
}

void Dot::select()
{
    Logger::write("Dot::select");
    GameObject::select();
    SDL_Surface * select_surface = screen_->load_image_alpha(kAssetArtDotCircle);
    screen_->apply_surface(0, 0, select_surface, surface_);
    SDL_FreeSurface(select_surface);
}

void Dot::deselect()
{
    Logger::write("Dot::deselect");
    GameObject::deselect();
    SDL_FreeSurface(surface_);
    surface_ = nullptr;
    surface_ = screen_->load_image_alpha(art_asset_);
}
