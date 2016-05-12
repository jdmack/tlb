#ifndef TLB_EVENT_EH_CAMERA_H_
#define TLB_EVENT_EH_CAMERA_H_

#include "event/Event.h"
#include "event/EventHandler.h"
#include "math/Vector2i.h"

class EHCamera : public EventHandler
{
    private:
        KeyType toggleKey_;

        bool mouseLeftClick(Vector2i position);
        bool mouseRightClick(Vector2i position);
        bool keyPress(KeyType key);

    public:
        EHCamera();
        ~EHCamera();

        bool handleEvent(Event * event);

};

#endif
