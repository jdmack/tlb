#include <cmath>
#include <vector>
#include <iostream>
#include <sstream>
#include <string>

#include "actions/action.h"
#include "actions/player_action.h"
#include "actions/movement_action.h"
#include "actions/rotate_action.h"
#include "actions/attack_action.h"

#include "game_object.h"
#include "point.h"
#include "utils/logger.h"
#include "entity.h"
#include "entity_manager.h"
#include "game.h"
#include "movement.h"

PlayerAction::PlayerAction()
{
    state_ = IDLE;
    target_ = nullptr;
    entity_manager_ = nullptr;
    movement_action_ = nullptr;
    rotate_action_ = nullptr;
    attack_action_ = new AttackAction();
    attack_action_->set_damage(kPlayerAttackDamage);
    attack_action_->set_cooldown_length(kPlayerAttackCooldown);
    attack_action_->set_duration_length(kPlayerAttackDuration);
    next_action_ = nullptr;
    game_ = nullptr;
    type_ = ACTION_IDLE;
}

bool PlayerAction::update(Entity * entity, int delta_ticks)
{
    Point position = Point(entity->x_position(), entity->y_position());
    Point target_position;
    std::vector<Entity *> entities;

    if(next_action_ != nullptr) {
        switch(state_) {
            case IDLE:
                break;
            case MOVE:
                if(movement_action_ != nullptr) movement_action_->stop();
                break;
            case ATTACK:
                //if(attack_action_ != nullptr) attack_action_->stop();
                break;
        }
    }

    switch(state_) {
        case IDLE:
            if(next_action_ != nullptr) {
                if(next_action_->type() == ACTION_MOVEMENT) {
                    movement_action_ = static_cast<MovementAction *>(next_action_);
                    next_action_ = nullptr;
                    state_ = MOVE;
                }
            }

            //Logger::write(Logger::string_stream << "PlayerAction: IDLE");
           /*
            entities = entity_manager_->get_entities_near(position, kPlayerAttackRange);

            //TODO(2014-07-24/JM): Choose way of selecting target if there are multiple
            while(target_ == nullptr) {
                if(entities.empty()) {
                    //Logger::write(Logger::string_stream << "Found nothing nearby");
                    return true;
                }
                if(entities.back()->object_id() == entity->object_id()) {
                    entities.pop_back();
                    continue;
                }
                if(entities.back()->type() == PLAYER) {
                    entities.pop_back();
                    continue;
                }
                target_ = entities.back();
                entities.pop_back();
            }
            state_ = ATTACK;
            */
            break;

        case MOVE:
            if(movement_action_ != nullptr) {
                // Perform movement
                bool keep_action = movement_action_->update(entity, delta_ticks);

                if(!keep_action) {
                    delete movement_action_;
                    movement_action_ = nullptr;
                    state_ = IDLE;
                    if(next_action_ != nullptr) {
                        if(next_action_->type() == ACTION_MOVEMENT) {
                            movement_action_ = static_cast<MovementAction *>(next_action_);
                            next_action_ = nullptr;
                            Point end = movement_action_->end();
                            MovementAction * new_movement_action = new MovementAction(entity->position(), end, movement_action_->level());
                            delete movement_action_;
                            movement_action_ = new_movement_action;
                            state_ = MOVE;
                        }
                    }
                }
            }

            break;

        case ATTACK:
            /*
            // Update rotate action if rotating
            if(rotate_action_ != nullptr) {
                bool keep_action = rotate_action_->update(entity, delta_ticks);
                if(!keep_action) {
                    delete rotate_action_;
                    rotate_action_ = nullptr;
                }
            }

            target_position = Point(target_->x_position(), target_->y_position());

            // Check if we are in range
            if(target_position.distance_from(position) > kZombieAttackRadius) {

                if(attack_action_ != nullptr) {
                    delete attack_action_;
                    attack_action_ = nullptr;
                }

               // Create movement action
               movement_action_ = new MovementAction(position, Point(target_->x_position(), target_->y_position()), game_->level());
               movement_action_->remove_movements_back();
               if(movement_action_->empty_path()) {
                   break;
               }
               state_ = SEEK;
               break;
            }
            // Check if we are facing the target
            if(!RotateAction::facing(entity, target_)) {
                // TODO(2014-08-21/JM): This rotation code will not result in the rotating being animated  because there is no change
                // of state to a state of rotating.
                if(attack_action_ != nullptr) {
                    delete attack_action_;
                    attack_action_ = nullptr;
                }
                rotate_action_ = new RotateAction(entity, target_->position());
                bool keep_action = rotate_action_->update(entity, delta_ticks);

                if(!keep_action) {
                    delete rotate_action_;
                    rotate_action_ = nullptr;
                    attack_action_ = new AttackAction(target_);
                }
                break;
            }

            // All checks good, attack
            if(attack_action_ == nullptr) {
                attack_action_ = new AttackAction(target_);
            }
            Logger::write(Logger::string_stream << "HERE");
            bool keep_action = attack_action_->update(entity, delta_ticks);

            if(!keep_action) {
                delete attack_action_;
                attack_action_ = nullptr;
            }
               */

            break;
    }
    return true;
}

ActionType PlayerAction::type()
{
    switch(state_) {
        case IDLE:
            type_ = ACTION_IDLE;
            break;
        case MOVE:
            type_ = ACTION_MOVEMENT;
            break;
        case ATTACK:
            if(attack_action_ != nullptr) {
                type_ = attack_action_->type();
            }
            else {
                type_ = ACTION_IDLE;
            }
            break;
    }

    return type_;
}


std::string PlayerAction::to_string()
{
	//for (std::list<GridNode *>::iterator iterator = nodes->begin(), end = nodes->end(); iterator != end; ++iterator) {
	//    Logger::string_stream << "(" << (**iterator).row() << ", " << (**iterator).column() << ") ";
	//}
	return "";
}

