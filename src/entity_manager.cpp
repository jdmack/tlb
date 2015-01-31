
#include "entity_manager.h"
#include "renderer.h"
#include "game.h"
#include "game_object.h"
#include "util/logger.h"
#include "point.h"
#include "entity.h"

////////////////////////////////////////////////////////////////////////////////
//
//
//
////////////////////////////////////////////////////////////////////////////////
EntityManager::EntityManager()
{
    objects_ = new std::list<GameObject *>();
    selected_ = new std::list<GameObject *>();
}

////////////////////////////////////////////////////////////////////////////////
//
//
//
////////////////////////////////////////////////////////////////////////////////
void EntityManager::add_object(GameObject * object)
{
    objects_->push_back(object);
}

////////////////////////////////////////////////////////////////////////////////
//
//
//
////////////////////////////////////////////////////////////////////////////////
void EntityManager::remove_object(GameObject * object)
{
    std::list<GameObject *>::iterator object_iterator = objects_->begin();
    while(object_iterator != objects_->end()) {
        if(object == *object_iterator) {
            object_iterator = objects_->erase(object_iterator);
        }
        else {
            object_iterator++;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////
//
//
//
////////////////////////////////////////////////////////////////////////////////
void EntityManager::delete_object(GameObject * object)
{
    std::list<GameObject *>::iterator object_iterator = objects_->begin();
    while(object_iterator != objects_->end()) {

        if(object == *object_iterator) {
            object_iterator = objects_->erase(object_iterator);
            delete object;
        }
        else {
            object_iterator++;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////
//
//
//
////////////////////////////////////////////////////////////////////////////////
void EntityManager::delete_all()
{
    deselect_all();

    std::list<GameObject *>::iterator object_iterator = objects_->begin();
    while(object_iterator != objects_->end()) {

        GameObject * object = *object_iterator;
        object_iterator = objects_->erase(object_iterator);
        object->deselect();
        delete object;
    }
}

////////////////////////////////////////////////////////////////////////////////
//
//
//
////////////////////////////////////////////////////////////////////////////////
GameObject * EntityManager::get_object_at(double x, double y)
{
    Logger::write(Logger::ss << "get_object_at(" << x << ", " << y << ")");
    for(std::list<GameObject *>::iterator object_iterator = objects_->begin(); object_iterator != objects_->end(); ++object_iterator) {
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
std::vector<Entity *> EntityManager::get_entities()
{
    std::vector<Entity *> entities;

    for(std::list<GameObject *>::iterator object_iterator = objects_->begin(); object_iterator != objects_->end(); ++object_iterator) {
        GameObject * object = *object_iterator;
        if(object->is_entity()) {
            Entity * entity = static_cast<Entity *>(object);
            entities.push_back(entity);
        }
    }

    return entities;
}

////////////////////////////////////////////////////////////////////////////////
//
//
//
////////////////////////////////////////////////////////////////////////////////
std::vector<Entity *> EntityManager::get_entities_near(Point position, double radius)
{
    std::vector<Entity *> entities;

    for(std::list<GameObject *>::iterator object_iterator = objects_->begin(); object_iterator != objects_->end(); ++object_iterator) {
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
    std::list<GameObject *>::iterator selected_iterator = selected_->begin();

    while(selected_iterator != selected_->end()) {

        if((*selected_iterator)->object_id() == object->object_id()) {
            (*selected_iterator)->deselect();
            selected_iterator = selected_->erase(selected_iterator);
            break;
        }
        else {
            selected_iterator++;
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
    std::list<GameObject *>::iterator selected_iterator = selected_->begin();

    while(selected_iterator != selected_->end()) {

        (*selected_iterator)->deselect();

        selected_iterator = selected_->erase(selected_iterator);
    }
}
