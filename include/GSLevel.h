#ifndef TLB_GS_LEVEL_H_
#define TLB_GS_LEVEL_H_

#include "Point.h"
#include "Entity.h"
#include "GameState.h"
#include "Frame.h"
#include "WinCondition.h"


// FOR TESTING
#include "gfx/Tile.h"
#include "gfx/Ray.h"

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
        Tile * tile_;
        Tile * tile2_;
        Ray * ray_;

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
