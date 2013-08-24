//#include "main.h"

Dot::Dot()
{
    x_position_ = 0;
    y_position_ = 0;
    x_velocity_ = 0;
    y_velocity_ = 0;
    surface_ = nullptr;
}

void Dot::handle_input(SDL_Event event)
{
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

void Dot::move(Uint32 deltaTicks)
{
    // Move left/right
    x_position_ += x_velocity_ * (deltaTicks / 1000.f);

    // Check left boundary
    if(x_position_ < 0) {
        x_position_ = 0;
    }
    // Check right boundary
    else if(x_position_ + kDotWidth > kScreenWidth) {
        x_position_ = kScreenWidth - kDotWidth;
    }

    // Move up/down
    y_position_ += y_velocity_ * (deltaTicks / 1000.f);

    // Check top boundary
    if(y_position_ < 0) {
        y_position_ = 0;
    }
    // Check bottom boundary
    else if(y_position_ + kDotHeight > kScreenHeight) {
        y_position_ = kScreenHeight - kDotHeight;
    }
}

void Dot::show()
{
    apply_surface((int) x_position_, (int) y,_position_ surface_, screen);
}
