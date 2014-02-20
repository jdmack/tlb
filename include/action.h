#ifndef TLB_ACTION_H_
#define TLB_ACTION_H_

#include <string>

const std::string kActionMovement = "MovementAction";
const std::string kActionIdle    = "IdleAction";
const std::string kActionEmpty    = "EmptyAction";

class Action
{
    protected:
        std::string type_;

    public:
        Action();

        std::string type() const { return type_; }

        virtual ~Action();
        virtual bool is_movement() const { return false; }

};

#endif
