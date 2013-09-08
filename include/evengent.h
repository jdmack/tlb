/* Event Agent */

#ifndef TLB_EVENGENT_H_
#define TLB_EVENGENT_H_

#include "coordinate.h"
#include "utils/timer.h"

class Game;

const double kFocusTimeout = 10000;

class Evengent
{
    private:
        Game * game_;
        Timer focus_timer_;

    public:
        Evengent(Game * game);
        void handle_events();

        static Coordinate mouse_position();
};

#endif
