#include "aiState/globalState.h"
#include "aiState/aiState.h"
#include "aiState/aiStateMachine.h"
#include "util/logger.h"
#include "entity.h"
#include "action/action.h"

GlobalState::GlobalState(AIStateMachine * stateMachine, Entity * entity)
{
    type_ = STATE_GLOBAL;
    stateMachine_ = stateMachine;
    entity_ = entity;
}

GlobalState::~GlobalState()
{

}

bool GlobalState::update(int deltaTicks)
{
    // Check if dead
    if(stateMachine_->currentState()->type() != STATE_DEAD) {
        if(entity_->hp()->empty()) {
            entity_->setDead(true);
            stateMachine_->setNextState(STATE_DEAD);
        }
    }
    return true;
}

void GlobalState::stop()
{

}

void GlobalState::start()
{
}

void GlobalState::end()
{
}

ActionType GlobalState::actionType()
{
    return ACTION_IDLE;
}
