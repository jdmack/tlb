#ifndef TLB_GS_LEVEL_H_
#define TLB_GS_LEVEL_H_

#include "point.h"
#include "entity.h"
#include "game_state.h"

class Game;

class GSLevel : public GameState
{
    private:
        Game * game_;

    public:
        GSLevel(Game * game);

        int init();
        bool update(int delta_ticks);
        void render();
        void end();

        Entity * spawn_entity(EntityType type, Point position, double rotation);
};

#endif
