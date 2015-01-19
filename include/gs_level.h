#ifndef TLB_GS_LEVEL_H_
#define TLB_GS_LEVEL_H_

#include "point.h"
#include "entity.h"
#include "game_state.h"
#include "frame.h"


// FOR TESTING

class Game;
class UserInterface;

class GSLevel : public GameState
{
    private:
        Game * game_;
        UserInterface * user_interface_;
        Frame * level_area_;

        // FOR TESTING

    public:
        GSLevel(Game * game);

        Frame * level_area() const { return level_area_; }

        int init();
        bool update(int delta_ticks);
        void render();
        void end();

        Entity * spawn_entity(EntityType type, Point position, double rotation);
};

#endif
