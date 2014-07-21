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


Game::Game()
{
    exit_code_ = 0;
    quit_ = false;
    renderer_ = new Renderer();
    entity_manager_ = new EntityManager(this);
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
    Entity * char1 = new Entity(this, 48 * 5 + 24, 48 * 3 + 24, 0);
    entity_manager_->add_object(char1);

    // Main Loop
    while(quit_ == false) {

        // Handle Events
        event_manager_->handle_events();

        // Update
        if(delta_timer_.get_ticks() >= 33) {
            char1->update(delta_timer_.get_ticks());
            delta_timer_.start();
        }


        // center camera
        camera_->center(char1);

        // Draw
        renderer_->clear();
        level_->render();
        char1->render();

        renderer_->update();
    }

    delete char1;
}

// placeholder functions (not implemented yet)

void Game::process_arguments(int argc, char * argv[])
{

}
