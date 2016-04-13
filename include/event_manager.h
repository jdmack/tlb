/* Event Agent */

#ifndef TLB_EVENGENT_H_
#define TLB_EVENGENT_H_

#include "point.h"
#include "util/timer.h"

const double kFocusTimeout = 10000;

class EventManager
{
    private:
        Timer focusTimer_;

    public:
        EventManager();
        void handleEvents();

        static Point mousePosition();
};

#endif
