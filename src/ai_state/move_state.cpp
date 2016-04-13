#include "aiState/moveState.h"
#include "aiState/aiState.h"
#include "aiState/aiStateMachine.h"
#include "point.h"
#include "action/action.h"
#include "action/moveAction.h"
#include "game.h"
#include "entity.h"
#include "util/logger.h"

MoveState::MoveState(AIStateMachine * stateMachine, Entity * entity)
{
    type_ = STATE_MOVE;
    stateMachine_ = stateMachine;
    entity_ = entity;
    destination_ = Point(0, 0);
    moveAction_ = nullptr;
}

MoveState::~MoveState()
{

}

bool MoveState::update(int deltaTicks)
{
    bool keepAction = moveAction_->update(entity_, deltaTicks);
    if(!keepAction) {
        stateMachine_->setPreviousState(nullptr);
    }

    return keepAction;
}

void MoveState::stop()
{
    if(moveAction_ != nullptr) {
        moveAction_->stop();
    }
}

void MoveState::start()
{
    Logger::write(Logger::ss << "Entity: " << entity_->objectId() << " - Entering State: MOVE");
    // Create move action
    moveAction_ = new MoveAction(entity_->position(), destination_, Game::instance()->level());
    if(moveAction_->emptyPath()) {
        //Logger::write("Empty path, cancelling Move");
        return;
    }

}

void MoveState::end()
{
    Logger::write(Logger::ss << "Entity: " << entity_->objectId() << " - Exiting  State: MOVE");
    // clear out old data
    delete moveAction_;
    moveAction_ = nullptr;
}

ActionType MoveState::actionType()
{
    return ACTION_MOVE;
}
