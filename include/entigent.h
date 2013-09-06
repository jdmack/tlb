/* Entity Agent */

#ifndef TLB_ENTIGENT_H_
#define TLB_ENTIGENT_H_

#include <vector>

class Game;
class GameObject;

class Entigent
{
    private:
        Game * game_;
        std::vector<GameObject *> * objects_;
        std::vector<GameObject *> * selected_;


    public:
        void add_object(GameObject * object);
        Entigent();
        GameObject * get_object_at(double x, double y);
        void select(GameObject * object);
        void deselect(GameObject * object);
        void deselect_all();

        // accessors
        std::vector<GameObject *> * objects() const { return objects_; }
        std::vector<GameObject *> * selected() const { return selected_; }

        // mutators
        void set_game(Game * game) { game_ = game; }
};

#endif
