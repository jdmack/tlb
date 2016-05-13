#include <cmath>

#include "SDL2/SDL.h"

#include "Entity.h"
#include "Assets.h"
#include "Point.h"
#include "Game.h"
#include "Level.h"
#include "action/MoveAction.h"
#include "action/DeadAction.h"
#include "action/Action.h"
#include "action/AttackAction.h"
#include "action/RotateAction.h"
#include "Movement.h"
#include "gfx/Renderer.h"
#include "gfx/Sprite.h"
#include "Vector.h"
#include "util/Logger.h"
#include "aiState/AIStateMachine.h"

Entity::Entity(EntityType type) : GameObject()
{
    type_ = type;

    xVelocity_ = 0;
    yVelocity_ = 0;

    width_  = kEntityWidth;
    height_ = kEntityHeight;

    hp_ = new HitPoint(10);

    selectable_ = true;
    controllable_ = false;

    maximumSpeed_ = kEntityDefaultVelocity;

    dead_ = false;

    stateMachine_ = new AIStateMachine(this);
}

Entity::Entity(EntityType type, Point position, double rot) : GameObject(position, rot)
{
    type_ = type;

    xVelocity_ = 0;
    yVelocity_ = 0;

    width_  = kEntityWidth;
    height_ = kEntityHeight;

    hp_ = new HitPoint(10);

    selectable_ = true;
    controllable_ = false;

    maximumSpeed_ = kEntityDefaultVelocity;

    dead_ = false;
    stateMachine_ = new AIStateMachine(this);
}

void Entity::update(int deltaTicks)
{
    // TODO(2014-08-21/JM): Can create a DeadAction that contains a duration to trigger DYING animation
    // and then will be a DEAD state

    if(stateMachine_ != nullptr) {
        stateMachine_->update(deltaTicks);
    }
    //model_.transform().translate(position_.x(), 0, position_.y());
    model_.transform().translate(xPosition_, 0, yPosition_);
}

bool Entity::containsPoint(double x, double y)
{
    //if((x < (xAbs_ - (width_ / 2))) || (x > (xAbs_ + (width_ / 2)))) {
    if((x < (xPosition_ - (width_ / 2))) || (x > (xPosition_ + (width_ / 2)))) {
        return false;
    }
    //else if((y < (yAbs_ - (width_ / 2))) || (y > (yAbs_ + (height_ / 2)))) {
    else if((y < (yPosition_ - (width_ / 2))) || (y > (yPosition_ + (height_ / 2)))) {
        return false;
    }

    return true;
}

//void Entity::select()
//{
//    Logger::write(Logger::ss << "Entity::select objectId: " << objectId_ << " (x,y): (" << xPosition_ << ", " <<  yPosition_ << ")");
//    //GameObject::select();
//}

//void Entity::deselect()
//{
//    Logger::write("Entity::deselect");
//    selected_ = false;
//}

void Entity::move(Point point)
{
    // TODO(2014-11-05/JM): May want to add distinction between "move" and "moveCommand". Depends on if there
    // is ever need for the case of an AI or event issuing a move directive to non-controllable entities
    if(controllable_) {
        Logger::write(Logger::ss << "Move - (x,y): (" << point.x() << "," << point.y() << ")");
        stateMachine_->moveCommand(point);
    }
}

void Entity::rotate(Point point)
{
    Logger::write(Logger::ss << "Rotate - " << point.toString());
    stateMachine_->rotateCommand(point);
}

void Entity::attack(Entity * target)
{
    Logger::write(Logger::ss << "Attack - (Entity): (" << target->objectId() << ")");
    stateMachine_->attackCommand(target);
}

void Entity::stop()
{
    stateMachine_->stop();
}

bool Entity::stopped()
{
    if((xVelocity_ == 0) && (yVelocity_ == 0) && (xAcceleration_ == 0) && (yAcceleration_ == 0)) {
        return true;
    }
    return false;
}

ActionType Entity::actionType()
{
    return stateMachine_->actionType();   
}

void Entity::setDead(bool dead)
{
    dead_ = dead;
    selectable_ = !dead;
    controllable_ = !dead;
}

void Entity::takeDamage(int damage, Entity * attacker)
{
    hp_->minusPoints(damage);
    stateMachine_->aggro(attacker);
}
