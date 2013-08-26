#ifndef TLB_TLB_GAME_H_
#define TLB_TLB_GAME_H_

#include "SDL/SDL.h"
#include "timer.h"

class Entigent;
class Screen;
class Logger;

class TlbGame
{
    private:
        bool exit_code_;
        bool quit_;
        Timer delta_timer_;
        Screen * screen_;
        Logger * logger_;
        Entigent * entigent_;

    public:
        TlbGame();
        ~TlbGame();
        int run();
        void game_loop();
        void process_arguments(int argc, char * argv[]);
        void set_quit(bool quit);
        Screen * screen();
        Entigent * entigent();
};

#endif
