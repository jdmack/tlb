#include "sprite.h"
#include "screen.h"
#include "game_object.h"

Sprite::Sprite(GameObject * object, std::string asset, std::string select_asset)
{
    object_ = object;
    rotation_ = 0;
    art_asset_ = asset;
    select_art_asset_ = select_asset;
    surface_ = nullptr;
    screen_ = nullptr;
}

void Sprite::select()
{
    SDL_Surface * select_surface = screen_->load_image_alpha(select_art_asset_);
    screen_->apply_surface(0, 0, select_surface, surface_);
    SDL_FreeSurface(select_surface);
}

void Sprite::deselect()
{
    SDL_FreeSurface(surface_);
    surface_ = nullptr;
    surface_ = screen_->load_image_alpha(art_asset_);
}

void Sprite::draw()
{
    if(rotation_ != object_->rotation()) {
        set_rotation(object_->rotation());
    }

    screen_->blit_surface(object_->x_position() - (object_->width() / 2), object_->y_position() - (object_->height() / 2), surface_);
}

void Sprite::set_rotation(double rotation)
{
    surface_ = screen_->rotate_surface(surface_, rotation - rotation_);
    rotation_ = rotation;
}
