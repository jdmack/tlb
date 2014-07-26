#include <cmath>
#include <vector>
#include <iostream>
#include <sstream>
#include <string>

#include "actions/action.h"
#include "actions/zombie_action.h"
#include "actions/movement_action.h"

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
    game_ = nullptr;
    type_ = ACTION_IDLE;
}

bool ZombieAction::update(Entity * entity, int delta_ticks)
{
    Point position = Point(entity->x_position(), entity->y_position());
    std::vector<Entity *> entities;
    switch(state_) {
        case IDLE:
            Logger::write(Logger::string_stream << "ZombieAction: IDLE");

            entities = entity_manager_->get_entities_near(position, kZombieAggroRadius);

            //TODO(2014-07-24/JM): Choose way of selecting target if there are multiple
            while(target_ == nullptr) {
                if(entities.empty()) {
                    Logger::write(Logger::string_stream << "Found nothing nearby");
                    return true;
                }
                if(entities.back()->object_id() == entity->object_id()) {
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
           if(movement_action_->empty_path()) {
               state_ = IDLE;
               break;
           }

           // Start the first movement
           entity->set_x_velocity(movement_action_->current()->maximum_velocity().x_component());
           entity->set_y_velocity(movement_action_->current()->maximum_velocity().y_component());

            break;

        case SEEK:
            if(movement_action_ != nullptr) {
                bool keep_action = movement_action_->update(entity, delta_ticks);

                if(!keep_action) {
                    delete movement_action_;
                    movement_action_ = nullptr;
                    state_ = IDLE;
                }
            }

            break;

        case ATTACK:
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

