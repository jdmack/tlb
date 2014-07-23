#ifndef TLB_MOVEMENT_ACTION_H_
#define TLB_MOVEMENT_ACTION_H_

#include <string>
#include "action.h"
#include "point.h"

class Entity;
class GameObject;

class ZombieAction : public Action
{
    private:

    public:
        ZombieAction();

        // accessors

        std::string to_string();

        // overridden
        bool update(Entity * entity, int delta_ticks);
};

#endif
