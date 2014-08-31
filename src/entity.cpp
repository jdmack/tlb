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
#include "action/player_action.h"
#include "action/attack_action.h"
#include "action/rotate_action.h"
#include "movement.h"
#include "renderer.h"
#include "sprite.h"
#include "vector.h"
#include "util/logger.h"

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

    current_action_ = new PlayerAction();
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
    current_action_ = new PlayerAction();
}

void Entity::update(int delta_ticks)
{
    // TODO(2014-08-21/JM): Can create a DeadAction that contains a duration to trigger DYING animation
    // and then will be a DEAD state

    // Check if need to die
    if((current_action_ != nullptr) && (current_action_->type() == ACTION_DEAD)) {
        return;
    }
    if(hp_->empty()) {
        dead_ = true;
        selectable_ = false;
        controllable_ = false;
        if(current_action_ != nullptr) {
            delete current_action_;
            current_action_ = nullptr;
        }
        current_action_ = new DeadAction();
    }
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
    Logger::write(Logger::ss << "Move - (x,y): (" << point.x() << "," << point.y() << ")");

    // Create movement action
    MoveAction * move_action = new MoveAction(Point(x_position_, y_position_), point, game_->level());
    if(move_action->empty_path()) {
        Logger::write("Empty path, cancelling Move");
        return;
    }
    PlayerAction * player_action = static_cast<PlayerAction *>(current_action_);
    player_action->stop();
    player_action->set_next_action(static_cast<Action *>(move_action));
    player_action->set_next_state(MOVE);
}

void Entity::rotate(Point point)
{
    RotateAction * rotate_action = new RotateAction(this, point);
    PlayerAction * player_action = static_cast<PlayerAction *>(current_action_);
    player_action->set_next_action(rotate_action);
    player_action->set_next_state(ROTATE);

}

void Entity::attack(Entity * target)
{
    AttackAction * attack_action = new AttackAction(target);
    attack_action->set_range(kPlayerAttackRange);
    attack_action->set_damage(kPlayerAttackDamage);
    PlayerAction * player_action = static_cast<PlayerAction *>(current_action_);
    player_action->stop();
    player_action->set_next_action(attack_action);
    player_action->set_next_state(ATTACK);
}

void Entity::stop()
{
    if(current_action_ != nullptr) {
        current_action_->stop();
    }
}

bool Entity::stopped()
{
    if((x_velocity_ == 0) && (y_velocity_ == 0) && (x_acceleration_ == 0) && (y_acceleration_ == 0)) {
        return true;
    }
    return false;
}
