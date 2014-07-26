#ifndef TLB_ZOMBIE_ACTION_H_
#define TLB_ZOMBIE_ACTION_H_

#include <string>
#include "action.h"
#include "point.h"
#include "entity_manager.h"

const double kZombieAggroRadius = 75;
const double kZombieLeashRadius = 100;

class Entity;
class GameObject;
class Game;
class MovementAction;

enum ZombieState {
    IDLE,
    SEEK,
    ATTACK
};

class ZombieAction : public Action
{
    private:
        ZombieState state_;
        EntityManager * entity_manager_;
        Entity * target_;
        Game * game_;

        MovementAction * movement_action_;

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
