#ifndef TLB_GS_MAIN_MENU_H_
#define TLB_GS_MAIN_MENU_H_

#include "point.h"
#include "game_state.h"

class GSMainMenu : public GameState
{
    private:

    public:
        GSMainMenu();

        int init();
        bool update(int delta_ticks);
        void render();
        void end();


};

#endif
