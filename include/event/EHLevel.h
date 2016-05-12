#ifndef TLB_EVENT_EH_LEVEL_H_
#define TLB_EVENT_EH_LEVEL_H_

#include "event/Event.h"
#include "event/EventHandler.h"
#include "math/Vector2i.h"

class EHLevel : public EventHandler
{
    private:
        KeyType toggleKey_;

        void mouseLeftClick(Vector2i position);
        void mouseRightClick(Vector2i position);
        void keyPress(KeyType key);

    public:
        EHLevel();
        ~EHLevel();

        bool handleEvent(Event * event);

};

#endif
