#ifndef TLB_GS_MAIN_MENU_H_
#define TLB_GS_MAIN_MENU_H_

#include "point.h"
#include "game_state.h"

class Game;

class GSMainMenu : public GameState
{
    private:
        Game * game_;

    public:
        GSMainMenu(Game * game);

        int init();
        bool update(int delta_ticks);
        void render();
        void end();


};

#endif
