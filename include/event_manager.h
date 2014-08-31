/* Event Agent */

#ifndef TLB_EVENGENT_H_
#define TLB_EVENGENT_H_

#include "point.h"
#include "util/timer.h"

class Game;

const double kFocusTimeout = 10000;

class EventManager
{
    private:
        Game * game_;
        Timer focus_timer_;

    public:
        EventManager(Game * game);
        void handle_events();

        static Point mouse_position();
};

#endif
