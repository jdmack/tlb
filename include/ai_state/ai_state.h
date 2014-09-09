#ifndef TLB_AI_STATE_AI_STATE_H_
#define TLB_AI_STATE_AI_STATE_H_

enum AIStateType {
    IDLE_STATE
};

class Entity;

class AIState
{
    protected:
        AIStateType type_;

    public:
        AIState();
        virtual ~AIState();

        // accessors
        AIStateType type() { return type_; }

        virtual bool update(Entity * entity, int delta_ticks);
        virtual void stop();
        virtual void start();
        virtual void end();

};

#endif
