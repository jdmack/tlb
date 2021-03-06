#ifndef TLB_ACTION_ACTION_H_
#define TLB_ACTION_ACTION_H_

#include <string>

enum ActionType {
    ACTION_MOVE,
    ACTION_IDLE,
    ACTION_ROTATE,
    ACTION_ZOMBIE,
    ACTION_SEEK,
    ACTION_ATTACK,
    ACTION_DEAD
};

class Entity;

class Action
{
    protected:
        ActionType type_;

    public:
        Action();

        // accessors
        virtual ActionType type() { return type_; }

        virtual ~Action();
        virtual bool update(Entity * entity, int deltaTicks);
        virtual void stop();

};

#endif
