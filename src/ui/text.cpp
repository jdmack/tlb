#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL.h"
#include "ui/text.h"
#include "point.h"
#include "color.h"
#include "util/logger.h"
#include "game.h"
#include "assets.h"

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
    font_asset_ = kAssetFontUbuntuMono;

    texture_ = nullptr;
    renderer_ = nullptr;
    font_ = load_font(font_asset_, size_);
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
    font_asset_ = kAssetFontUbuntuMono;
    texture_ = nullptr;
    renderer_ = nullptr;
    font_ = load_font(font_asset_, size_);

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
    //SDL_Surface * surface = TTF_RenderText_Solid(font_, text_.c_str(), color);
    SDL_Surface * surface = TTF_RenderText_Blended_Wrapped(font_, text_.c_str(), color, wrap_);
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
            SDL_QueryTexture(texture_, NULL, NULL, &width_, &height_);
        }

        //Get rid of old surface
        SDL_FreeSurface(surface);
    }
}

TTF_Font * Text::load_font(std::string filename, int size)
{
    TTF_Font * font = TTF_OpenFont(filename.c_str(), size);
        if(font == nullptr) {
            Logger::write(Logger::ss << "Failed to load font! SDL_ttf Error: " << TTF_GetError());
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
    renderer->render_texture_frame(texture_, frame, &offset);

}

void Text::update()
{
    set_text(text_);
}

void Text::reload_font()
{
    font_ = load_font(font_asset_, size_);
}
