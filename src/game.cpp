#include <stdlib.h>
#include <time.h>
#include "SDL2/SDL.h"

// Project Files
#include "game.h"
#include "entity.h"
#include "renderer.h"
#include "entity_manager.h"
#include "event_manager.h"
#include "utils/logger.h"
#include "camera.h"
#include "level.h"
#include "gs_level.h"
#include "game_state.h"
#include "utils/global_timer.h"


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

    current_state_ = static_cast<GameState *>(new GSLevel(this));
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

    if(current_state_->init() == 1) {
        return 1;
    }
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
        if(delta_timer_.get_ticks() >= 33) {
            current_state_->update(delta_timer_.get_ticks());
            delta_timer_.start();
        }


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
