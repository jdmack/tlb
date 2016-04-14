#include <vector>

#include "WinCondition.h"
#include "EntityManager.h"
#include "Entity.h"
#include "Game.h"

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
