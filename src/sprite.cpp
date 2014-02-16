#include "sprite.h"
#include "screen.h"
#include "game_object.h"
#include "utils/logger.h"

Sprite::Sprite(GameObject * object, std::string asset, std::string select_asset)
{
    object_ = object;
    art_asset_ = asset;
    select_art_asset_ = select_asset;
    texture_ = nullptr;
    screen_ = nullptr;
    height_ = object->height();
    width_ = object->width();
}

void Sprite::select()
{
    SDL_DestroyTexture(texture_);

    SDL_Surface * surface = screen_->load_image_alpha(art_asset_);
    SDL_Surface * select_surface = screen_->load_image_alpha(select_art_asset_);

    SDL_Rect offset;
    offset.x = 0;
    offset.y = 0;
    offset.w = width_;
    offset.h = height_;

    screen_->apply_surface(select_surface, surface, &offset);

    texture_ = SDL_CreateTextureFromSurface(screen_->renderer(), surface);
    SDL_FreeSurface(select_surface);
}

void Sprite::deselect()
{
    SDL_DestroyTexture(texture_);
    texture_ = nullptr;
    texture_ = screen_->load_texture_alpha(art_asset_);
}

void Sprite::render()
{
    SDL_Rect offset;
    offset.x = object_->x_position() - (object_->width() / 2);
    offset.y = object_->y_position() - (object_->height() / 2);
    offset.h = height_;
    offset.w = width_;
    screen_->render_texture_rotate(texture_, &offset, nullptr, -object_->rotation());
    //screen_->render_texture(texture_, &offset);
}
