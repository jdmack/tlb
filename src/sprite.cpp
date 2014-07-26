#include "assets.h"
#include "actions/action.h"
#include "sprite.h"
#include "renderer.h"
#include "game_object.h"
#include "utils/logger.h"
#include "rapidxml/rapidxml.hpp"

Sprite::Sprite(GameObject * object, std::string asset, std::string select_asset)
{
    object_ = object;
    art_asset_ = asset;
    select_art_asset_ = select_asset;
    texture_ = nullptr;
    renderer_ = nullptr;
    height_ = object->height();
    width_ = object->width();

    current_action_ = ACTION_IDLE;
    current_direction_ = object_->rotation();

    // open xml doc
    rapidxml::xml_document<> doc;
    //std::ifstream file(kAssetSpriteXMLZombie);
    std::ifstream file(kAssetSpriteXMLHuman);
    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();
    std::string content(buffer.str());
    doc.parse<0>(&content[0]);

    rapidxml::xml_node<> *sprite = doc.first_node();     // this is the sprite element

    // Iterate through animations
    for(rapidxml::xml_node<> *animation = sprite->first_node("animation"); animation; animation = animation->next_sibling()) {

        std::string animation_key;
        int animation_time;

        for (rapidxml::xml_attribute<> *attribute = animation->first_attribute(); attribute; attribute = attribute->next_attribute()) {

                std::string attribute_name = attribute->name();

                if(attribute_name.compare("key") == 0) {
                    animation_key = attribute->value();
                }
                else if(attribute_name.compare("time") == 0) {
                    animation_time = atoi(attribute->value());
                }

        }

        Animation this_animation(animation_key, animation_time);

        // Iterate through frames
        for(rapidxml::xml_node<> *frame = animation->first_node("frame"); frame; frame = frame->next_sibling()) {

            std::string frame_key;
            int frame_x, frame_y, frame_width, frame_height;

            // Iterate through attributes
            for (rapidxml::xml_attribute<> *attribute = frame->first_attribute(); attribute; attribute = attribute->next_attribute()) {

                std::string attribute_name = attribute->name();

                if(attribute_name.compare("key") == 0) {
                    frame_key = attribute->value();
                }
                else if(attribute_name.compare("x") == 0) {
                    frame_x = atoi(attribute->value());
                }
                else if(attribute_name.compare("y") == 0) {
                    frame_y = atoi(attribute->value());
                }
                else if(attribute_name.compare("width") == 0) {
                    frame_width = atoi(attribute->value());
                }
                else if(attribute_name.compare("height") == 0) {
                    frame_height = atoi(attribute->value());
                }
            }

            SDL_Rect this_frame = { frame_x, frame_y, frame_width, frame_height };
            this_animation.insert_frame(animation_key + frame_key, this_frame);
        }

    animations_.insert(std::pair<std::string, Animation>(animation_key, this_animation));

    }

    animation_timer_.start();
    current_animation_ = animations_["idle_right"];
}

void Sprite::select()
{
    /*
    SDL_DestroyTexture(texture_);

    SDL_Surface * surface = renderer_->load_image_alpha(art_asset_);
    SDL_Surface * select_surface = renderer_->load_image_alpha(select_art_asset_);

    SDL_Rect offset;
    offset.x = 0;
    offset.y = 0;
    offset.w = width_;
    offset.h = height_;

    renderer_->apply_surface(select_surface, surface, &offset);

    texture_ = SDL_CreateTextureFromSurface(renderer_->renderer(), surface);
    SDL_FreeSurface(select_surface);
    */
}

void Sprite::deselect()
{
    /*
    SDL_DestroyTexture(texture_);
    texture_ = nullptr;
    texture_ = renderer_->load_texture_alpha(art_asset_);
    */
}

void Sprite::render()
{
    update();

    // convert floating-point positions to integers for drawing
    //SDL_Rect offset = { object_->x_position() - (object_->width() / 2), object_->y_position() - (object_->height() / 2), height_, width_ };
    //SDL_Rect offset = { (int)object_->x_position() - ((int)object_->width() / 2), (int)object_->y_position() - ((int)object_->height() / 2), 32, 35 };
    SDL_Rect offset = { (int)object_->x_position() - ((int)object_->width() / 2), (int)object_->y_position() - ((int)object_->height() / 2), height_, width_ };
    //renderer_->render_texture_rotate(texture_, &offset, nullptr, -object_->rotation());
    //renderer_->render_texture(texture_, &offset, &(current_animation_.current()->second));
    //renderer_->render_texture(texture_, &offset, &(*(current_animation_.current())));
    SDL_Rect clip = current_animation_.current_frame();
    renderer_->render_texture(texture_, &offset, &clip);
    //Logger::write(Logger::string_stream << "Frame: " << current_animation_.current());
}

void Sprite::update()
{
    // update current animation based on current action
    ActionType action_type;

    if(object_->current_action() == nullptr) {
        action_type = ACTION_IDLE;
    }
    else {
        action_type = object_->current_action()->type();
    }

    if(action_type != current_action_) {
        current_action_ = action_type;

        if(action_type == ACTION_MOVEMENT) {
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
        else if(action_type == ACTION_IDLE) {
        //if((object_->current_action() == nullptr) || (object_->current_action()->is_idle())) {
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
        if(action_type == ACTION_MOVEMENT) {
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
        else if(action_type == ACTION_IDLE) {
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
