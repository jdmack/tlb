#include "aiState/idleState.h"
#include "aiState/seekState.h"
#include "aiState/attackState.h"
#include "aiState/aiState.h"
#include "aiState/aiStateMachine.h"
#include "action/action.h"
#include "action/rotateAction.h"
#include "entity.h"
#include "game.h"
#include "entityManager.h"
#include "util/logger.h"

IdleState::IdleState(AIStateMachine * stateMachine, Entity * entity)
{
    type_ = STATE_IDLE;
    stateMachine_ = stateMachine;
    entity_ = entity;
    stop_ = false;
}

IdleState::~IdleState()
{

}

bool IdleState::update(int deltaTicks)
{
    Point position = entity_->position();
    std::vector<Entity *> entities;

    // Check if another action has been set
    if(stop_) {
        return false;
    }

    if(entity_->type() == PLAYER) {

        // PLAYER

        // Check for entities within Aggro Range
        entities = Game::instance()->entityManager()->getEntitiesNear(position, kPlayerAttackRange);
        Entity * target = nullptr;

        //TODO(2014-07-24/JM): Choose way of selecting target if there are multiple
        while(target == nullptr) {
            if(entities.empty()) {
                //Logger::write(Logger::ss << "Found nothing nearby");
                return true;
            }
            if(entities.back()->objectId() == entity_->objectId()) {
                entities.popBack();
                continue;
            }
            if(entities.back()->dead()) {
                entities.popBack();
                continue;
            }
            if(entities.back()->type() != ZOMBIE) {
                entities.popBack();
                continue;
            }
            // Check in arc
            if(!RotateAction::facing(entity_, entities.back(), 60)) {
                entities.popBack();
                continue;
            }

            // Found a target, setup next action
            target = entities.back();
            entities.popBack();

            if(target != nullptr) {
                // Found target, decide next action
                stateMachine_->attackState()->setTarget(target);
                stateMachine_->setNextState(STATE_ATTACK);
                return false;
            }

            return true;

        }
        return false;
    }
    else {
        // ZOMBIE

        // Check for entities within Aggro Range
        entities = Game::instance()->entityManager()->getEntitiesNear(position, kZombieAggroRadius);
        Entity * target = nullptr;

        //TODO(2014-07-24/JM): Choose way of selecting target if there are multiple
        while(target == nullptr) {
            if(entities.empty()) {
                //Logger::write(Logger::ss << "Found nothing nearby");
                return true;
            }
            if(entities.back()->objectId() == entity_->objectId()) {
                entities.popBack();
                continue;
            }
            if(entities.back()->dead()) {
                entities.popBack();
                continue;
            }
            if(entities.back()->type() == ZOMBIE) {
                entities.popBack();
                continue;
            }

            // Found a target, setup next action
            target = entities.back();
            entities.popBack();
        }

        if(target != nullptr) {
            // Found target, decide next action
            stateMachine_->seekState()->setTarget(target);
            stateMachine_->setNextState(STATE_SEEK);
            return false;
        }

        return true;
    }
}

void IdleState::stop()
{
    stop_ = true;
}

void IdleState::start()
{
    Logger::write(Logger::ss << "Entity: " << entity_->objectId() << " - Entering State: IDLE");
    stop_ = false;
}

void IdleState::end()
{
    Logger::write(Logger::ss << "Entity: " << entity_->objectId() << " - Exiting  State: IDLE");
}

ActionType IdleState::actionType()
{
    return ACTION_IDLE;
}
