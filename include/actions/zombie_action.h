#ifndef TLB_ZOMBIE_ACTION_H_
#define TLB_ZOMBIE_ACTION_H_

#include <string>
#include "action.h"
#include "point.h"
#include "entity_manager.h"

const double kZombieAggroRadius = 96;
const double kZombieLeashRadius = 144;
const double kZombieAttackRadius = 48;

class Entity;
class GameObject;
class Game;
class MovementAction;
class RotateAction;
class AttackAction;

enum ZombieState {
    IDLE,
    SEEK,
    ATTACK,
    ATTACK_READY

};

class ZombieAction : public Action
{
    private:
        ZombieState state_;
        EntityManager * entity_manager_;
        Entity * target_;
        Game * game_;

        Point target_last_position;

        MovementAction * movement_action_;
        RotateAction * rotate_action_;
        AttackAction * attack_action_;

    public:
        ZombieAction();

        // accessors
        EntityManager * entity_manager() { return entity_manager_; }
        Game * game() { return game_; }

        // mutators
        void  set_entity_manager(EntityManager * em) { entity_manager_ = em; }
        void  set_game(Game * game) { game_ = game; }

        std::string to_string();

        // overridden
        bool update(Entity * entity, int delta_ticks);
        ActionType type();

};

#endif
