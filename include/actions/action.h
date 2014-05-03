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

        // accessors
        std::string type() const { return type_; }

        virtual ~Action();
        virtual bool update(Entity * entity, int delta_ticks);

        // determination functions
        virtual bool is_idle() const { return false; }
        virtual bool is_movement() const { return false; }

};

#endif
