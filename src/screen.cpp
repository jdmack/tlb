#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "screen.h"
#include "game_object.h"
#include "sprite.h"
#include "util/logger.h"

////////////////////////////////////////////////////////////////////////////////
//
//
//
////////////////////////////////////////////////////////////////////////////////
Screen::Screen()
{
    surface_ = nullptr;
}

////////////////////////////////////////////////////////////////////////////////
//
//
//
////////////////////////////////////////////////////////////////////////////////
bool Screen::init()
{
    // Initialize SDL
    // TODO(2013-08-23/JM): Move this elsewhere, init function for whole game
    if(SDL_Init(SDL_INIT_EVERYTHING) == -1) {
        return false;
    }

    // Setup screen
    //surface_ = SDL_SetVideoMode(kScreenWidth, kScreenHeight, kScreenBitsPerPixel, SDL_SWSURFACE | SDL_NOFRAME);
    surface_ = SDL_SetVideoMode(kScreenWidth, kScreenHeight, kScreenBitsPerPixel, SDL_SWSURFACE);

    // Check screen was setup successfully
    if(surface_ == nullptr) {
        return false;
    }

    // Set window caption
    SDL_WM_SetCaption(kWindowName.c_str(), nullptr);
    //SDL_putenv("SDL_VIDEO_CENTERED=center");
    /* Game was the unchanging parts of Teitrus, such as the overlay, title, border, etc
    game = SDL_CreateRGBSurface(0, kScreenWidth, kScreenHeight, kScreenBitsPerPixel, kRedMask, kGreenMask, kBlueMask, kAlphaMask);
    if(game == nullptr) {
        return false;
    } */
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//
//
//
////////////////////////////////////////////////////////////////////////////////
void Screen::blit_surface(int x_position, int y_position, SDL_Surface * source, SDL_Rect * clip)
{
    // TODO(2013-08-28/JM): Set constants for the rendering boundaries
    if(x_position < 0) { x_position = 0; }
    if(x_position > kScreenWidth) { x_position = kScreenWidth; }
    if(y_position < 0) { y_position = 0; }
    if(y_position > kScreenHeight) { y_position = kScreenHeight; }

    apply_surface(x_position, y_position, source, surface_, clip);
}

////////////////////////////////////////////////////////////////////////////////
//
//
//
////////////////////////////////////////////////////////////////////////////////
void Screen::clear()
{
    Uint32 clear_color = kDefaultClearColor;
    SDL_FillRect(surface_, &surface_->clip_rect, clear_color);
}

////////////////////////////////////////////////////////////////////////////////
//
//
//
////////////////////////////////////////////////////////////////////////////////
void Screen::clear(Uint32 clear_color)
{
    SDL_FillRect(surface_, &surface_->clip_rect, clear_color);
}

////////////////////////////////////////////////////////////////////////////////
//
//
//
////////////////////////////////////////////////////////////////////////////////
bool Screen::update()
{
    if(SDL_Flip(surface_) == -1) {
        return false;
    }

    return true;
}

////////////////////////////////////////////////////////////////////////////////
//
//
//
////////////////////////////////////////////////////////////////////////////////
void Screen::clean_up()
{
    // TODO(2013-08-23/JM): Move this elsewhere, cleanup function for whole game
    SDL_Quit();
}

////////////////////////////////////////////////////////////////////////////////
//
//
//
////////////////////////////////////////////////////////////////////////////////
SDL_Surface * Screen::load_image(std::string filename)
{
    SDL_Surface* loadedImage    = nullptr;
    SDL_Surface* optimizedImage = nullptr;

    loadedImage = IMG_Load(filename.c_str());

    if(loadedImage != nullptr) {
        optimizedImage = SDL_DisplayFormat(loadedImage);
        SDL_FreeSurface(loadedImage);
    }

    if( optimizedImage != NULL ) {
        Uint32 colorkey = SDL_MapRGB(optimizedImage->format, 0xFF, 0, 0xFF);
        SDL_SetColorKey(optimizedImage, SDL_SRCCOLORKEY, colorkey);
    }

    return optimizedImage;
}

////////////////////////////////////////////////////////////////////////////////
//
//
//
////////////////////////////////////////////////////////////////////////////////
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

////////////////////////////////////////////////////////////////////////////////
//
//
//
////////////////////////////////////////////////////////////////////////////////
void Screen::apply_surface(int x, int y, SDL_Surface * source, SDL_Surface * destination, SDL_Rect * clip)
{
    SDL_Rect offset;

    offset.x = x;
    offset.y = y;

    SDL_BlitSurface(source, clip, destination, &offset );
}

////////////////////////////////////////////////////////////////////////////////
//
//
//
////////////////////////////////////////////////////////////////////////////////
void Screen::init_object(GameObject * object)
{
    object->sprite()->set_surface(load_image_alpha(object->sprite()->art_asset()));
    object->sprite()->set_screen(this);
}

////////////////////////////////////////////////////////////////////////////////
//
//
//
////////////////////////////////////////////////////////////////////////////////
SDL_Surface * Screen::rotate_surface(SDL_Surface * surface, double rotation)
{
    SDL_Surface * rotated_surface = nullptr;

    double degrees = rotation / kPi * 180;
    Logger::write(Logger::string_stream << "rotating: " << degrees << " degrees");
    //rotated_surface = rotozoomSurface(surface, degrees, 1, SMOOTHING_ON);

    SDL_FreeSurface(surface);
    return rotated_surface;
}
