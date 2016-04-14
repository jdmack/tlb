
#include "EntityManager.h"
#include "gfx/Renderer.h"
#include "Game.h"
#include "GameObject.h"
#include "util/Logger.h"
#include "Point.h"
#include "Entity.h"

////////////////////////////////////////////////////////////////////////////////
//
//
//
////////////////////////////////////////////////////////////////////////////////
EntityManager::EntityManager()
{
    objects_ = new std::list<GameObject *>();
    //selected_ = new std::list<GameObject *>();
    selected_ = nullptr;
}

////////////////////////////////////////////////////////////////////////////////
//
//
//
////////////////////////////////////////////////////////////////////////////////
void EntityManager::addObject(GameObject * object)
{
    objects_->push_back(object);
}

////////////////////////////////////////////////////////////////////////////////
//
//
//
////////////////////////////////////////////////////////////////////////////////
void EntityManager::removeObject(GameObject * object)
{
    std::list<GameObject *>::iterator objectIterator = objects_->begin();
    while(objectIterator != objects_->end()) {
        if(object == *objectIterator) {
            objectIterator = objects_->erase(objectIterator);
        }
        else {
            objectIterator++;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////
//
//
//
////////////////////////////////////////////////////////////////////////////////
void EntityManager::deleteObject(GameObject * object)
{
    std::list<GameObject *>::iterator objectIterator = objects_->begin();
    while(objectIterator != objects_->end()) {

        if(object == *objectIterator) {
            objectIterator = objects_->erase(objectIterator);
            delete object;
        }
        else {
            objectIterator++;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////
//
//
//
////////////////////////////////////////////////////////////////////////////////
void EntityManager::deleteAll()
{
    deselectAll();

    std::list<GameObject *>::iterator objectIterator = objects_->begin();
    while(objectIterator != objects_->end()) {

        GameObject * object = *objectIterator;
        objectIterator = objects_->erase(objectIterator);
        object->deselect();
        delete object;
    }
}

////////////////////////////////////////////////////////////////////////////////
//
//
//
////////////////////////////////////////////////////////////////////////////////
GameObject * EntityManager::getObjectAt(double x, double y)
{
    Logger::write(Logger::ss << "getObjectAt(" << x << ", " << y << ")");
    for(std::list<GameObject *>::iterator objectIterator = objects_->begin(); objectIterator != objects_->end(); ++objectIterator) {
        if((*objectIterator)->containsPoint(x, y)) {
            return *objectIterator;
        }
    }

    return nullptr;
}

////////////////////////////////////////////////////////////////////////////////
//
//
//
////////////////////////////////////////////////////////////////////////////////
std::vector<Entity *> EntityManager::getEntities()
{
    std::vector<Entity *> entities;

    for(std::list<GameObject *>::iterator objectIterator = objects_->begin(); objectIterator != objects_->end(); ++objectIterator) {
        GameObject * object = *objectIterator;
        if(object->isEntity()) {
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
std::vector<Entity *> EntityManager::getEntitiesNear(Point position, double radius)
{
    std::vector<Entity *> entities;

    for(std::list<GameObject *>::iterator objectIterator = objects_->begin(); objectIterator != objects_->end(); ++objectIterator) {
        GameObject * object = *objectIterator;
        if(object->isEntity()) {
            Entity * entity = static_cast<Entity *>(object);
            Point p = Point(entity->xPosition(), entity->yPosition());
            double distance = p.distanceFrom(position);
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
    selected_ = static_cast<Entity *>(object);
    //selected_->push_back(object);
}

////////////////////////////////////////////////////////////////////////////////
//
//
//
////////////////////////////////////////////////////////////////////////////////
void EntityManager::deselect(GameObject * object)
{
    object->deselect();
    /*
    std::list<GameObject *>::iterator selectedIterator = selected_->begin();

    while(selectedIterator != selected_->end()) {

        if((*selectedIterator)->objectId() == object->objectId()) {
            (*selectedIterator)->deselect();
            selectedIterator = selected_->erase(selectedIterator);
            break;
        }
        else {
            selectedIterator++;
        }
    }
    */
    selected_ = nullptr;
}

////////////////////////////////////////////////////////////////////////////////
//
//
//
////////////////////////////////////////////////////////////////////////////////
void EntityManager::deselectAll()
{
    if(selected_ != nullptr) {
        selected_->deselect();
        selected_ = nullptr;
    }
    /*
    std::list<GameObject *>::iterator selectedIterator = selected_->begin();

    while(selectedIterator != selected_->end()) {

        (*selectedIterator)->deselect();

        selectedIterator = selected_->erase(selectedIterator);
    }
    */
}
