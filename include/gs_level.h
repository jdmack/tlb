#ifndef TLB_GS_LEVEL_H_
#define TLB_GS_LEVEL_H_

#include "point.h"
#include "entity.h"
#include "gameState.h"
#include "frame.h"
#include "winCondition.h"


// FOR TESTING

class UserInterface;
class EHLevel;
class Model;

class GSLevel : public GameState
{
    private:
        UserInterface * userInterface_;
        Frame * levelArea_;
        EHLevel * eventHandler_;
        WinCondition winCondition_;

        // FOR TESTING
        Model * model_;

    public:
        GSLevel();

        UserInterface * userInterface() const { return userInterface_; }
        Frame * levelArea() const { return levelArea_; }

        bool init();
        bool update(int deltaTicks);
        void render();
        void end();

        Entity * spawnEntity(EntityType type, Point position, double rotation);
};

#endif
