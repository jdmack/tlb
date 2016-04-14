#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL.h"
#include "ui/Text.h"
#include "Point.h"
#include "Color.h"
#include "util/Logger.h"
#include "Game.h"
#include "Assets.h"

Text::Text()
{
    position_ = Point(0, 0);
    width_ = 0;
    height_ = 0;
    size_ = kDefaultTextSize;
    wrap_ = kDefaultTextWrap;
    visible_ = true;
    text_ = "";
    color_ = Color(0, 0, 0);
    fontAsset_ = kAssetFontUbuntuMono;

    texture_ = nullptr;
    renderer_ = nullptr;
    font_ = loadFont(fontAsset_, size_);
}

Text::Text(std::string text, int size)
{
    position_ = Point(0, 0);
    width_ = 0;
    height_ = 0;
    size_ = size;
    wrap_ = kDefaultTextWrap;
    visible_ = true;
    color_ = Color(255, 255, 255);
    fontAsset_ = kAssetFontUbuntuMono;
    texture_ = nullptr;
    renderer_ = nullptr;
    font_ = loadFont(fontAsset_, size_);

    setText(text);
}

Text::~Text()
{
    SDL_DestroyTexture(texture_);
}

void Text::setText(std::string text)
{
    text_ = text;

    //Render text surface
    SDL_Color color = { color_.red(), color_.green(), color_.blue() };
    //SDL_Surface * surface = TTF_RenderText_Solid(font_, text_.c_str(), color);
    SDL_Surface * surface = TTF_RenderText_Blended_Wrapped(font_, text_.c_str(), color, wrap_);
    if(surface == nullptr) {
        Logger::write(Logger::ss << "Unable to render text surface! SDLTtf Error: " << TTF_GetError());
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
            SDL_QueryTexture(texture_, NULL, NULL, &width_, &height_);
        }

        //Get rid of old surface
        SDL_FreeSurface(surface);
    }
}

TTF_Font * Text::loadFont(std::string filename, int size)
{
    TTF_Font * font = TTF_OpenFont(filename.c_str(), size);
        if(font == nullptr) {
            Logger::write(Logger::ss << "Failed to load font! SDLTtf Error: " << TTF_GetError());
        }
        return font;
}

void Text::render(Frame * frame)
{
    if(texture_ == nullptr) printf("ERROR\n");
    if(!visible_) return;
    //SDL_Rect offset = { position_.x() - (width_ / 2), position_.y() - (height_ / 2), width_, height_ };
    SDL_Rect offset = { (int)position_.x(), (int)position_.y(), width_, height_ };

    Renderer * renderer = Game::instance()->renderer();
    renderer->renderTextureFrame(texture_, frame, &offset);

}

void Text::update()
{
    setText(text_);
}

void Text::reloadFont()
{
    font_ = loadFont(fontAsset_, size_);
}
