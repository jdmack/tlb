#ifndef TLB_TLB_GAME_H_
#define TLB_TLB_GAME_H_

#include "SDL/SDL.h"
#include "timer.h"

class Entigent;
class Evengent;
class Screen;

class TlbGame
{
    private:
        bool exit_code_;
        bool quit_;
        Timer delta_timer_;
        Screen * screen_;
        Entigent * entigent_;
        Evengent * evengent_;

    public:
        TlbGame();
        ~TlbGame();
        int run();
        void game_loop();
        void process_arguments(int argc, char * argv[]);

        // accessors
        Screen * screen() const { return screen_; }
        Entigent * entigent() const { return entigent_; }
        Evengent * evengent() const { return evengent_; }

        // mutators
        void set_quit(bool quit) { quit_ = quit; }
};

#endif
