#ifndef TLB_ACTION_H_
#define TLB_ACTION_H_

#include <string>

const std::string kActionMovement = "MovementAction";
const std::string kActionIdle    = "IdleAction";
const std::string kActionEmpty    = "EmptyAction";

class Entity;

class Action
{
    protected:
        std::string type_;

    public:
        Action();

        std::string type() const { return type_; }

        virtual ~Action();
        virtual bool is_movement() const { return false; }
        virtual bool update(Entity * entity, int delta_ticks);

};

#endif
