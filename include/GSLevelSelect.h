#ifndef TLB_GS_LEVEL_SELECT_H_
#define TLB_GS_LEVEL_SELECT_H_

#include "GameState.h"


// FOR TESTING

class LevelGraph;
class UserInterface;
class EHLevel;
class Graphic;

class GSLevelSelect : public GameState
{
    private:
        LevelGraph * levelGraph_;
        UserInterface * userInterface_;
        EHLevel * eventHandler_;

        Graphic * background_;


        // FOR TESTING

    public:
        GSLevelSelect();

        UserInterface * userInterface() const { return userInterface_; }

        bool init();
        bool update(int deltaTicks);
        void render();
        void end();

};

#endif
