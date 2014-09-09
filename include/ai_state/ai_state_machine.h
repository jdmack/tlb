#ifndef TLB_AI_STATE_AI_STATE_MACHINE_H_
#define TLB_AI_STATE_AI_STATE_MACHINE_H_

class Entity;
class State;

class AIStateMachine
{
    private:
        Entity * entity_;
        State * current_state_;
        State * previous_state_;
        State * next_state_;
        State * global_state_;

    public:
        AIStateMachine();
        ~AIStateMachine();

        // accessors
        Entity * entity() { return entity_; }

        // mutators
        void set_entity(Entity * entity) { entity_ = entity; }
        void set_current_state(State * current_state) { current_state_ = current_state; }
        void set_previous_state(State * previous_state) { previous_state_ = previous_state; }
        void set_next_state(State * next_state) { next_state_ = next_state; }
        void set_global_state(State * global_state) { global_state_ = global_state; }

        bool update(Entity * entity, int delta_ticks);
        void stop();

};

#endif
