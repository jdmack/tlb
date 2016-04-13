#include "aiState/rotateState.h"
#include "aiState/aiState.h"
#include "point.h"
#include "action/action.h"
#include "action/rotateAction.h"
#include "game.h"
#include "entity.h"
#include "util/logger.h"

RotateState::RotateState(AIStateMachine * stateMachine, Entity * entity)
{
    type_ = STATE_ROTATE;
    stateMachine_ = stateMachine;
    entity_ = entity;
    position_ = Point(0, 0);
    rotateAction_ = nullptr;
}

RotateState::~RotateState()
{

}

bool RotateState::update(int deltaTicks)
{
    bool keepAction = rotateAction_->update(entity_, deltaTicks);

    return keepAction;
}

void RotateState::stop()
{
    if(rotateAction_ != nullptr) {
        rotateAction_->stop();
    }
}

void RotateState::start()
{
    Logger::write(Logger::ss << "Entity: " << entity_->objectId() << " - Entering State: ROTATE");
    // Create rotate action
    rotateAction_ = new RotateAction(entity_, position_);
}

void RotateState::end()
{
    Logger::write(Logger::ss << "Entity: " << entity_->objectId() << " - Exiting  State: ROTATE");
    // clear out old data
    delete rotateAction_;
    rotateAction_ = nullptr;
}

ActionType RotateState::actionType()
{
    return ACTION_ROTATE;
}
