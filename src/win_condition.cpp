#include <vector>

#include "win_condition.h"
#include "entity_manager.h"
#include "entity.h"
#include "game.h"

WinCondition::WinCondition()
{
    // nothing to do
}

bool WinCondition::check()
{
    return check_enemies();
}

bool WinCondition::check_enemies()
{
    std::vector<Entity *> entities = Game::instance()->entity_manager()->get_entities();
    for(std::vector<Entity *>::iterator it = entities.begin(); it != entities.end(); ++it) {
        if((*it)->type() == ZOMBIE) {
            if(!(*it)->dead()) {
                return false;
            }
        }
    }

    return true;
}
