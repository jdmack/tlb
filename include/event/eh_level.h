#ifndef TLB_EVENT_EH_LEVEL_H_
#define TLB_EVENT_EH_LEVEL_H_

#include "event/event.h"
#include "event/event_handler.h"
#include "point.h"
class EHLevel : public EventHandler
{
    private:
        KeyType toggle_key_;

    public:
        EHLevel();
        ~EHLevel();

        void handle_event(Event * event);

        void mouse_left_click(Point point);
        void mouse_right_click(Point point);
        void key_press(KeyType key);
};

#endif
