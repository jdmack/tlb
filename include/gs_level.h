#ifndef TLB_GS_LEVEL_H_
#define TLB_GS_LEVEL_H_

#include "point.h"
#include "entity.h"
#include "game_state.h"
#include "frame.h"


// FOR TESTING

class UserInterface;
class EHLevel;

class GSLevel : public GameState
{
    private:
        UserInterface * user_interface_;
        Frame * level_area_;
        EHLevel * event_handler_;


        // FOR TESTING

    public:
        GSLevel();

        Frame * level_area() const { return level_area_; }

        int init();
        bool update(int delta_ticks);
        void render();
        void end();

        Entity * spawn_entity(EntityType type, Point position, double rotation);
};

#endif
