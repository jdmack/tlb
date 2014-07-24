/* Entity Agent */

#include "entity_manager.h"
#include "renderer.h"
#include "game.h"
#include "game_object.h"
#include "utils/logger.h"
#include "point.h"
#include "entity.h"

////////////////////////////////////////////////////////////////////////////////
//
//
//
////////////////////////////////////////////////////////////////////////////////
EntityManager::EntityManager()
{
    objects_ = new std::vector<GameObject *>();
    selected_ = new std::vector<GameObject *>();
}

////////////////////////////////////////////////////////////////////////////////
//
//
//
////////////////////////////////////////////////////////////////////////////////
void EntityManager::add_object(GameObject * object)
{
    objects_->push_back(object);

    // TODO(2013-08-24/JM): Add function to remove object from the vector
    // or add an "active" field to distinguish elements that haven't been deleted yet
}

////////////////////////////////////////////////////////////////////////////////
//
//
//
////////////////////////////////////////////////////////////////////////////////
GameObject * EntityManager::get_object_at(double x, double y)
{
    for(std::vector<GameObject *>::iterator object_iterator = objects_->begin(); object_iterator != objects_->end(); ++object_iterator) {
        if((*object_iterator)->contains_point(x, y)) {
            return *object_iterator;
        }
    }

    return nullptr;
}

////////////////////////////////////////////////////////////////////////////////
//
//
//
////////////////////////////////////////////////////////////////////////////////
std::vector<Entity *> EntityManager::get_entities_near(Point position, double radius)
{
    std::vector<Entity *> entities;
    for(std::vector<GameObject *>::iterator object_iterator = objects_->begin(); object_iterator != objects_->end(); ++object_iterator) {
        GameObject * object = *object_iterator;
        if(object->is_entity()) {
            Entity * entity = static_cast<Entity *>(object);
            Point p = Point(entity->x_position(), entity->y_position());
            double distance = p.distance_from(position);
            if(distance <= radius) {
                entities.push_back(entity);
            }
        }
    }

    return entities;
}

////////////////////////////////////////////////////////////////////////////////
//
//
//
////////////////////////////////////////////////////////////////////////////////
void EntityManager::select(GameObject * object)
{
    object->select();
    selected_->push_back(object);
}

////////////////////////////////////////////////////////////////////////////////
//
//
//
////////////////////////////////////////////////////////////////////////////////
void EntityManager::deselect(GameObject * object)
{
    object->deselect();
    for(std::vector<GameObject *>::iterator selected_iterator = selected_->begin(); selected_iterator != selected_->end(); ++selected_iterator) {
        if((*selected_iterator)->object_id() == object->object_id()) {
            (*selected_iterator)->deselect();
            selected_->erase(selected_iterator);
            break;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////
//
//
//
////////////////////////////////////////////////////////////////////////////////
void EntityManager::deselect_all()
{
    if(!selected_->empty()) {
        for(std::vector<GameObject *>::iterator selected_iterator = selected_->begin(); selected_iterator < selected_->end(); ++selected_iterator) {
            (*selected_iterator)->deselect();
            selected_->erase(selected_iterator);
        }
    }
}
