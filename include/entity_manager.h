/* Entity Agent */

#ifndef TLB_ENTIGENT_H_
#define TLB_ENTIGENT_H_

#include <vector>
#include "point.h"

class GameObject;
class Entity;

class EntityManager
{
    private:
        std::vector<GameObject *> * objects_;
        std::vector<GameObject *> * selected_;



    public:
        EntityManager();

        // accessors
        std::vector<GameObject *> * objects() { return objects_; }
        std::vector<GameObject *> * selected() { return selected_; }

        void add_object(GameObject * object);
        void select(GameObject * object);
        void deselect(GameObject * object);
        void deselect_all();
        GameObject * get_object_at(double x, double y);
        std::vector<Entity *> get_entities_near(Point position, double radius);
};

#endif
