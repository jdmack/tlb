#ifndef TLB_DEAD_ACTION_H_
#define TLB_DEAD_ACTION_H_

#include <string>

class Entity;

class DeadAction : public Action
{
    private:

    public:
        DeadAction();

        bool update(Entity * entity, int deltaTicks);

};

#endif
