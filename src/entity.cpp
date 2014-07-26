#include <cmath>

#include "SDL2/SDL.h"

#include "entity.h"
#include "assets.h"
#include "point.h"
#include "game.h"
#include "level.h"
#include "actions/movement_action.h"
#include "movement.h"
#include "renderer.h"
#include "sprite.h"
#include "vector.h"
#include "utils/logger.h"

Entity::Entity(Game * game, EntityType type) : GameObject(game)
{
    type_ = type;

    x_velocity_ = 0;
    y_velocity_ = 0;

    width_  = kEntityWidth;
    height_ = kEntityHeight;

    hp_ = new HitPoint(10);

    selectable_ = true;
    controllable_ = false;

    maximum_speed_ = kEntityDefaultVelocity;
}

Entity::Entity(Game * game, EntityType type, Point position, double rot) : GameObject(game, position, rot)
{
    type_ = type;

    x_velocity_ = 0;
    y_velocity_ = 0;

    width_  = kEntityWidth;
    height_ = kEntityHeight;

    hp_ = new HitPoint(10);

    selectable_ = true;
    controllable_ = false;

    maximum_speed_ = kEntityDefaultVelocity;
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
