#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL.h"
#include "ui/text.h"
#include "point.h"
#include "color.h"
#include "utils/logger.h"
#include "game.h"
#include "assets.h"

Text::Text()
{
    position_ = Point(0, 0);
    width_ = 0;
    height_ = 0;
    size_ = 0;
    visible_ = true;
    text_ = "";
    color_ = Color(0, 0, 0);

    texture_ = nullptr;
    renderer_ = nullptr;
    font_ = nullptr;

}

Text::Text(std::string text)
{
    position_ = Point(0, 0);
    width_ = 0;
    height_ = 0;
    size_ = 0;
    visible_ = true;
    color_ = Color(255, 0, 255);

    texture_ = nullptr;
    renderer_ = nullptr;
    font_ = load_font(kAssetFontPsychoPoetry, 28);

    set_text(text);


}

Text::~Text()
{
    SDL_DestroyTexture(texture_);
}

void Text::set_text(std::string text)
{
    text_ = text;

    //Render text surface
    SDL_Color color = { color_.red(), color_.green(), color_.blue() };
    SDL_Surface * surface = TTF_RenderText_Solid(font_, text_.c_str(), color);
    if(surface == nullptr) {
        Logger::write(Logger::ss << "Unable to render text surface! SDL_ttf Error: " << TTF_GetError());
    }
    else
    {
        //Create texture from surface pixels
        texture_ = SDL_CreateTextureFromSurface(Game::instance()->renderer()->renderer(), surface);
        if(texture_ == nullptr)  {
            Logger::write(Logger::ss << "Unable to create texture from rendered text! SDL Error: " << SDL_GetError());
        }
        else {
            //Get image dimensions
            width_ = surface->w;
            height_ = surface->h;
        }

        //Get rid of old surface
        SDL_FreeSurface(surface);
    }
}

TTF_Font * Text::load_font(std::string filename, int size)
{
    TTF_Font * font = TTF_OpenFont(filename.c_str(), size);
        if(font == nullptr) {
            Logger::write(Logger::ss << "Failed to load lazy font! SDL_ttf Error: " << TTF_GetError());
        }
        return font;
}

void Text::render()
{
    if(texture_ == nullptr) printf("ERROR\n");
    //SDL_Rect offset = { position_.x() - (width_ / 2), position_.y() - (height_ / 2), height_, width_ };
    SDL_Rect offset = { position_.x(), position_.y(), height_, width_ };
    Game::instance()->renderer()->render_texture(texture_, &offset);

}
