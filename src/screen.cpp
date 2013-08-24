#include "SDL/SDL.h"
#include "screen.h"
#include "surface.h"
#include "constants.h"

Screen::Screen()
{
    surface_ = nullptr;
}

bool Screen::init()
{
    // Initialize SDL
    // TODO(2013-08-23/JM): Move this elsewhere, init function for whole game
    if(SDL_Init(SDL_INIT_EVERYTHING) == -1) {
        return false;
    }

    // Setup screen
    surface_ = SDL_SetVideoMode(kScreenWidth, kScreenHeight, kScreenBitsPerPixel, SDL_SWSURFACE);

    // Check screen was setup successfully
    if(surface_ == nullptr) {
        return false;
    }

    // Set window caption
    SDL_WM_SetCaption(kWindowName.c_str(), nullptr);

    /* Game was the unchanging parts of Teitrus, such as the overlay, title, border, etc
    game = SDL_CreateRGBSurface(0, kScreenWidth, kScreenHeight, kScreenBitsPerPixel, kRedMask, kGreenMask, kBlueMask, kAlphaMask);
    if(game == nullptr) {
        return false;
    } */

    return true;
}

void Screen::blit_surface(int x_position, int y_position, SDL_Surface * source)
{
    surface::apply_surface(x_position, y_position, source, surface_);
}

void Screen::clear()
{
    SDL_FillRect(surface_, &surface_->clip_rect, SDL_MapRGB(surface_->format, 0x00, 0x00, 0x00));
}

bool Screen::update()
{
    if(SDL_Flip(surface_) == -1) {
        return false;
    }

    return true;
}

void Screen::clean_up()
{
    // TODO(2013-08-23/JM): Move this elsewhere, cleanup function for whole game
    SDL_Quit();
}

/*******************************************************************************
/*  Accessors
/******************************************************************************/

SDL_Surface * Screen::surface()
{
    return surface_;
}
