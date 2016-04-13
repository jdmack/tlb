#include <vector>

#include "gsLevel.h"

#include "gfx/renderer.h"
#include "game.h"
#include "level.h"
#include "entityManager.h"
#include "entity.h"
#include "assets.h"
#include "util/logger.h"
#include "ui/userInterface.h"
#include "event/ehLevel.h"
#include "event/eventDispatcher.h"
#include "ui/characterPanel.h"
#include "gfx/model.h"


GSLevel::GSLevel()
{
    type_ = GS_LEVEL;
    userInterface_ = nullptr;
    levelArea_ = new Frame(200, 0, 976, 864);
    eventHandler_ = new EHLevel();
}

bool GSLevel::init()
{
    // Load level
    //Level * level = new Level();

    //if(!level->load(kMapTestHexIsometric)) {
    //if(!level->load(kMapTest24x18)) {
    //    Logger::write(Logger::ss << "Failed to load map");
    //    return false;
    //}

    //Game::instance()->setLevel(level);

    //userInterface_ = new UserInterface();

    EventDispatcher::instance()->registerHandler(eventHandler_);

    // (264,216)
    ///*Entity * char1   = */spawnEntity(PLAYER, Point(48 * 1 + 24, 48 * 1 + 24), 90);
    ///*Entity * zombie1 = */spawnEntity(ZOMBIE, Point(48 * 5 + 24, 48 * 5 + 24), 270);

    //Entity * zombie2 = spawnEntity(ZOMBIE, Point(48 * 5 + 24, 48 * 1 + 24), 90);
    //Entity * zombie3 = spawnEntity(ZOMBIE, Point(48 * 6 + 24, 48 * 1 + 24), 90);
    //Entity * zombie4 = spawnEntity(ZOMBIE, Point(48 * 7 + 24, 48 * 1 + 24), 90);
    //Entity * zombie5 = spawnEntity(ZOMBIE, Point(48 * 8 + 24, 48 * 1 + 24), 0);
    //Entity * zombie6 = spawnEntity(ZOMBIE, Point(48 * 7 + 24, 48 * 1 + 24), 0);

    // FOR TESTING
    model_ = new Model();

    return true;
}

bool GSLevel::update(int deltaTicks)
{
    //if(winCondition_.check()) {
        // TODO(2015-05-13/JM): Going to want to change this to transition to another state instead of quit
    //    Game::instance()->setQuit(true);
    //}

    std::vector<Entity *> entities = Game::instance()->entityManager()->getEntities();

    // Update
    for(std::vector<Entity *>::iterator entityIterator = entities.begin(); entityIterator != entities.end(); ++entityIterator) {
        (*entityIterator)->update(deltaTicks);
    }

    //userInterface_->update();

    return true;
}
void GSLevel::render()
{
    //Game::instance()->level()->render(levelArea_);

    // Render
    std::vector<Entity *> entities = Game::instance()->entityManager()->getEntities();
    for(std::vector<Entity *>::iterator entityIterator = entities.begin(); entityIterator != entities.end(); ++entityIterator) {
        (*entityIterator)->render(levelArea_);

        if(((*entityIterator)->type() == PLAYER) || ((*entityIterator)->type() == ZOMBIE)) {
            Game::instance()->renderer()->drawLifeBar(*entityIterator, levelArea_);
        }
    }

    //userInterface_->render();

    // FOR TESTING
    model_->render();
}

void GSLevel::end()
{
    Game::instance()->entityManager()->deleteAll();
    // TODO(2014-08-06/JM): Move Level into this class
    // TODO(2014-08-06/JM): Delete Level
}

Entity * GSLevel::spawnEntity(EntityType type, Point position, double rotation)
{
    Entity * entity = new Entity(type, position, rotation);
    if(type == PLAYER) {
        entity->setControllable(true);
        entity->createSprite(kAssetSpriteHuman1);
        //userInterface_->characterPanel(0)->setEntity(entity);
    }
    else if(type == HUMAN) {
        entity->setControllable(false);
        entity->createSprite(kAssetSpriteHuman1);
    }
    else if(type == ZOMBIE) {
        entity->setSelectable(false);
        entity->setControllable(false);
        entity->setMaximumSpeed(kEntityDefaultVelocity * 0.6);

        int randomNum = rand() % 5 + 1;

        std::string asset;
        asset = kAssetSpriteZombie1;

     /* switch(randomNum) {
            case 1: asset = kAssetSpriteZombie1; break;
            case 2: asset = kAssetSpriteZombie2; break;
            case 3: asset = kAssetSpriteZombie3; break;
            case 4: asset = kAssetSpriteZombie4; break;
            case 5: asset = kAssetSpriteZombie5; break;
            case 6: asset = kAssetSpriteZombie6; break;
            default: asset = kAssetSpriteZombie1; break;
       } */
        entity->createSprite(asset);
    }

    Game::instance()->entityManager()->addObject(entity);
    Game::instance()->renderer()->initObject(entity);


    return entity;
}


