#include <stdlib.h>
#include <time.h>
#include "SDL2/SDL.h"

// Project Files
#include "game.h"
#include "entity.h"
#include "renderer.h"
#include "entity_manager.h"
#include "event_manager.h"
#include "util/logger.h"
#include "camera.h"
#include "level.h"
#include "gs_level.h"
#include "game_state.h"
#include "util/global_timer.h"
#include "event/event_dispatcher.h"

Game * Game::instance_ = nullptr;

Game::Game()
{
    exit_code_ = 0;
    quit_ = false;
    renderer_ = new Renderer();
    entity_manager_ = new EntityManager();
    event_manager_ = new EventManager();
    camera_ = new Camera();
    renderer_->set_camera(camera_);
    level_ = nullptr;

    current_state_ = static_cast<GameState *>(new GSLevel());

    Game::instance_ = nullptr;
}

Game::~Game()
{
    delete renderer_;
}

Game * Game::instance()
{
    if(instance_ == nullptr) {
        instance_ = new Game();
    }
    return instance_;
}


int Game::run()
{
    Logger::write("Game running");

    srand((unsigned) time(NULL));

    if(renderer_->init() == false) {
        return 1;
    }

    if(current_state_->init() == 1) {
        return 1;
    }
    EventDispatcher::instance();
    GlobalTimer::instance()->start();

    delta_timer_.start();

    game_loop();

    //Clean up
    renderer_->clean_up();

    Logger::write("Game shutting down");
    return exit_code_;
}

void Game::game_loop()
{
    //current_state_->init();
    // Main Loop
    while(quit_ == false) {

        // Handle Events
        event_manager_->handle_events();

        // Update
        //if(delta_timer_.get_ticks() >= 33) {
        current_state_->update(delta_timer_.get_ticks());
        delta_timer_.start();
        //}


        // center camera
        //camera_->center(char1);

        // Draw
        renderer_->clear();
        current_state_->render();

        renderer_->update();
    }

    current_state_->end();
}


// placeholder functions (not implemented yet)

void Game::process_arguments(int argc, char * argv[])
{

}
