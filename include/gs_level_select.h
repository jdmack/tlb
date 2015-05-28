#ifndef TLB_GS_LEVEL_SELECT_H_
#define TLB_GS_LEVEL_SELECT_H_

#include "game_state.h"


// FOR TESTING

class LevelGraph;
class UserInterface;
class EHLevel;

class GSLevelSelect : public GameState
{
    private:
        LevelGraph * level_graph_;
        UserInterface * user_interface_;
        EHLevel * event_handler_;


        // FOR TESTING

    public:
        GSLevelSelect();

        UserInterface * user_interface() const { return user_interface_; }

        bool init();
        bool update(int delta_ticks);
        void render();
        void end();

};

#endif
