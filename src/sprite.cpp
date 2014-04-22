#include "assets.h"
#include "action.h"
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

    current_action_ = kActionIdle;
    current_direction_ = object_->rotation();

    // temporary animation build code
    // walk_right
    Animation walk_right("walk_right", 100);
    SDL_Rect walk_right_1 = { 0, 36, 32, 35 };
    SDL_Rect walk_right_2 = { 46, 36, 32, 35 };
    SDL_Rect walk_right_3 = { 92, 36, 32, 35 };
    walk_right.insert_frame("walk_right_1", walk_right_1);
    walk_right.insert_frame("walk_right_2", walk_right_2);
    walk_right.insert_frame("walk_right_3", walk_right_3);
    walk_right.insert_frame("walk_right_2", walk_right_2);
    animations_.insert(std::pair<std::string, Animation>("walk_right", walk_right));

    // walk down
    Animation walk_down("walk_down", 100);
    SDL_Rect walk_down_1 = { 0, 0, 32, 35 };
    SDL_Rect walk_down_2 = { 46, 0, 32, 35 };
    SDL_Rect walk_down_3 = { 92, 0, 32, 35 };
    walk_down.insert_frame("walk_down_1", walk_down_1);
    walk_down.insert_frame("walk_down_2", walk_down_2);
    walk_down.insert_frame("walk_down_3", walk_down_3);
    walk_down.insert_frame("walk_down_2", walk_down_2);
    animations_.insert(std::pair<std::string, Animation>("walk_down", walk_down));

    // walk left
    Animation walk_left("walk_left", 100);
    SDL_Rect walk_left_1 = { 0, 108, 32, 35 };
    SDL_Rect walk_left_2 = { 46, 108, 32, 35 };
    SDL_Rect walk_left_3 = { 92, 108, 32, 35 };
    walk_left.insert_frame("walk_left_1", walk_left_1);
    walk_left.insert_frame("walk_left_2", walk_left_2);
    walk_left.insert_frame("walk_left_3", walk_left_3);
    walk_left.insert_frame("walk_left_2", walk_left_2);
    animations_.insert(std::pair<std::string, Animation>("walk_left", walk_left));

    // walk up
    Animation walk_up("walk_up", 100);
    SDL_Rect walk_up_1 = { 0, 72, 32, 35 };
    SDL_Rect walk_up_2 = { 46, 72, 32, 35 };
    SDL_Rect walk_up_3 = { 92, 72, 32, 35 };
    walk_up.insert_frame("walk_up_1", walk_up_1);
    walk_up.insert_frame("walk_up_2", walk_up_2);
    walk_up.insert_frame("walk_up_3", walk_up_3);
    walk_up.insert_frame("walk_up_2", walk_up_2);
    animations_.insert(std::pair<std::string, Animation>("walk_up", walk_up));

    Animation idle_down("idle_down", 200);
    idle_down.insert_frame("idle_down_1", walk_down_2);
    animations_.insert(std::pair<std::string, Animation>("idle_down", idle_down));

    Animation idle_right("idle_right", 200);
    idle_right.insert_frame("idle_right_1", walk_right_2);
    animations_.insert(std::pair<std::string, Animation>("idle_right", idle_right));

    Animation idle_up("idle_up", 200);
    idle_up.insert_frame("idle_up_1", walk_up_2);
    animations_.insert(std::pair<std::string, Animation>("idle_up", idle_up));

    Animation idle_left("idle_left", 200);
    idle_left.insert_frame("idle_left_1", walk_left_2);
    animations_.insert(std::pair<std::string, Animation>("idle_left", idle_left));

    animation_timer_.start();
    //current_animation_ = idle_right;
    current_animation_ = animations_["idle_right"];
    //current_animation_ = walk_right;
}

void Sprite::select()
{
    /*
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
    */
}

void Sprite::deselect()
{
    /*
    SDL_DestroyTexture(texture_);
    texture_ = nullptr;
    texture_ = screen_->load_texture_alpha(art_asset_);
    */
}

void Sprite::render()
{
    update();

    // convert floating-point positions to integers for drawing
    //SDL_Rect offset = { object_->x_position() - (object_->width() / 2), object_->y_position() - (object_->height() / 2), height_, width_ };
    SDL_Rect offset = { (int)object_->x_position() - ((int)object_->width() / 2), (int)object_->y_position() - ((int)object_->height() / 2), 32, 35 };
    //screen_->render_texture_rotate(texture_, &offset, nullptr, -object_->rotation());
    //screen_->render_texture(texture_, &offset, &(current_animation_.current()->second));
    //screen_->render_texture(texture_, &offset, &(*(current_animation_.current())));
    SDL_Rect clip = current_animation_.current_frame();
    screen_->render_texture(texture_, &offset, &clip);
    Logger::write(Logger::string_stream << "Frame: " << current_animation_.current());
}

void Sprite::update()
{
    // update current animation based on current action
    std::string action_type;

    if(object_->current_action() == nullptr) {
        action_type = kActionIdle;
    }
    else {
        action_type = object_->current_action()->type();
    }

    if(action_type != current_action_) {
        current_action_ = action_type;

        if(action_type == kActionMovement) {
            // determine direction
            double rotation = object_->rotation();

            if((rotation >= 45) && (rotation <= 135)) {
                current_animation_ = animations_["walk_down"];
            }
            else if((rotation >= 135) && (rotation <= 225)) {
                current_animation_ = animations_["walk_left"];
            }
            else if((rotation >= 225) && (rotation <= 315)) {
                current_animation_ = animations_["walk_up"];
            }
            else {
                current_animation_ = animations_["walk_right"];
            }
        }
        else if(action_type == kActionIdle) {
            // determine direction
            double rotation = object_->rotation();

            if((rotation >= 45) && (rotation <= 135)) {
                current_animation_ = animations_["idle_down"];
            }
            else if((rotation >= 135) && (rotation <= 225)) {
                current_animation_ = animations_["idle_left"];
            }
            else if((rotation >= 225) && (rotation <= 315)) {
                current_animation_ = animations_["idle_up"];
            }
            else {
                current_animation_ = animations_["idle_right"];
            }
        }

    }
    if(current_direction_ != object_->rotation()) {
        current_direction_ = object_->rotation();
        if(action_type == kActionMovement) {
            // determine direction
            double rotation = object_->rotation();

            if((rotation >= 45) && (rotation <= 135)) {
                current_animation_ = animations_["walk_down"];
            }
            else if((rotation >= 135) && (rotation <= 225)) {
                current_animation_ = animations_["walk_left"];
            }
            else if((rotation >= 225) && (rotation <= 315)) {
                current_animation_ = animations_["walk_up"];
            }
            else {
                current_animation_ = animations_["walk_right"];
            }
        }
        else if(action_type == kActionIdle) {
            // determine direction
            double rotation = object_->rotation();

            if((rotation >= 45) && (rotation <= 135)) {
                current_animation_ = animations_["idle_down"];
            }
            else if((rotation >= 135) && (rotation <= 225)) {
                current_animation_ = animations_["idle_left"];
            }
            else if((rotation >= 225) && (rotation <= 315)) {
                current_animation_ = animations_["idle_up"];
            }
            else {
                current_animation_ = animations_["idle_right"];
            }
        }
    }


    // update frame of current animation
    if(animation_timer_.get_ticks() >= current_animation_.time()) {
        current_animation_.next_frame();
        animation_timer_.start();
    }

}
