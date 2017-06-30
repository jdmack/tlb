#include <vector>

#include "GSLevel.h"

#include "gfx/Renderer.h"
#include "gfx/Camera.h"
#include "Game.h"
#include "Level.h"
#include "EntityManager.h"
#include "Entity.h"
#include "Assets.h"
#include "util/Logger.h"
#include "ui/UserInterface.h"
#include "event/EHLevel.h"
#include "event/EventDispatcher.h"
#include "ui/CharacterPanel.h"
#include "gfx/lighting/LightManager.h"


// FOR TESTING
#include "gfx/Model.h"
#include "gfx/Tile.h"
#include "math/Vector3f.h"

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
    Level * level = new Level();

    //if(!level->load(kMapTestHexIsometric)) {
    if(!level->load(kMapTest3D)) {
        Logger::write(Logger::ss << "Failed to load map");
        return false;
    }

    Game::instance()->setLevel(level);
    LightManager * lightManager = Game::instance()->renderer()->lightManager();

    //lightManager->createDirectionalLight(Vector3f(1,1,1), 0.2, 0.4, Vector3f(1,-1,0));
    //lightManager->createPointLight(Vector3f(1,1,1), 0.2, 0.5, Vector3f(10,1,10), 1, 1, 0.1);
    lightManager->createPointLight(Vector3f(1,1,1), 0.2, 0.5, Vector3f(20,1,10), 1, 1, 0.1);
    lightManager->createSpotLight(Vector3f(1, 1, 1), 0.2, 0.8, Vector3f(10,1,0), 1, 1, 0.1, Vector3f(0, 0, 1), 10);
    lightManager->createSpotLight(Vector3f(1, 1, 1), 0.2, 0.8, Vector3f(20,1,0), 1, 1, 0.1, Vector3f(-1, 0, 0), 20);

    //userInterface_ = new UserInterface();

    EventDispatcher::instance()->registerHandler(eventHandler_);

    // (264,216)
    /*Entity * char1   = */spawnEntity(PLAYER, Point(1, 1), 90);
    ///*Entity * zombie1 = */spawnEntity(ZOMBIE, Point(48 * 5 + 24, 48 * 5 + 24), 270);
    
    //Entity * zombie2 = spawnEntity(ZOMBIE, Point(48 * 5 + 24, 48 * 1 + 24), 90);
    //Entity * zombie3 = spawnEntity(ZOMBIE, Point(48 * 6 + 24, 48 * 1 + 24), 90);
    //Entity * zombie4 = spawnEntity(ZOMBIE, Point(48 * 7 + 24, 48 * 1 + 24), 90);
    //Entity * zombie5 = spawnEntity(ZOMBIE, Point(48 * 8 + 24, 48 * 1 + 24), 0);
    //Entity * zombie6 = spawnEntity(ZOMBIE, Point(48 * 7 + 24, 48 * 1 + 24), 0);

    // FOR TESTING
    tile_ = new Tile();
    tile2_ = new Tile();
    tile2_->setPosition(Vector3f(1, 0.0, 0.0));
    tile2_->setWidth(0.5);
    tile2_->setLength(0.5);
    tile2_->setHeight(0.1);
    tile2_->setType(2);

    

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
    Game::instance()->level()->render(levelArea_);

    // Render
    std::vector<Entity *> entities = Game::instance()->entityManager()->getEntities();
    for(std::vector<Entity *>::iterator entityIterator = entities.begin(); entityIterator != entities.end(); ++entityIterator) {
        (*entityIterator)->render();

        //if(((*entityIterator)->type() == PLAYER) || ((*entityIterator)->type() == ZOMBIE)) {
        //    Game::instance()->renderer()->drawLifeBar(*entityIterator, levelArea_);
        //}
    }

    //userInterface_->render();

    // FOR TESTING
    //tile_->render();
    //tile2_->render();
    eventHandler_->update();
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
        //userInterface_->characterPanel(0)->setEntity(entity);
    }
    else if(type == HUMAN) {
        entity->setControllable(false);
    }
    else if(type == ZOMBIE) {
        entity->setSelectable(false);
        entity->setControllable(false);
        entity->setMaximumSpeed(kEntityDefaultVelocity * 0.6);

        int randomNum = rand() % 5 + 1;

        //std::string asset;
        //asset = kAssetSpriteZombie1;

     /* switch(randomNum) {
            case 1: asset = kAssetSpriteZombie1; break;
            case 2: asset = kAssetSpriteZombie2; break;
            case 3: asset = kAssetSpriteZombie3; break;
            case 4: asset = kAssetSpriteZombie4; break;
            case 5: asset = kAssetSpriteZombie5; break;
            case 6: asset = kAssetSpriteZombie6; break;
            default: asset = kAssetSpriteZombie1; break;
       } */
    }

    Game::instance()->entityManager()->addObject(entity);

    entity->move(Point(22, 16));
    //entity->move(Point(10, 3));
    return entity;
}


