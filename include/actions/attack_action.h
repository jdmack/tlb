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
        void set_target(Entity * target) { target_ = target; }


        bool update(Entity * entity, int delta_ticks);

};

#endif
