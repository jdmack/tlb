#include <stdlib.h>
#include <time.h>
#include "SDL2/SDL.h"

// Project Files
#include "game.h"
#include "entity.h"
#include "gfx/renderer.h"
#include "entity_manager.h"
#include "event_manager.h"
#include "util/logger.h"
#include "gfx/camera.h"
#include "level.h"
#include "gs_level.h"
#include "gs_level_select.h"
#include "game_state.h"
#include "util/global_timer.h"
#include "event/event_dispatcher.h"

Game * Game::instance_;// = nullptr;

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

    current_state_ = nullptr;
    next_state_ = nullptr;
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

    // Setup initial state - need to do this after renderer is initialized or bad things happen
    current_state_ = static_cast<GameState *>(new GSLevel());   // change this
    //current_state_ = static_cast<GameState *>(new GSLevelSelect());

    if(!current_state_->init()) {
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
    while(!quit_) {

        // Handle Events - state agnostic
        event_manager_->handle_events();

        // Update
        //if(delta_timer_.get_ticks() >= 33) {
        bool keep_state = current_state_->update(delta_timer_.get_ticks());

        delta_timer_.start();

        // Draw
        //renderer_->clear();
        current_state_->render();

        renderer_->update();

        if(!keep_state) {
            change_state();
        }
    }

}

bool Game::change_state()
{
    current_state_->end();

    if(next_state_ == nullptr) {
        quit_ = true;
        return true;
    }

    current_state_ = next_state_;
    next_state_ = nullptr;

    current_state_->init();

    return true;
}


// placeholder functions (not implemented yet)

void Game::process_arguments(int argc, char * argv[])
{

}
