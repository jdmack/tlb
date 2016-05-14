/* Event Agent */

#ifndef TLB_EVENGENT_H_
#define TLB_EVENGENT_H_

#include "math/Vector2i.h"
#include "util/Timer.h"

const double kFocusTimeout = 10000;

class EventManager
{
    private:
        Vector2i mouse_;

    public:
        EventManager();
        void handleEvents();

        static Vector2i mousePosition();
};

#endif
