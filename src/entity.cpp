#include <cmath>

#include "SDL2/SDL.h"

#include "entity.h"
#include "assets.h"
#include "point.h"
#include "game.h"
#include "level.h"
#include "action/move_action.h"
#include "action/dead_action.h"
#include "action/action.h"
#include "action/attack_action.h"
#include "action/rotate_action.h"
#include "movement.h"
#include "renderer.h"
#include "sprite.h"
#include "vector.h"
#include "util/logger.h"
#include "ai_state/ai_state_machine.h"

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

    dead_ = false;

    state_machine_ = new AIStateMachine(this);
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

    dead_ = false;
    state_machine_ = new AIStateMachine(this);
}

void Entity::update(int delta_ticks)
{
    // TODO(2014-08-21/JM): Can create a DeadAction that contains a duration to trigger DYING animation
    // and then will be a DEAD state

    if(state_machine_ != nullptr) {
        state_machine_->update(delta_ticks);
    }
}

bool Entity::contains_point(double x, double y)
{
    if((x < (x_abs_ - (width_ / 2))) || (x > (x_abs_ + (width_ / 2)))) {
        return false;
    }
    else if((y < (y_abs_ - (width_ / 2))) || (y > (y_abs_ + (height_ / 2)))) {
        return false;
    }

    return true;
}

//void Entity::select()
//{
//    Logger::write(Logger::ss << "Entity::select object_id: " << object_id_ << " (x,y): (" << x_position_ << ", " <<  y_position_ << ")");
//    //GameObject::select();
//}

//void Entity::deselect()
//{
//    Logger::write("Entity::deselect");
//    selected_ = false;
//}

void Entity::move(Point point)
{
    // TODO(2014-11-05/JM): May want to add distinction between "move" and "move_command". Depends on if there
    // is ever need for the case of an AI or event issuing a move directive to non-controllable entities
    if(controllable_) {
        Logger::write(Logger::ss << "Move - (x,y): (" << point.x() << "," << point.y() << ")");
        state_machine_->move_command(point);
    }
}

void Entity::rotate(Point point)
{
    state_machine_->rotate_command(point);
}

void Entity::attack(Entity * target)
{
    Logger::write(Logger::ss << "Attack - (Entity): (" << target->object_id() << ")");
    state_machine_->attack_command(target);
}

void Entity::stop()
{
    state_machine_->stop();
}

bool Entity::stopped()
{
    if((x_velocity_ == 0) && (y_velocity_ == 0) && (x_acceleration_ == 0) && (y_acceleration_ == 0)) {
        return true;
    }
    return false;
}

ActionType Entity::action_type()
{
    return state_machine_->action_type();   
}

void Entity::set_dead(bool dead)
{
    dead_ = dead;
    selectable_ = !dead;
    controllable_ = !dead;
}
