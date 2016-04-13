#ifndef TLB_AI_STATE_AI_STATE_MACHINE_H_
#define TLB_AI_STATE_AI_STATE_MACHINE_H_

#include "action/action.h"
#include "point.h"
#include "aiState/aiState.h"

class Entity;
class AIState;
class AttackState;
class DeadState;
class IdleState;
class MoveState;
class RotateState;
class SeekState;
class GlobalState;

class AIStateMachine
{
    private:
        Entity * entity_;
        AIState * currentState_;
        AIState * previousState_;
        AIState * nextState_;
        GlobalState * globalState_;

        AttackState * attackState_;
        DeadState * deadState_;
        IdleState * idleState_;
        MoveState * moveState_;
        RotateState * rotateState_;
        SeekState * seekState_;

    public:
        AIStateMachine(Entity * entity);
        ~AIStateMachine();

        // accessors
        Entity * entity() { return entity_; }
        AIState * currentState() { return currentState_; }
        AIState * previousState() { return previousState_; }
        AIState * nextState() { return nextState_; }
        GlobalState * globalState() { return globalState_; }
        AttackState * attackState() { return attackState_; }
        DeadState * deadState() { return deadState_; }
        IdleState * idleState() { return idleState_; }
        MoveState * moveState() { return moveState_; }
        RotateState * rotateState() { return rotateState_; }
        SeekState * seekState() { return seekState_; }

        // mutators
        void setEntity(Entity * entity) { entity_ = entity; }
        void setCurrentState(AIState * currentState) { currentState_ = currentState; }
        void setPreviousState(AIState * previousState) { previousState_ = previousState; }
        void setNextState(AIState * nextState) { nextState_ = nextState; }
        void setGlobalState(GlobalState * globalState) { globalState_ = globalState; }

        void setNextState(AIStateType type);
        void setPreviousState(AIStateType type);

        void moveCommand(Point destination);
        void attackCommand(Entity * target);
        void rotateCommand(Point position);
        void aggro(Entity * target);

        bool update(int deltaTicks);
        void stop();
        ActionType actionType();

};

#endif
