#ifndef TLB_EVENT_EH_LEVEL_H_
#define TLB_EVENT_EH_LEVEL_H_

#include "event/Event.h"
#include "event/EventHandler.h"
#include "math/Vector2i.h"

// FOR TESTING
#include "gfx/Ray.h"

class EHLevel : public EventHandler
{
    private:
        KeyType toggleKey_;
        int cameraHandlerId_;
        bool cameraOn_;

        // FOR TESTING
        Ray ray_;

        void mouseLeftClick(Vector2i position);
        void mouseRightClick(Vector2i position);
        void mouseMotion(Vector2i position);
        void keyPress(KeyType key);

    public:
        EHLevel();
        ~EHLevel();

        bool handleEvent(Event * event);
        void update();
};

#endif
