#include <cmath>
#include <vector>
#include <iostream>
#include <sstream>
#include <string>

#include "action/action.h"
#include "action/zombie_action.h"
#include "action/move_action.h"
#include "action/rotate_action.h"
#include "action/attack_action.h"

#include "game_object.h"
#include "point.h"
#include "util/logger.h"
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
    move_action_ = nullptr;
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
                break;

            case SEEK:
                break;

            case ATTACK:
                break;

            case ROTATE:
                // No checks to do

                break;
        }
    }

    // Perform action

    switch(state_) {
        case IDLE:
            break;

        case SEEK:
            break;

        case ATTACK:
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
            break;

        case SEEK:
            break;

        case ATTACK:
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
            type_ = ACTION_MOVE;
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
        default:
            type_ = ACTION_IDLE;
    }

    return type_;
}


std::string ZombieAction::to_string()
{
	//for (std::list<GridNode *>::iterator iterator = nodes->begin(), end = nodes->end(); iterator != end; ++iterator) {
	//    Logger::ss << "(" << (**iterator).row() << ", " << (**iterator).column() << ") ";
	//}
	return "";
}

