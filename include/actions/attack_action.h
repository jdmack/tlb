#ifndef TLB_ATTACK_ACTION_H_
#define TLB_ATTACK_ACTION_H_

#include <string>
#include "cooldown.h"
#include "duration.h"

enum AttackState {
    ATTACKING,
    COOLDOWN
};

class Entity;

class AttackAction : public Action
{
    private:
        int damage_;
        int cooldown_length_;
        int duration_length_;
        AttackState state_;
        Cooldown cooldown_;
        Duration duration_;
        Entity * target_;

    public:
        AttackAction();
        AttackAction(Entity * target);

        // accessors
        int damage() const { return damage_; }
        Entity * target() { return target_; }

        // mutators
        void set_damage(int damage) { damage_ = damage; }
        void set_cooldown_length(int cooldown_length) { cooldown_length_ = cooldown_length; cooldown_.set_length(cooldown_length_);}
        void set_duration_length(int duration_length) { duration_length_ = duration_length; duration_.set_length(duration_length_);}
        void set_target(Entity * target) { target_ = target; }

        // overridden
        bool update(Entity * entity, int delta_ticks);
        ActionType type();

};

#endif
