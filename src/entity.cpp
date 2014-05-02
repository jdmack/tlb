#include <cmath>

#include "SDL2/SDL.h"

#include "entity.h"
#include "assets.h"
#include "point.h"
#include "game.h"
#include "level.h"
#include "movement_action.h"
#include "movement.h"
#include "screen.h"
#include "sprite.h"
#include "vector.h"
#include "utils/logger.h"

Entity::Entity(Game * game) : GameObject(game)
{
    x_velocity_ = 0;
    y_velocity_ = 0;

    width_  = kEntityWidth;
    height_ = kEntityHeight;

    selectable_ = true;
    sprite_ = new Sprite(this, kAssetArtHexagon, kAssetArtHexagonOutline);
}

Entity::Entity(Game * game, double x, double y, double rot) : GameObject(game, x, y, rot)
{
    x_velocity_ = 0;
    y_velocity_ = 0;

    width_  = kEntityWidth;
    height_ = kEntityHeight;

    selectable_ = true;
    sprite_ = new Sprite(this, kAssetArtHexagon, kAssetArtHexagonOutline);
}

void Entity::update(int delta_ticks)
{
    if(current_action_ != nullptr) {
        bool keep_action = current_action_->update(this, delta_ticks);

        if(!keep_action) {
            delete current_action_;
            current_action_ = nullptr;
        }
    }
}

bool Entity::contains_point(double x, double y)
{
    if((x < (x_position_ - (width_ / 2))) || (x > (x_position_ + (width_ / 2)))) {
        return false;
    }
    else if((y < (y_position_ - (width_ / 2))) || (y > (y_position_ + (height_ / 2)))) {
        return false;
    }

    return true;
}

void Entity::select()
{
    Logger::write(Logger::string_stream << "Entity::select object_id: " << object_id_ << " (x,y): (" << x_position_ << ", " <<  y_position_ << ")");
    GameObject::select();
    sprite_->select();
}

void Entity::deselect()
{
    Logger::write("Entity::deselect");
    GameObject::deselect();
    sprite_->deselect();
}

void Entity::move(double x, double y)
{
    Logger::write(Logger::string_stream << "Move - (x,y): (" << x_position_ << "," << y_position_ << ")");

    // Delete current action if one exists
    if(current_action_ != nullptr) {
        delete current_action_;
        current_action_ = nullptr;
    }

    // Create movement action
    MovementAction * movement_action = new MovementAction(Point(x_position_, y_position_), Point(x, y), game_->level());
    if(movement_action->empty_path()) {
        return;
    }
    current_action_ = movement_action;

    // Start the first movement

    //Vector acceleration(kEntityAcceleration, movement_action->current()->vector().direction());
    x_velocity_ = movement_action->current()->maximum_velocity().x_component();
    y_velocity_ = movement_action->current()->maximum_velocity().y_component();
    //x_acceleration_ = acceleration.x_component();
    //y_acceleration_ = acceleration.y_component();

}

void Entity::stop()
{
    x_velocity_ = 0;
    y_velocity_ = 0;
    x_acceleration_ = 0;
    y_acceleration_ = 0;
}

bool Entity::stopped()
{
    if((x_velocity_ == 0) && (y_velocity_ == 0) && (x_acceleration_ == 0) && (y_acceleration_ == 0)) {
        return true;
    }
    return false;
}
