#ifndef TLB_EVENT_EH_CAMERA_H_
#define TLB_EVENT_EH_CAMERA_H_

#include "event/Event.h"
#include "event/EventHandler.h"
#include "Point.h"

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
