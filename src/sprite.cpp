#include "assets.h"
#include "sprite.h"
#include "screen.h"
#include "game_object.h"
#include "utils/logger.h"

Sprite::Sprite(GameObject * object, std::string asset, std::string select_asset)
{
    object_ = object;
    //art_asset_ = asset;
    art_asset_ = kAssetSpriteZombie1;
    select_art_asset_ = select_asset;
    texture_ = nullptr;
    screen_ = nullptr;
    height_ = object->height();
    width_ = object->width();

    animation_timer_.start();


    // temporary animation build code
    //Animation walk_down("walk_down", 10);
    //walk_down.insert_frame("walk_down_1", SDL_Rect(0, 0, 0, 0));
    //walk_down.insert_frame("walk_down_2", SDL_Rect(0, 0, 0, 0));
    //walk_down.insert_frame("walk_down_3", SDL_Rect(0, 0, 0, 0));

    Animation walk_right("walk_right", 10);
    SDL_Rect walk_right_1;
    walk_right_1.x = 0;
    walk_right_1.y = 36;
    walk_right_1.w = 48;
    walk_right_1.h = 31;
    walk_right.insert_frame("walk_right_1", walk_right_1);
    SDL_Rect walk_right_2;
    walk_right_2.x = 48;
    walk_right_2.y = 36;
    walk_right_2.w = 48;
    walk_right_2.h = 31;
    walk_right.insert_frame("walk_right_2", walk_right_2);
    SDL_Rect walk_right_3;
    walk_right_3.x = 96;
    walk_right_3.y = 36;
    walk_right_3.w = 48;
    walk_right_3.h = 31;
    walk_right.insert_frame("walk_right_3", walk_right_3);

    //Animation walk_up("walk_up", 10);
    //walk_up.insert_frame("walk_up_1", SDL_Rect(0, 0, 0, 0));
    //walk_up.insert_frame("walk_up_2", SDL_Rect(0, 0, 0, 0));
    //walk_up.insert_frame("walk_up_3", SDL_Rect(0, 0, 0, 0));

    //Animation walk_left("walk_left", 10);
    //walk_left.insert_frame("walk_left_1", SDL_Rect(0, 0, 0, 0));
    //walk_left.insert_frame("walk_left_2", SDL_Rect(0, 0, 0, 0));
    //walk_left.insert_frame("walk_left_3", SDL_Rect(0, 0, 0, 0));

    current_animation_ = walk_right;
    // setup first animation frame

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
    //screen_->render_texture_rotate(texture_, &offset, nullptr, -object_->rotation());
    screen_->render_texture(texture_, &offset, &(current_animation_.current()->second));
}

void Sprite::update()
{
    if(animation_timer_.get_ticks() >= current_animation_.time()) {

    }

}
