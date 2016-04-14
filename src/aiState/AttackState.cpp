#include "aiState/AttackState.h"
#include "aiState/RotateState.h"
#include "aiState/SeekState.h"
#include "aiState/AIState.h"
#include "aiState/AIStateMachine.h"
#include "util/Logger.h"
#include "Entity.h"
#include "action/AttackAction.h"
#include "action/RotateAction.h"

AttackState::AttackState(AIStateMachine * stateMachine, Entity * entity)
{
    type_ = STATE_ATTACK;
    stateMachine_ = stateMachine;
    entity_ = entity;
    target_ = nullptr;
    attackAction_ = nullptr;
    command_ = false;
    damage_ = 0;
    range_ = 0;
}

AttackState::~AttackState()
{

}

bool AttackState::update(int deltaTicks)
{

    Point position = entity_->position();
    Point targetPosition = Point(target_->xPosition(), target_->yPosition());

    // Only do checks if the next state hasn't been determined yet
    if(stateMachine_->nextState() == nullptr) {
        // Check if we are in range
        if(targetPosition.distanceFrom(position) > attackAction_->range()) {
            if(command_) {
                stateMachine_->setNextState(STATE_SEEK);
                stateMachine_->seekState()->setTarget(target_);
            }
            else {
                stateMachine_->setNextState(STATE_IDLE);
            }
            Logger::write("ATTACK: Target out of attack range");
            return false;
        }

        // Check if we are facing the target
        if(!RotateAction::facing(entity_, target_, attackAction_->arc())) {
            // TODO(2014-09-12/JM): Need to implement a way for the renderer to tell which direction entity is
            // rotating if we end up with a rotation animation at some point
            if(command_ || (entity_->type() == ZOMBIE)) {
                stateMachine_->setNextState(STATE_ROTATE);
                stateMachine_->rotateState()->setPosition(targetPosition);
            }
            else {
                stateMachine_->setNextState(STATE_IDLE);
            }
            Logger::write("ATTACK: Not facing target");
            return false;
        }
    }

    // Perform attack
    //if(nextState_ != BLANK) break;   // NOT SURE WHAT THIS WAS DOING

    bool keepAction = attackAction_->update(entity_, deltaTicks);

    if(!keepAction) {
        if(stateMachine_->nextState() == nullptr) {
            stateMachine_->setNextState(STATE_IDLE);
        }
    }

    return keepAction;
}

void AttackState::stop()
{
    if(attackAction_ != nullptr) {
        attackAction_->stop();
    }
}

void AttackState::start()
{
    Logger::write(Logger::ss << "Entity: " << entity_->objectId() << " - Entering State: ATTACK");
    //attackAction_->reset();
    attackAction_ = new AttackAction(target_);

    attackAction_->setEntity(entity_);
    attackAction_->setDamage(damage_);
    attackAction_->setRange(range_);
    // TODO(2014-09-12/JM): Set attack cooldown and duration



}

void AttackState::end()
{
    Logger::write(Logger::ss << "Entity: " << entity_->objectId() << " - Exiting  State: ATTACK");
    delete attackAction_;
    attackAction_ = nullptr;
    command_ = false;
}

ActionType AttackState::actionType()
{
    if(attackAction_ != nullptr) {
        return attackAction_->type();
    }
    return ACTION_ATTACK;
}
