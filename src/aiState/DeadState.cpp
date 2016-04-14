#include "aiState/DeadState.h"
#include "aiState/AIState.h"
#include "aiState/AIStateMachine.h"
#include "action/Action.h"
#include "Entity.h"
#include "util/Logger.h"

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
