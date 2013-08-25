#ifndef TLB_TLB_GAME_H_
#define TLB_TLB_GAME_H_

#include "SDL/SDL.h"
#include "timer.h"
#include "logger.h"

class Screen;

class TlbGame
{
    private:
        bool exit_code_;
        bool quit_;
        Timer delta_timer_;
        SDL_Event event_;
        Screen * screen_;
        Logger logger;

    public:
        TlbGame();
        int run();
        void game_loop();
        void process_arguments(int argc, char * argv[]);

};

#endif
