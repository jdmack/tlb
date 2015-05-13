#include <vector>

#include "gs_level.h"

#include "gfx/renderer.h"
#include "game.h"
#include "level.h"
#include "entity_manager.h"
#include "entity.h"
#include "assets.h"
#include "util/logger.h"
#include "ui/user_interface.h"
#include "event/eh_level.h"
#include "event/event_dispatcher.h"
#include "ui/character_panel.h"


GSLevel::GSLevel()
{
    type_ = GS_LEVEL;
    user_interface_ = nullptr;
    level_area_ = new Frame(200, 0, 976, 864);
    event_handler_ = new EHLevel();
}

int GSLevel::init()
{
    int return_code = 0;

    // Load level
    Level * level = new Level();

    //if(!level->load(kMapTestHexIsometric)) {
    if(!level->load(kMapTest24x18)) {
        Logger::write(Logger::ss << "Failed to load map");
        return_code = 1;
    }

    Game::instance()->set_level(level);

    user_interface_ = new UserInterface();

    EventDispatcher::instance()->register_handler(event_handler_);

    // (264,216)
    /*Entity * char1   = */spawn_entity(PLAYER, Point(48 * 1 + 24, 48 * 1 + 24), 90);
    /*Entity * zombie1 = */spawn_entity(ZOMBIE, Point(48 * 5 + 24, 48 * 5 + 24), 270);

    //Entity * zombie2 = spawn_entity(ZOMBIE, Point(48 * 5 + 24, 48 * 1 + 24), 90);
    //Entity * zombie3 = spawn_entity(ZOMBIE, Point(48 * 6 + 24, 48 * 1 + 24), 90);
    //Entity * zombie4 = spawn_entity(ZOMBIE, Point(48 * 7 + 24, 48 * 1 + 24), 90);
    //Entity * zombie5 = spawn_entity(ZOMBIE, Point(48 * 8 + 24, 48 * 1 + 24), 0);
    //Entity * zombie6 = spawn_entity(ZOMBIE, Point(48 * 7 + 24, 48 * 1 + 24), 0);

    // FOR TESTING

    return return_code;
}

bool GSLevel::update(int delta_ticks)
{
    if(win_condition_.check()) {
        Game::instance()->set_quit(true);
    }

    std::vector<Entity *> entities = Game::instance()->entity_manager()->get_entities();

    // Update
    for(std::vector<Entity *>::iterator entity_iterator = entities.begin(); entity_iterator != entities.end(); ++entity_iterator) {
        (*entity_iterator)->update(delta_ticks);
    }

    user_interface_->update();

    return true;
}
void GSLevel::render()
{
    Game::instance()->level()->render(level_area_);

    // Render
    std::vector<Entity *> entities = Game::instance()->entity_manager()->get_entities();
    for(std::vector<Entity *>::iterator entity_iterator = entities.begin(); entity_iterator != entities.end(); ++entity_iterator) {
        (*entity_iterator)->render(level_area_);

        if(((*entity_iterator)->type() == PLAYER) || ((*entity_iterator)->type() == ZOMBIE)) {
            Game::instance()->renderer()->draw_life_bar(*entity_iterator, level_area_);
        }
    }

    user_interface_->render();

    // FOR TESTING
}

void GSLevel::end()
{
    Game::instance()->entity_manager()->delete_all();
    // TODO(2014-08-06/JM): Move Level into this class
    // TODO(2014-08-06/JM): Delete Level
}

Entity * GSLevel::spawn_entity(EntityType type, Point position, double rotation)
{
    Entity * entity = new Entity(type, position, rotation);
    if(type == PLAYER) {
        entity->set_controllable(true);
        entity->create_sprite(kAssetSpriteHuman1);
        user_interface_->character_panel(0)->set_entity(entity);
    }
    else if(type == HUMAN) {
        entity->set_controllable(false);
        entity->create_sprite(kAssetSpriteHuman1);
    }
    else if(type == ZOMBIE) {
        entity->set_selectable(false);
        entity->set_controllable(false);
        entity->set_maximum_speed(kEntityDefaultVelocity * 0.6);

        int random_num = rand() % 5 + 1;

        std::string asset;
        asset = kAssetSpriteZombie1;

     /* switch(random_num) {
            case 1: asset = kAssetSpriteZombie1; break;
            case 2: asset = kAssetSpriteZombie2; break;
            case 3: asset = kAssetSpriteZombie3; break;
            case 4: asset = kAssetSpriteZombie4; break;
            case 5: asset = kAssetSpriteZombie5; break;
            case 6: asset = kAssetSpriteZombie6; break;
            default: asset = kAssetSpriteZombie1; break;
       } */
        entity->create_sprite(asset);
    }

    Game::instance()->entity_manager()->add_object(entity);
    Game::instance()->renderer()->init_object(entity);


    return entity;
}


