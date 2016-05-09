/* Event Agent */

#ifndef TLB_EVENGENT_H_
#define TLB_EVENGENT_H_

#include "Point.h"
#include "math/Vector2i.h"
#include "util/Timer.h"

const double kFocusTimeout = 10000;

class EventManager
{
    private:
        Timer focusTimer_;
        Vector2i mouse_;

    public:
        EventManager();
        void handleEvents();

        static Point mousePosition();
};

#endif
