#ifndef TLB_PLAYER_ACTION_H_
#define TLB_PLAYER_ACTION_H_

#include <string>
#include "action.h"
#include "point.h"
#include "entity_manager.h"

class Entity;
class GameObject;
class Game;
class MovementAction;
class RotateAction;
class AttackAction;

const double kPlayerAttackRange = 200;
const double kPlayerAttackDamage = 2;
const double kPlayerAttackCooldown = 3000;
const double kPlayerAttackDuration = 500;

enum PlayerState {
    IDLE,
    MOVE,
    ATTACK,
    ROTATE
};

class PlayerAction : public Action
{
    private:
        PlayerState state_;
        EntityManager * entity_manager_;
        Entity * target_;
        Game * game_;

        Point target_last_position;

        MovementAction * movement_action_;
        RotateAction * rotate_action_;
        AttackAction * attack_action_;
        Action * next_action_;

    public:
        PlayerAction();

        // accessors
        EntityManager * entity_manager() { return entity_manager_; }
        Game * game() { return game_; }

        // mutators
        void  set_entity_manager(EntityManager * em) { entity_manager_ = em; }
        void  set_game(Game * game) { game_ = game; }
        void set_next_action(Action * next_action) { next_action_ = next_action; }

        std::string to_string();

        // overridden
        bool update(Entity * entity, int delta_ticks);
        ActionType type();

};

#endif
