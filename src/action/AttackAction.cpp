#include "action/Action.h"
#include "action/AttackAction.h"
#include "Entity.h"
#include "util/Logger.h"

AttackAction::AttackAction()
{
    type_ = ACTION_ATTACK;

    damage_ = 1;
    cooldown_ = Cooldown(3000);
    duration_ = Duration(1000);
    target_ = nullptr;
    arc_ = 60;
    state_ = ATTACKING;
    stopped_ = false;
    cooldownLength_ = 3000;
    durationLength_ = 1000;
    range_ = 0;

    entity_ = nullptr;
}

AttackAction::AttackAction(Entity * target)
{
    type_ = ACTION_ATTACK;

    damage_ = 1;
    cooldown_ = Cooldown(3000);
    duration_ = Duration(1000);
    arc_ = 60;
    target_ = target;
    state_ = ATTACKING;
    duration_.start();
    stopped_ = false;

    cooldownLength_ = 3000;
    durationLength_ = 1000;
    range_ = 0;

    entity_ = nullptr;

}
bool AttackAction::update(Entity * entity, int deltaTicks)
{
    //bool returnValue = true;

    if(target_ == nullptr) {
        Logger::write("Target is NULL");
        return false;
    }
    if(stopped_) {
        return false;
    }
    if(target_->dead()) {
        return false;
    }
    if(entity->position().distanceFrom(target_->position()) > range_) {
        return false;
    }

    switch(state_) {
        case ATTACKING:
            if(duration_.isComplete()) {
                //Logger::write(Logger::ss << "DAMAGE");
                //target_->hp()->minusPoints(damage_);
                target_->takeDamage(damage_, entity_);
                cooldown_.reset();
                state_ = COOLDOWN;
            }
            break;
        case COOLDOWN:
            if(cooldown_.ready()) {
                // Perform attack
                cooldown_.reset();
                state_ = ATTACKING;
                duration_.reset();
            }

           break;
        case STOPPED:
            return false;
            break;
    }

    return true;
}

ActionType AttackAction::type()
{
    switch(state_) {
        case COOLDOWN:
            type_ = ACTION_IDLE;
            break;
        case ATTACKING:
            type_ = ACTION_ATTACK;
            break;
        case STOPPED:
            break;
    }

    return type_;
}

void AttackAction::reset()
{
    cooldown_.reset();
    duration_.start();
    state_ = ATTACKING;
}
void AttackAction::stop()
{
    state_ = STOPPED;
    stopped_ = true;

}
