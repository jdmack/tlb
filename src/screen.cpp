#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "screen.h"
#include "game_object.h"

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
    apply_surface(x_position, y_position, source, surface_);
}

void Screen::clear()
{
    Uint32 clear_color = kDefaultClearColor;
    SDL_FillRect(surface_, &surface_->clip_rect, clear_color);
}

void Screen::clear(Uint32 clear_color)
{
    SDL_FillRect(surface_, &surface_->clip_rect, clear_color);
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
SDL_Surface * Screen::load_image(std::string filename)
{
    SDL_Surface* loadedImage    = nullptr;
    SDL_Surface* optimizedImage = nullptr;

    loadedImage = IMG_Load(filename.c_str());

    if(loadedImage != nullptr) {
        optimizedImage = SDL_DisplayFormat(loadedImage);
        SDL_FreeSurface(loadedImage);
    }

    return optimizedImage;
}

SDL_Surface * Screen::load_image_alpha(std::string filename)
{
    SDL_Surface* loadedImage = nullptr;
    SDL_Surface* optimizedImage = nullptr;

    loadedImage = IMG_Load(filename.c_str());

    if(loadedImage != nullptr) {
        optimizedImage = SDL_DisplayFormatAlpha(loadedImage);
        SDL_FreeSurface(loadedImage);
    }

    return optimizedImage;
}

void Screen::apply_surface(int x, int y, SDL_Surface * source, SDL_Surface * destination )
{
    SDL_Rect offset;

    offset.x = x;
    offset.y = y;

    SDL_BlitSurface(source, nullptr, destination, &offset );
}

void Screen::addObject(GameObject * object)
{
    objects.push_back(object);
    object->set_surface(load_image_alpha(object->art_asset()));
    object->register_screen(this);
    // TODO(2013-08-24/JM): Add function to remove object from the vector
    // or add an "active" field to distinguish elements that haven't been deleted yet
}

/*******************************************************************************
/*  Accessors
/******************************************************************************/

SDL_Surface * Screen::surface()
{
    return surface_;
}
