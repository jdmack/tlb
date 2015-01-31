
#include <list>
#include "event/eh_level.h"
#include "event/event.h"
#include "event/e_key_press.h"
#include "event/e_mouse_click.h"
#include "game.h"
#include "game_object.h"
#include "entity.h"
#include "util/global_timer.h"
#include "game_state.h"
#include "gs_level.h"
#include "util/logger.h"
#include "entity_manager.H"


EHLevel::EHLevel()
{
    toggle_key_ = KEY_NONE;
}

EHLevel::~EHLevel()
{

}

void EHLevel::handle_event(Event * event)
{
    if(event->type() == EVENT_MOUSE_CLICK) {
        EMouseClick * mouse_event = static_cast<EMouseClick *>(event);
        if(mouse_event->button() == MOUSE_LEFT) {
            mouse_left_click(mouse_event->point());
        }
        else if(mouse_event->button() == MOUSE_RIGHT) {
            mouse_right_click(mouse_event->point());
        }
    }
    else if(event->type() == EVENT_GAME_QUIT) {

    }

    else if(event->type() == EVENT_KEY_PRESS) {
        EKeyPress * key_event = static_cast<EKeyPress *>(event);
        key_press(key_event->key_type());
        return;
    }
}

void EHLevel::mouse_left_click(Point point)
{
    Logger::write("Mouse Left Click");
    // Check if an entity is selected and R is being held down
    //if(!Game::instance()->entity_manager()->selected()->empty()) {
        if(toggle_key_ == KEY_R) {
            Entity * entity = Game::instance()->entity_manager()->selected();
            entity->rotate(point);
        }
        // Check if an entity is selected and A is being held down
        else if(toggle_key_ == KEY_A) {
            Entity * entity = Game::instance()->entity_manager()->selected();

            GameObject * target_object = Game::instance()->entity_manager()->get_object_at(point.x(), point.y());

            if((target_object != nullptr) && (target_object->is_entity())) {
                Entity * target_entity = static_cast<Entity *>(target_object);
                entity->attack(target_entity);
            }

        }
    //}
    else {
        // 2 cases
        GameObject * clicked_on = Game::instance()->entity_manager()->get_object_at(point.x(), point.y());
        // 1. clicking on nothing
        if(clicked_on == nullptr) {
            // NOTE: left clicking on anything deselects_all with current functionality
            Logger::write("Deselecting");
            Game::instance()->entity_manager()->deselect_all();
        }
        // 2. clicking on something
        else {
            if(!clicked_on->selected() || Game::instance()->entity_manager()->objects()->size() != 1) {
                Game::instance()->entity_manager()->deselect_all();
                Game::instance()->entity_manager()->select(clicked_on);
            }
        }
    }

        toggle_key_ = KEY_NONE;
}

void EHLevel::mouse_right_click(Point point)
{
    Entity * entity = Game::instance()->entity_manager()->selected();
    if(entity != nullptr) {
        // something is selected, can now give it an order

        Point mouse_point = point;

        if(Game::instance()->state()->type() == GS_LEVEL) {
            GSLevel * state = static_cast<GSLevel *>(Game::instance()->state());
            mouse_point = Point(point.x() - state->level_area()->x(), point.y() - state->level_area()->y());
        }

        entity->move(mouse_point);
    }
}

void EHLevel::key_press(KeyType key)
{
    toggle_key_ = key;
    Entity * entity;

    switch(key) {

        case KEY_ESCAPE:
            Game::instance()->set_quit(true);
            break;

        case KEY_SPACE:
            GlobalTimer::instance()->toggle_pause();
            break;

        case KEY_S:
            entity = Game::instance()->entity_manager()->selected();
            if(entity != nullptr) {
            // something is selected, can now give it an order
                entity->stop();
            }
            break;
        case KEY_UP:
        case KEY_DOWN:
        case KEY_LEFT:
        case KEY_RIGHT:
        case KEY_A:
        case KEY_B:
        case KEY_C:
        case KEY_D:
        case KEY_E:
        case KEY_F:
        case KEY_G:
        case KEY_H:
        case KEY_I:
        case KEY_J:
        case KEY_K:
        case KEY_L:
        case KEY_M:
        case KEY_N:
        case KEY_O:
        case KEY_P:
        case KEY_Q:
        case KEY_R:
        case KEY_T:
        case KEY_U:
        case KEY_V:
        case KEY_W:
        case KEY_X:
        case KEY_Y:
        case KEY_Z:
        case KEY_NONE:
            break;
    }
}

