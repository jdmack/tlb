#ifndef TLB_IDLE_ACTION_H_
#define TLB_IDLE_ACTION_H_

#include <string>

class Entity;

class IdleAction
{
    private:

    public:
        IdleAction();

        bool update(Entity * entity, int delta_ticks);
        bool is_idle() const { return true; }


};

#endif
