#include <cmath>
#include <vector>
#include <iostream>
#include <sstream>
#include <string>

#include "actions/action.h"
#include "actions/player_action.h"
#include "actions/move_action.h"
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
    next_state_ = BLANK;
    target_ = nullptr;
    entity_manager_ = nullptr;
    move_action_ = nullptr;
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
    bool keep_action = true;
    Point position = Point(entity->x_position(), entity->y_position());
    Point target_position;
    std::vector<Entity *> entities;


    // Check conditions
    if(next_state_ == BLANK) {
        switch(state_) {
            case IDLE:
                /*
                // Check for entities within Aggro Range in the direction we're facing
                entities = entity_manager_->get_entities_near(position, kZombieAggroRadius);

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
                    if(entities.back()->type() == ZOMBIE) {
                        entities.pop_back();
                        continue;
                    }
                    target_ = entities.back();
                    attack_action_ = new AttackAction(target_);
                    Logger::write("IDLE: Found entity");
                    entities.pop_back();
                }
                if(target_ != nullptr) {
                    next_state_ = SEEK;
                }
                */
                break;
            case MOVE:
                    // no checks to do for MOVE
                break;

            case SEEK:
                /*
                    // check if target has exceeded leash range
                    if(position.distance_from(Point(target_->x_position(), target_->y_position())) >= kZombieLeashRadius) {
                        move_action_->stop();
                        next_state_ = IDLE;
                        Logger::write("SEEK: Out of leash range");
                    }

                    // check if target has moved far from we think it is
                    // TODO(2014-08-15/JM): Hard coded number 12 here for distance, change
                    else if(target_last_position.distance_from(Point(target_->x_position(), target_->y_position())) >= 12) {
                        move_action_->stop();
                        next_state_ = SEEK;
                        Logger::write("SEEK: Recalculating movement to target");
                    }
                    */

                break;

            case ATTACK:
                //target_position = Point(target_->x_position(), target_->y_position());

                // Check if we are in range
                /*
                if(target_position.distance_from(position) > kPlayerAttackRange) {
                    //next_state_ = SEEK;
                    next_state_ = IDLE;
                    Logger::write("ATTACK: Target out of attack range");
                    break;
                }
                */

                // Check if we are facing the target
                /*
                if(!RotateAction::facing(entity, target_)) {
                    // TODO(2014-08-21/JM): This rotation code will not result in the rotating being animated  because there is no change
                    // of state to a state of rotating.
                    next_state_ = ROTATE;
                    Logger::write("ATTACK: Not facing target");
                }
                */

                break;

            case ROTATE:
                // No checks to do

                break;
        }
    }
    else {
        // Start movement if we're doing nothing
        if(state_ == IDLE) {
            if(next_state_ == MOVE) {
                state_ = MOVE;
                next_state_ = BLANK;
                move_action_ = static_cast<MoveAction *>(next_action_);
                next_action_ = nullptr;
            }
            else if(next_state_ == ATTACK) {
                state_ = ATTACK;
                next_state_ = BLANK;
                attack_action_ = static_cast<AttackAction *>(next_action_);
                next_action_ = nullptr;
            }
        }

    }

    // Perform action

    switch(state_) {
        case IDLE:
            // Nothing to do because we're IDLE
            if(next_state_ != BLANK) {
                keep_action = false;
            }
            break;

        case SEEK:

            // Perform movement
            keep_action = move_action_->update(entity, delta_ticks);
            //Logger::write(Logger::string_stream << "keep_action: " << keep_action);

            if(!keep_action) {
                Logger::write("SEEK complete");
                delete move_action_;
                move_action_ = nullptr;
                if(next_state_ == BLANK) {
                    next_state_ = ATTACK;
                }
            }
            break;

        case MOVE:

            keep_action = move_action_->update(entity, delta_ticks);

            if(!keep_action) {
                Logger::write("MOVE complete");
                delete move_action_;
                move_action_ = nullptr;
            }

            break;

        case ATTACK:

            // Perform attack

            keep_action = attack_action_->update(entity, delta_ticks);

            if(!keep_action) {
                Logger::write("ATTACK complete");
                delete attack_action_;
                if(next_state_ == BLANK) {
                    next_state_ = IDLE;
                }
            }
            break;

        case ROTATE:

            // Perform rotate
            keep_action = rotate_action_->update(entity, delta_ticks);

            if(!keep_action) {
                Logger::write("ROTATE complete");
                delete rotate_action_;
                rotate_action_ = nullptr;
                next_state_ = ATTACK;
            }
            break;
    }

    // Need to account for the target dying which is a ATTACK -> IDLE transition

    // Setup next action
    switch(next_state_) {
        case IDLE:
            // SEEK -> IDLE

            // ATTACK -> IDLE;
            target_ = nullptr;

            state_ = IDLE;
            next_state_ = BLANK;
            Logger::write("Switching to IDLE");
            break;
        case SEEK:
            // IDLE -> SEEK
            // SEEK -> SEEK
            // ATTACK -> SEEK
            if(!keep_action || (state_ == ATTACK)) {

               // Create movement action
               move_action_ = new MoveAction(position, Point(target_->x_position(), target_->y_position()), game_->level());
               move_action_->remove_movements_back();
               target_last_position = Point(target_->x_position(), target_->y_position());
               state_ = SEEK;
               next_state_ = BLANK;
                Logger::write("Switching to SEEK");
            }
            else {
                Logger::write("SOMETHING BAD");
            }

            break;
        case MOVE:
            if(!keep_action) {
                if((next_action_ != nullptr) && (next_action_->type() == ACTION_MOVEMENT)) {
                    state_ = MOVE;
                    next_state_ = BLANK;
                    move_action_ = static_cast<MoveAction *>(next_action_);
                    MoveAction * next_move_action = new MoveAction(position, move_action_->end(), move_action_->level());
                    delete move_action_;
                    move_action_ = next_move_action;
                    next_action_ = nullptr;
                }
                else {
                    state_ = IDLE;
                    next_state_ = BLANK;
                }
            }
            break;

        case ATTACK:
            // SEEK -> ATTACK
            attack_action_->reset();
            state_ = ATTACK;
            next_state_ = BLANK;
            Logger::write("Switching to ATTACK");
            break;
        case ROTATE:
            // ATTACK -> ROTATE
            rotate_action_ = new RotateAction(entity, target_->position());

            state_ = ROTATE;
            next_state_ = BLANK;
            Logger::write("Switching to ROTATE");
            break;
        case BLANK:
            if(!keep_action) {
                state_ = IDLE;
                next_state_ = BLANK;
            }
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
        default:
            //type_ = ACTION_IDLE;
            break;
    }

    return type_;
}

void PlayerAction::stop()
{
    switch(state_) {
        case IDLE:
            break;
        case SEEK:
            break;
        case MOVE:
            move_action_->stop();
            break;
        case ATTACK:
            attack_action_->stop();
            break;
        case ROTATE:
            break;
    }
}

std::string PlayerAction::to_string()
{
	//for (std::list<GridNode *>::iterator iterator = nodes->begin(), end = nodes->end(); iterator != end; ++iterator) {
	//    Logger::string_stream << "(" << (**iterator).row() << ", " << (**iterator).column() << ") ";
	//}
	return "";
}

