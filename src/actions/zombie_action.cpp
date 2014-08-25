#include <cmath>
#include <vector>
#include <iostream>
#include <sstream>
#include <string>

#include "actions/action.h"
#include "actions/zombie_action.h"
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

ZombieAction::ZombieAction()
{
    state_ = IDLE;
    next_state_ = BLANK;
    target_ = nullptr;
    entity_manager_ = nullptr;
    movement_action_ = nullptr;
    rotate_action_ = nullptr;
    attack_action_ = nullptr;
    game_ = nullptr;
    type_ = ACTION_IDLE;
}

bool ZombieAction::update(Entity * entity, int delta_ticks)
{
    bool keep_action = true;
    Point position = Point(entity->x_position(), entity->y_position());
    Point target_position;
    std::vector<Entity *> entities;


    // Check conditions
    if(next_state_ == BLANK) {
        switch(state_) {
            case IDLE:
                // Check for entities within Aggro Range
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

                break;

            case SEEK:
                    // check if target has exceeded leash range
                    if(position.distance_from(Point(target_->x_position(), target_->y_position())) >= kZombieLeashRadius) {
                        movement_action_->stop();
                        next_state_ = IDLE;
                        Logger::write("SEEK: Out of leash range");
                    }

                    // check if target has moved far from we think it is
                    // TODO(2014-08-15/JM): Hard coded number 12 here for distance, change
                    else if(target_last_position.distance_from(Point(target_->x_position(), target_->y_position())) >= 12) {
                        movement_action_->stop();
                        next_state_ = SEEK;
                        Logger::write("SEEK: Recalculating movement to target");
                    }

                break;

            case ATTACK:

                target_position = Point(target_->x_position(), target_->y_position());

                // Check if we are in range
                if(target_position.distance_from(position) > kZombieAttackRadius) {
                    next_state_ = SEEK;
                    Logger::write("ATTACK: Target out of attack range");
                    break;
                }

                // Check if we are facing the target
                if(!RotateAction::facing(entity, target_)) {
                    // TODO(2014-08-21/JM): This rotation code will not result in the rotating being animated  because there is no change
                    // of state to a state of rotating.
                    next_state_ = ROTATE;
                    Logger::write("ATTACK: Not facing target");
                }


                break;

            case ROTATE:
                // No checks to do

                break;
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
            if(movement_action_ == nullptr) Logger::write("SOMETHING BAD 2");
            keep_action = movement_action_->update(entity, delta_ticks);
            //Logger::write(Logger::string_stream << "keep_action: " << keep_action);

            if(!keep_action) {
                Logger::write("SEEK complete");
                delete movement_action_;
                movement_action_ = nullptr;
                if(next_state_ == BLANK) {
                    next_state_ = ATTACK;
                }
            }
            break;

        case ATTACK:

            // Perform attack
            if(next_state_ != BLANK) break;

            keep_action = attack_action_->update(entity, delta_ticks);

            if(!keep_action) {
                Logger::write("ATTACK complete");
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
            delete attack_action_;
            attack_action_ = nullptr;
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
               movement_action_ = new MovementAction(position, Point(target_->x_position(), target_->y_position()), game_->level());
               movement_action_->remove_movements_back();
               target_last_position = Point(target_->x_position(), target_->y_position());
               state_ = SEEK;
               next_state_ = BLANK;
                Logger::write("Switching to SEEK");
            }
            else {
                Logger::write("SOMETHING BAD");
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
            break;
    }
    return true;
}

ActionType ZombieAction::type()
{
    switch(state_) {
        case IDLE:
            type_ = ACTION_IDLE;
            break;
        case SEEK:
            type_ = ACTION_MOVEMENT;
            break;
        case ATTACK_READY:
            type_ = ACTION_IDLE;
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


std::string ZombieAction::to_string()
{
	//for (std::list<GridNode *>::iterator iterator = nodes->begin(), end = nodes->end(); iterator != end; ++iterator) {
	//    Logger::string_stream << "(" << (**iterator).row() << ", " << (**iterator).column() << ") ";
	//}
	return "";
}

