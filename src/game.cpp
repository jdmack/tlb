#include <stdlib.h>
#include <time.h>
#include "SDL2/SDL.h"

// Project Files
#include "game.h"
#include "entity.h"
#include "assets.h"
#include "renderer.h"
#include "entity_manager.h"
#include "event_manager.h"
#include "utils/logger.h"
#include "camera.h"
#include "level.h"
#include "actions/zombie_action.h"


Game::Game()
{
    exit_code_ = 0;
    quit_ = false;
    renderer_ = new Renderer();
    entity_manager_ = new EntityManager();
    event_manager_ = new EventManager(this);
    camera_ = new Camera(this);
    renderer_->set_camera(camera_);
    level_ = nullptr;
}

Game::~Game()
{
    delete renderer_;
}

int Game::run()
{
    Logger::write("Game running");

    srand((unsigned) time(NULL));

    if(renderer_->init() == false) {
        return 1;
    }

    // Load level
    level_ = new Level(this);
    //if(!level_->load(kMapTest24x18Blank)) {
    if(!level_->load(kMapTest24x18)) {
        Logger::write(Logger::string_stream << "Failed to load map");
        exit_code_ = 1;
        return exit_code_;
    }
    delta_timer_.start();

    game_loop();

    //Clean up
    renderer_->clean_up();

    Logger::write("Game shutting down");
    return exit_code_;
}

void Game::game_loop()
{
    // Create a dot
    Entity * char1 = spawn_entity(PLAYER, Point(48 * 5 + 24, 48 * 3 + 24), 0);
    Entity * zombie1 = spawn_entity(ZOMBIE, Point(48 * 8 + 24, 48 * 3 + 24), 0);
    //Entity * zombie2 = spawn_entity(ZOMBIE, Point(48 * 9 + 24, 48 * 3 + 24), 0);
    //Entity * zombie3 = spawn_entity(ZOMBIE, Point(48 * 10 + 24, 48 * 3 + 24), 0);
    //Entity * zombie4 = spawn_entity(ZOMBIE, Point(48 * 11 + 24, 48 * 3 + 24), 0);
    //Entity * zombie5 = spawn_entity(ZOMBIE, Point(48 * 12 + 24, 48 * 3 + 24), 0);
    //Entity * zombie6 = spawn_entity(ZOMBIE, Point(48 * 13 + 24, 48 * 3 + 24), 0);


    //std::vector<GameObject *> objects = entity_manager_->objects();
    // Main Loop
    while(quit_ == false) {

        // Handle Events
        event_manager_->handle_events();

        // Update
        if(delta_timer_.get_ticks() >= 33) {
            char1->update(delta_timer_.get_ticks());
            zombie1->update(delta_timer_.get_ticks());
            //zombie2->update(delta_timer_.get_ticks());
            //zombie3->update(delta_timer_.get_ticks());
            //zombie4->update(delta_timer_.get_ticks());
            //zombie5->update(delta_timer_.get_ticks());
            //zombie6->update(delta_timer_.get_ticks());

            delta_timer_.start();
        }


        // center camera
        camera_->center(char1);

        // Draw
        renderer_->clear();
        level_->render();
        char1->render();
        zombie1->render();
        //zombie2->render();
        //zombie3->render();
        //zombie4->render();
        //zombie5->render();
        //zombie6->render();
        renderer_->draw_life_bar(char1);

        renderer_->update();
    }

    //for(std::vector<GameObject *>::iterator object_iterator = objects->begin(); object_iterator != objects->end(); ++object_iterator) {
    //    *object_iterator
    //}
    delete char1;
    delete zombie1;
}

Entity * Game::spawn_entity(EntityType type, Point position, double rotation)
{
    Entity * entity = new Entity(this, position, rotation);
    if(type == PLAYER) {
        entity->set_controllable(true);
        entity->create_sprite(kAssetSpriteHuman1);
    }
    else if(type == HUMAN) {
        entity->set_controllable(false);
        entity->create_sprite(kAssetSpriteHuman1);
    }
    else if(type == ZOMBIE) {
        entity->set_controllable(false);

        int random_num = rand() % 5 + 1;

        std::string asset;
        switch(random_num) {
            case 1: asset = kAssetSpriteZombie1; break;
            case 2: asset = kAssetSpriteZombie2; break;
            case 3: asset = kAssetSpriteZombie3; break;
            case 4: asset = kAssetSpriteZombie4; break;
            case 5: asset = kAssetSpriteZombie5; break;
            case 6: asset = kAssetSpriteZombie6; break;
            default: asset = kAssetSpriteZombie1; break;
        }
        entity->create_sprite(asset);

        ZombieAction * zombie_action = new ZombieAction();
        zombie_action->set_entity_manager(entity_manager_);
        zombie_action->set_game(this);

        entity->set_current_action(zombie_action);
    }

    entity_manager_->add_object(entity);
    renderer_->init_object(entity);


    return entity;
}



// placeholder functions (not implemented yet)

void Game::process_arguments(int argc, char * argv[])
{

}
