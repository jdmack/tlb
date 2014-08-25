#include "actions/action.h"
#include "actions/attack_action.h"
#include "entity.h"
#include "utils/logger.h"

AttackAction::AttackAction()
{
    type_ = ACTION_ATTACK;

    damage_ = 1;
    cooldown_ = Cooldown(3000);
    duration_ = Duration(1000);
    target_ = nullptr;
    state_ = ATTACKING;
}

AttackAction::AttackAction(Entity * target)
{
    type_ = ACTION_ATTACK;

    damage_ = 1;
    cooldown_ = Cooldown(3000);
    duration_ = Duration(1000);
    target_ = target;
    state_ = ATTACKING;
    duration_.start();

}
bool AttackAction::update(Entity * entity, int delta_ticks)
{
    bool return_value = true;

    if(target_->dead()) {
        return false;
    }
    Logger::write(Logger::string_stream << "Attacking");

    switch(state_) {
        case ATTACKING:
            if(duration_.is_complete()) {
                //Logger::write(Logger::string_stream << "DAMAGE");
                target_->hp()->minus_points(damage_);
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
}
