#ifndef TLB_ATTACK_ACTION_H_
#define TLB_ATTACK_ACTION_H_

#include <string>
#include "Cooldown.h"
#include "Duration.h"

enum AttackStateType {
    ATTACKING,
    COOLDOWN,
    STOPPED
};

class Entity;

class AttackAction : public Action
{
    private:
        bool stopped_;
        int damage_;
        int cooldownLength_;
        int durationLength_;
        double arc_;
        double range_;
        AttackStateType state_;
        Cooldown cooldown_;
        Duration duration_;
        Entity * entity_;
        Entity * target_;

    public:
        AttackAction();
        AttackAction(Entity * target);

        // accessors
        int damage() const { return damage_; }
        double arc() const { return arc_; }
        double range() const { return range_; }
        Entity * entity() { return entity_; }
        Entity * target() { return target_; }

        // mutators
        void setDamage(int damage) { damage_ = damage; }
        void setRange(double range) { range_ = range; }
        void setCooldownLength(int cooldownLength) { cooldownLength_ = cooldownLength; cooldown_.setLength(cooldownLength_);}
        void setDurationLength(int durationLength) { durationLength_ = durationLength; duration_.setLength(durationLength_);}
        void setArc(double arc) { arc_ = arc; }
        void setEntity(Entity * entity) { entity_ = entity; }
        void setTarget(Entity * target) { target_ = target; }

        void reset();
        void stop();

        // overridden
        bool update(Entity * entity, int deltaTicks);
        ActionType type();

};

#endif
