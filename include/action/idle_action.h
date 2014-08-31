#ifndef TLB_IDLE_ACTION_H_
#define TLB_IDLE_ACTION_H_

#include <string>

class Entity;

class IdleAction : public Action
{
    private:

    public:
        IdleAction();

        bool update(Entity * entity, int delta_ticks);

};

#endif
