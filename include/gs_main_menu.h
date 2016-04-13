#ifndef TLB_GS_MAIN_MENU_H_
#define TLB_GS_MAIN_MENU_H_

#include "point.h"
#include "gameState.h"

class GSMainMenu : public GameState
{
    private:

    public:
        GSMainMenu();

        bool init();
        bool update(int deltaTicks);
        void render();
        void end();


};

#endif
