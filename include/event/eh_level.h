#ifndef TLB_EVENT_EH_LEVEL_H_
#define TLB_EVENT_EH_LEVEL_H_

#include "event/event.h"
#include "event/eventHandler.h"
#include "point.h"
class EHLevel : public EventHandler
{
    private:
        KeyType toggleKey_;

    public:
        EHLevel();
        ~EHLevel();

        void handleEvent(Event * event);

        void mouseLeftClick(Point point);
        void mouseRightClick(Point point);
        void keyPress(KeyType key);
};

#endif
