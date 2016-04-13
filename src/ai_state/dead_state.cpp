#include "aiState/deadState.h"
#include "aiState/aiState.h"
#include "aiState/aiStateMachine.h"
#include "action/action.h"
#include "entity.h"
#include "util/logger.h"

DeadState::DeadState(AIStateMachine * stateMachine, Entity * entity)
{
    type_ = STATE_DEAD;
    stateMachine_ = stateMachine;
    entity_ = entity;
}

DeadState::~DeadState()
{

}

bool DeadState::update(int deltaTicks)
{
    return true;
}

void DeadState::stop()
{

}

void DeadState::start()
{
    Logger::write(Logger::ss << "Entity: " << entity_->objectId() << " - Entering State: DEAD");
}

void DeadState::end()
{
    Logger::write(Logger::ss << "Entity: " << entity_->objectId() << " - Exiting  State: DEAD");
}

ActionType DeadState::actionType()
{
    return ACTION_DEAD;
}
