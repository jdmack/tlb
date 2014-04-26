
#include <gtest/gtest.h>
#include "level.h"
#include "game.h"

TEST(Level,Basic)
{
    Game * game = new Game();
    Level * level = new Level(game);
}

