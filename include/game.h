#ifndef TLB_TLB_GAME_H_
#define TLB_TLB_GAME_H_

#include "SDL/SDL.h"
#include "timer.h"

class Entigent;
class Evengent;
class Screen;
class Camera;
class Level;

class Game
{
    private:
        int exit_code_;
        bool quit_;
        Timer delta_timer_;
        Screen * screen_;
        Entigent * entigent_;
        Evengent * evengent_;
        Camera * camera_;
        Level * level_;

    public:
        Game();
        ~Game();
        int run();
        void game_loop();
        void process_arguments(int argc, char * argv[]);

        // accessors
        Screen * screen() const { return screen_; }
        Entigent * entigent() const { return entigent_; }
        Evengent * evengent() const { return evengent_; }
        Camera * camera() const { return camera_; }
        Level * level() const { return level_; }

        // mutators
        void set_quit(bool quit) { quit_ = quit; }
        void level(Level * level) { level_ = level; }
};

#endif
