#include <vector>

#include "winCondition.h"
#include "entityManager.h"
#include "entity.h"
#include "game.h"

WinCondition::WinCondition()
{
    // nothing to do
}

bool WinCondition::check()
{
    return checkEnemies();
}

bool WinCondition::checkEnemies()
{
    std::vector<Entity *> entities = Game::instance()->entityManager()->getEntities();
    for(std::vector<Entity *>::iterator it = entities.begin(); it != entities.end(); ++it) {
        if((*it)->type() == ZOMBIE) {
            if(!(*it)->dead()) {
                return false;
            }
        }
    }

    return true;
}
