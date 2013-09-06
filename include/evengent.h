/* Event Agent */

#ifndef TLB_EVENGENT_H_
#define TLB_EVENGENT_H_

#include "coordinate.h"
#include "timer.h"

class Game;

const double kFocusTimeout = 10000;

class Evengent
{
    private:
        Game * game_;
        Timer focus_timer_;

    public:
        Evengent();
        void handle_events();

        // mutators
        void set_game(Game * game) { game_ = game; }

        static Coordinate mouse_position();
};

#endif
