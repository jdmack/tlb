#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "screen.h"
#include "camera.h"
#include "color.h"
#include "game_object.h"
#include "sprite.h"
#include "utils/logger.h"


////////////////////////////////////////////////////////////////////////////////
//
//
//
////////////////////////////////////////////////////////////////////////////////
Screen::Screen()
{
    window_ = nullptr;
    renderer_ = nullptr;
    camera_ = nullptr;
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
    if(SDL_Init(SDL_INIT_VIDEO) == -1) {
        return false;
    }
    /*
    NOTE/TODO: Uncomment this when SDL_ttf is installed
    if(TTF_Init()==-1) {
        Logger::write(Logger::string_stream << "TTF_Init: " << TTF_GetError());
        return false;
    }
    */

    // Setup screen
    window_ = SDL_CreateWindow(kWindowName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, kScreenWidth, kScreenHeight, SDL_WINDOW_SHOWN);
    renderer_ = SDL_CreateRenderer(window_, -1, 0);

    // Check screen was setup successfully
    if((window_ == nullptr) || (renderer_ == nullptr)) {
        return false;
    }


/*
    int w;
    int h;
    SDL_GetWindowMinimumSize(window_, &w, &h);
    Logger::write(Logger::string_stream << "Minimum: (" << w << " x " << h << ")");
    SDL_GetWindowMaximumSize(window_, &w, &h);
    Logger::write(Logger::string_stream << "Maximum: (" << w << " x " << h << ")");
    */

    return true;
}

////////////////////////////////////////////////////////////////////////////////
//
//
//
////////////////////////////////////////////////////////////////////////////////
void Screen::render_texture(SDL_Texture * texture, SDL_Rect * offset, SDL_Rect * clip)
{
    // TODO(2013-09-09/JM): Add render offset checks

    SDL_Rect rect = { (int)offset->x - (int)camera_->x_position(), (int)offset->y - (int)camera_->y_position(), (int)offset->w, (int)offset->h };

    int return_code = SDL_RenderCopy(renderer_, texture, clip, &rect);

    if(return_code != 0) {
        Logger::write(Logger::string_stream << "Render Error: " << SDL_GetError());
    }
}

////////////////////////////////////////////////////////////////////////////////
//
//
//
////////////////////////////////////////////////////////////////////////////////
void Screen::render_texture_rotate(SDL_Texture * texture, SDL_Rect * offset, SDL_Rect * clip, double angle)
{
    // TODO(2013-09-09/JM): Add render offset checks

    SDL_Rect rect = { (int)offset->x - (int)camera_->x_position(), (int)offset->y - (int)camera_->y_position(), (int)offset->w, (int)offset->h };

    int return_code = SDL_RenderCopyEx(renderer_, texture, nullptr, &rect, -angle, nullptr, SDL_FLIP_NONE);

    if(return_code != 0) {
        Logger::write(Logger::string_stream << "Render Error: " << SDL_GetError());
    }
}

////////////////////////////////////////////////////////////////////////////////
//
//
//
////////////////////////////////////////////////////////////////////////////////
void Screen::apply_surface(SDL_Surface * source, SDL_Surface * destination, SDL_Rect * offset, SDL_Rect * clip)
{
    SDL_BlitSurface(source, clip, destination, offset );
}

////////////////////////////////////////////////////////////////////////////////
//
//
//
////////////////////////////////////////////////////////////////////////////////
void Screen::clear()
{
    SDL_SetRenderDrawColor(renderer_, kDefaultClearColor.red(), kDefaultClearColor.green(), kDefaultClearColor.blue(), 255);
    SDL_RenderClear(renderer_);
}

////////////////////////////////////////////////////////////////////////////////
//
//
//
////////////////////////////////////////////////////////////////////////////////
void Screen::clear(Color clear_color)
{
    SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);
    SDL_RenderClear(renderer_);
}

////////////////////////////////////////////////////////////////////////////////
//
//
//
////////////////////////////////////////////////////////////////////////////////
void Screen::update()
{
    //if(debug_) debug_frame_->render();
    SDL_RenderPresent(renderer_);
}

////////////////////////////////////////////////////////////////////////////////
//
//
//
////////////////////////////////////////////////////////////////////////////////
void Screen::clean_up()
{
    // TODO(2013-08-23/JM): Move this elsewhere, cleanup function for whole game

    //NOTE/TODO: Uncomment this when SDL_ttf is installed
    //TTF_Quit();

    SDL_Quit();
}

////////////////////////////////////////////////////////////////////////////////
//
//
//
////////////////////////////////////////////////////////////////////////////////
SDL_Surface * Screen::load_image(std::string filename)
{
    SDL_Surface* loaded_image    = nullptr;

    loaded_image = IMG_Load(filename.c_str());

    if(loaded_image == nullptr) {
        Logger::write(Logger::string_stream << "IMG_Load Error: " << IMG_GetError());
    }
    else {
        Uint32 colorkey = SDL_MapRGB(loaded_image->format, 0xFF, 0, 0xFF);
        SDL_SetColorKey(loaded_image, SDL_TRUE, colorkey);
    }

    return loaded_image;
}

////////////////////////////////////////////////////////////////////////////////
//
//
//
////////////////////////////////////////////////////////////////////////////////
SDL_Surface * Screen::load_image_alpha(std::string filename)
{
    SDL_Surface* loaded_image = nullptr;

    loaded_image = IMG_Load(filename.c_str());
    if(loaded_image == nullptr) {
        Logger::write(Logger::string_stream << "IMG_Load Error: " << IMG_GetError());
    }
    return loaded_image;
}

////////////////////////////////////////////////////////////////////////////////
//
//
//
////////////////////////////////////////////////////////////////////////////////
SDL_Texture * Screen::load_texture(std::string filename)
{
    SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer_, load_image(filename));

    if(texture == nullptr) {
        Logger::write(Logger::string_stream << "Error creating texture: " << SDL_GetError());
    }

     return texture;
}

////////////////////////////////////////////////////////////////////////////////
//
//
//
////////////////////////////////////////////////////////////////////////////////
SDL_Texture * Screen::load_texture_alpha(std::string filename)
{
    SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer_, load_image_alpha(filename));

    if(texture == nullptr) {
        Logger::write(Logger::string_stream << "Error creating texture: " << SDL_GetError());
    }

     return texture;
}
////////////////////////////////////////////////////////////////////////////////
//
//
//
////////////////////////////////////////////////////////////////////////////////
void Screen::init_object(GameObject * object)
{
    object->sprite()->set_texture(load_texture_alpha(object->sprite()->art_asset()));
    object->sprite()->set_screen(this);
}
