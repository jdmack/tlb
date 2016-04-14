#ifndef TLB_GS_MAIN_MENU_H_
#define TLB_GS_MAIN_MENU_H_

#include "Point.h"
#include "GameState.h"

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
