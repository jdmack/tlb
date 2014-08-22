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
    Point position = Point(entity->x_position(), entity->y_position());
    Point target_position;
    std::vector<Entity *> entities;
    switch(state_) {
        case IDLE:
            //Logger::write(Logger::string_stream << "ZombieAction: IDLE");

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
                entities.pop_back();
            }
            state_ = SEEK;

           // Delete current action if one exists
           if(movement_action_ != nullptr) {
               delete movement_action_;
               movement_action_ = nullptr;
           }

           // Create movement action
           movement_action_ = new MovementAction(position, Point(target_->x_position(), target_->y_position()), game_->level());
           movement_action_->remove_movements_back();
           if(movement_action_->empty_path()) {
               state_ = IDLE;
               break;
           }
           target_last_position = Point(target_->x_position(), target_->y_position());

            break;

        case SEEK:
            if(movement_action_ != nullptr) {
                // check if target has exceeded leash range
                if(position.distance_from(Point(target_->x_position(), target_->y_position())) >= kZombieLeashRadius) {
                    target_ = nullptr;
                    delete movement_action_;
                    movement_action_ = nullptr;
                    state_ = IDLE;
                    break;
                }

                // check if target has moved far from we think it is
                // TODO(2014-08-15/JM): Hard coded number 12 here for distance, change
                if(target_last_position.distance_from(Point(target_->x_position(), target_->y_position())) >= 12) {
                    delete movement_action_;
                   // Create movement action
                   movement_action_ = new MovementAction(position, Point(target_->x_position(), target_->y_position()), game_->level());
                   movement_action_->remove_movements_back();
                   if(movement_action_->empty_path()) {
                       state_ = IDLE;
                       break;
                   }
                   target_last_position = Point(target_->x_position(), target_->y_position());

                }

                // Perform movement
                bool keep_action = movement_action_->update(entity, delta_ticks);

                if(!keep_action) {
                    delete movement_action_;
                    movement_action_ = nullptr;
                    state_ = ATTACK;
                }
            }

            break;

        case ATTACK:
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
            type_ = ACTION_IDLE;
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

