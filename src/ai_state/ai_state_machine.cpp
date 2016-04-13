#include "aiState/aiStateMachine.h"
#include "aiState/aiState.h"
#include "aiState/attackState.h"
#include "aiState/deadState.h"
#include "aiState/idleState.h"
#include "aiState/moveState.h"
#include "aiState/rotateState.h"
#include "aiState/seekState.h"
#include "aiState/globalState.h"
#include "point.h"
#include "entity.h"

AIStateMachine::AIStateMachine(Entity * entity)
{
    entity_ = entity;
    currentState_ = nullptr;;
    previousState_ = nullptr;;
    nextState_ = nullptr;

    globalState_ = new GlobalState(this, entity);

    attackState_ = new AttackState(this, entity);
    deadState_ = new DeadState(this, entity);
    idleState_ = new IdleState(this, entity);
    moveState_ = new MoveState(this, entity);
    rotateState_ = new RotateState(this, entity);
    seekState_ = new SeekState(this, entity);

    if(entity_->type() == PLAYER) {
        attackState_->setDamage(kPlayerAttackDamage);
        attackState_->setRange(kPlayerAttackRange);
    }
    else if(entity_->type() == ZOMBIE) {
        attackState_->setDamage(kZombieAttackDamage);
        attackState_->setRange(kZombieAttackRange);
    }
}

AIStateMachine::~AIStateMachine()
{
    delete attackState_;
    delete deadState_;
    delete idleState_;
    delete moveState_;
    delete rotateState_;
    delete seekState_;

}

bool AIStateMachine::update(int deltaTicks)
{
    // Start up the state machine if needed
    if(currentState_ == nullptr) {
        currentState_ = idleState_;
        currentState_->start();
    }

    // Run global checks
    globalState_->update(deltaTicks);

    // Check if dead
    if((nextState_ != nullptr) && (nextState_->type() == STATE_DEAD)) {
        currentState_->end();
        previousState_ = currentState_;
        currentState_ = nextState_;
        currentState_->start();
        nextState_ = nullptr;
    }

    bool keepAction = currentState_->update(deltaTicks);

    // TODO(2014-09-09/JM): Eventually make it so that when a state finishes, it responds with how many deltaTicks need to be run
    // in the next state and update() the new state with the remaining ticks

    if(!keepAction) {
        currentState_->end();

        if(nextState_ == nullptr) {
            if(previousState_ == nullptr) {
                currentState_ = staticCast<AIState *>(idleState_);
            }
            else {
                currentState_ = previousState_;
                previousState_ = nullptr;
            }
        }
        else {
            previousState_ = currentState_;
            currentState_ = nextState_;
            nextState_ = nullptr;
        }

        currentState_->start();
    }

    return true;
}

void AIStateMachine::stop()
{
    if(currentState_ != nullptr) {
        currentState_->stop();
    }
}

void AIStateMachine::moveCommand(Point destination)
{
    currentState_->stop();
    nextState_ = moveState_;
    moveState_->setDestination(destination);
}

void AIStateMachine::attackCommand(Entity * target)
{
    currentState_->stop();
    nextState_ = attackState_;
    attackState_->setTarget(target);
    attackState_->setCommand(true);
}

void AIStateMachine::rotateCommand(Point position)
{
    currentState_->stop();
    nextState_ = rotateState_;
    rotateState_->setPosition(position);
}

void AIStateMachine::aggro(Entity * target)
{
    if(entity_->type() == PLAYER) {
        return;
    }
    if(currentState_ != nullptr) {
        if(currentState_->type() == STATE_IDLE) {
            currentState_->stop();
            nextState_ = seekState_;
            seekState_->setTarget(target);
        }
    }
}

ActionType AIStateMachine::actionType()
{
    if(currentState_ != nullptr) {
        return currentState_->actionType();
    }
    return ACTION_IDLE;
}

void AIStateMachine::setNextState(AIStateType type)
{
    switch(type) {
        case STATE_ATTACK:
            nextState_ = attackState_;
            break;

        case STATE_DEAD:
            nextState_ = deadState_;
            break;

        case STATE_IDLE:
            nextState_ = idleState_;
            break;

        case STATE_MOVE:
            nextState_ = moveState_;
            break;

        case STATE_ROTATE:
            nextState_ = rotateState_;
            break;

        case STATE_SEEK:
            nextState_ = seekState_;
            break;
        case STATE_GLOBAL:
            break;

    }
}

void AIStateMachine::setPreviousState(AIStateType type)
{
    switch(type) {
        case STATE_ATTACK:
            previousState_ = attackState_;
            break;

        case STATE_DEAD:
            previousState_ = deadState_;
            break;

        case STATE_IDLE:
            previousState_ = idleState_;
            break;

        case STATE_MOVE:
            previousState_ = moveState_;
            break;

        case STATE_ROTATE:
            previousState_ = rotateState_;
            break;

        case STATE_SEEK:
            previousState_ = seekState_;
            break;
        case STATE_GLOBAL:
            break;
    }
}
