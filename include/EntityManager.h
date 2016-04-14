
#ifndef TLB_ENTITY_MANAGER_H_
#define TLB_ENTITY_MANAGER_H_

#include <vector>
#include <list>
#include "Point.h"

class GameObject;
class Entity;

class EntityManager
{
    private:
        std::list<GameObject *> * objects_;
        //std::list<GameObject *> * selected_;
        Entity * selected_;

    public:
        EntityManager();

        // accessors
        std::list<GameObject *> * objects() { return objects_; }
        //std::list<GameObject *> * selected() { return selected_; }
        Entity * selected() { return selected_; }

        void addObject(GameObject * object);
        void removeObject(GameObject * object);
        void deleteObject(GameObject * object);
        void deleteAll();
        void select(GameObject * object);
        void deselect(GameObject * object);
        void deselectAll();
        GameObject * getObjectAt(double x, double y);
        std::vector<Entity *> getEntitiesNear(Point position, double radius);
        std::vector<Entity *> getEntities();
};

#endif
