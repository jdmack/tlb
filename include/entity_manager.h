/* Entity Agent */

#ifndef TLB_ENTIGENT_H_
#define TLB_ENTIGENT_H_

#include <vector>

class GameObject;

class EntityManager
{
    private:
        std::vector<GameObject *> * objects_;
        std::vector<GameObject *> * selected_;

    public:
        EntityManager();

        // accessors
        std::vector<GameObject *> * objects() const { return objects_; }
        std::vector<GameObject *> * selected() const { return selected_; }

        void add_object(GameObject * object);
        void select(GameObject * object);
        void deselect(GameObject * object);
        void deselect_all();
        GameObject * get_object_at(double x, double y);

};

#endif
