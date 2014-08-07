
#ifndef TLB_ENTITY_MANAGER_H_
#define TLB_ENTITY_MANAGER_H_

#include <vector>
#include <list>
#include "point.h"

class GameObject;
class Entity;

class EntityManager
{
    private:
        std::list<GameObject *> * objects_;
        std::list<GameObject *> * selected_;

    public:
        EntityManager();

        // accessors
        std::list<GameObject *> * objects() { return objects_; }
        std::list<GameObject *> * selected() { return selected_; }

        void add_object(GameObject * object);
        void remove_object(GameObject * object);
        void delete_object(GameObject * object);
        void delete_all();
        void select(GameObject * object);
        void deselect(GameObject * object);
        void deselect_all();
        GameObject * get_object_at(double x, double y);
        std::vector<Entity *> get_entities_near(Point position, double radius);
        std::vector<Entity *> get_entities();
};

#endif
