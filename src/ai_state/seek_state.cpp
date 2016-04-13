#include "aiState/seekState.h"
#include "aiState/idleState.h"
#include "aiState/attackState.h"
#include "aiState/aiStateMachine.h"
#include "util/logger.h"
#include "entity.h"
#include "action/moveAction.h"
#include "game.h"

SeekState::SeekState(AIStateMachine * stateMachine, Entity * entity)
{
    type_ = STATE_SEEK;
    stateMachine_ = stateMachine;
    entity_ = entity;
    moveAction_ = nullptr;
    target_ = nullptr;
}

SeekState::~SeekState()
{

}

bool SeekState::update(int deltaTicks)
{
    // Only do state transition checks if nextState hasn't been chosen yet
    if(stateMachine_->nextState() == nullptr) {

        if(target_ == nullptr) {
            // switch to IDLE
            stateMachine_->setNextState(STATE_IDLE);
            return false;
        }

        Point position = entity_->position();

        // check if target has exceeded leash range
        if(entity_->type() == ZOMBIE) {
            if(position.distanceFrom(Point(target_->xPosition(), target_->yPosition())) > kZombieLeashRadius) {
                moveAction_->stop();
                stateMachine_->setNextState(STATE_IDLE);

                Logger::write("SEEK: Out of leash range");
                Logger::write(Logger::ss << position.distanceFrom(Point(target_->xPosition(), target_->yPosition())));

                Point targetPosition = Point(target_->xPosition(), target_->yPosition());
                Point entityPosition = Point(entity_->xPosition(), entity_->yPosition());

                Logger::write(Logger::ss << "Entity Position: " << entityPosition.toString());
                Logger::write(Logger::ss << "Target Position: " << targetPosition.toString());
            }
        }

        // check if target has moved far from we think it is
        // TODO(2014-08-15/JM): Hard coded number 12 here for distance, change
        else if(targetLastPosition_.distanceFrom(target_->position()) >= 12) {
            moveAction_->stop();
            stateMachine_->setNextState(STATE_SEEK);
            Logger::write("SEEK: Recalculating movement to target");
        }

        // check if we are in attack range
        else if(entity_->position().distanceFrom(target_->position()) <= stateMachine_->attackState()->range()) {
            moveAction_->stop();
            stateMachine_->setNextState(STATE_ATTACK);
            stateMachine_->attackState()->setTarget(target_);
        }

    }

    // Perform movement

    bool keepAction = moveAction_->update(entity_, deltaTicks);

    if(!keepAction) {
        if(stateMachine_->nextState() == nullptr) {
            stateMachine_->attackState()->setTarget(target_);
            stateMachine_->setNextState(STATE_ATTACK);
        }
    }

    return keepAction;
}

void SeekState::stop()
{
    if(moveAction_ != nullptr) {
        moveAction_->stop();
    }
}

void SeekState::start()
{
    Logger::write(Logger::ss << "Entity: " << entity_->objectId() << " - Entering State: SEEK");

    moveAction_ = new MoveAction(entity_->position(), target_->position(), Game::instance()->level());
    moveAction_->removeMovementsBack();
    targetLastPosition_ = Point(target_->xPosition(), target_->yPosition());

}

void SeekState::end()
{
    Logger::write(Logger::ss << "Entity: " << entity_->objectId() << " - Exiting  State: SEEK");
    delete moveAction_;
    moveAction_ = nullptr;
}

ActionType SeekState::actionType()
{
    return ACTION_MOVE;
}
