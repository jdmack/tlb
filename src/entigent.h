/* Entity Agent */

#ifndef TLB_ENTIGENT_H_
#define TLB_ENTIGENT_H_

#include <vector>

class TlbGame;
class GameObject;

class Entigent
{
    private:
        TlbGame * game_;
        std::vector<GameObject *> * objects_;
        std::vector<GameObject *> * selected_;


    public:
        void add_object(GameObject * object);
        void register_game(TlbGame * game);
        Entigent();
        GameObject * get_object_at(float x, float y);
        void select(GameObject * object);
        void deselect(GameObject * object);
        void deselect_all();
        std::vector<GameObject *> * objects();
        std::vector<GameObject *> * selected();
};
#endif
