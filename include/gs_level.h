#ifndef TLB_GS_LEVEL_H_
#define TLB_GS_LEVEL_H_

#include "point.h"
#include "entity.h"
#include "game_state.h"


// FOR TESTING
#include "ui/panel.h"

class Game;

class GSLevel : public GameState
{
    private:
        Game * game_;

        // FOR TESTING
        Panel panel;

    public:
        GSLevel(Game * game);

        int init();
        bool update(int delta_ticks);
        void render();
        void end();

        Entity * spawn_entity(EntityType type, Point position, double rotation);
};

#endif
