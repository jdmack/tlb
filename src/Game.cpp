#include <stdlib.h>
#include <time.h>
#include "SDL2/SDL.h"

// Project Files
#include "Game.h"
#include "Entity.h"
#include "gfx/Renderer.h"
#include "EntityManager.h"
#include "EventManager.h"
#include "util/Logger.h"
#include "gfx/Camera.h"
#include "Level.h"
#include "GSLevel.h"
#include "GSLevelSelect.h"
#include "GameState.h"
#include "util/GlobalTimer.h"
#include "event/EventDispatcher.h"

Game * Game::instance_;// = nullptr;

Game::Game()
{
    exitCode_ = 0;
    quit_ = false;
    renderer_ = new Renderer();
    entityManager_ = new EntityManager();
    eventManager_ = new EventManager();
    level_ = nullptr;

    currentState_ = nullptr;
    nextState_ = nullptr;
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
    currentState_ = static_cast<GameState *>(new GSLevel());   // change this
    //currentState_ = static_cast<GameState *>(new GSLevelSelect());

    if(!currentState_->init()) {
        return 1;
    }


    EventDispatcher::instance();
    GlobalTimer::instance()->start();

    deltaTimer_.start();

    gameLoop();

    //Clean up
    renderer_->cleanUp();

    Logger::write("Game shutting down");
    return exitCode_;
}

void Game::gameLoop()
{
    //currentState_->init();
    // Main Loop
    while(!quit_) {

        // Handle Events - state agnostic
        eventManager_->handleEvents();

        // Update
        //if(deltaTimer_.getTicks() >= 33) {
        bool keepState = currentState_->update(deltaTimer_.getTicks());

        deltaTimer_.start();

        // Draw
        renderer_->clear();
        currentState_->render();

        renderer_->update();

        if(!keepState) {
            changeState();
        }
    }

}

bool Game::changeState()
{
    currentState_->end();

    if(nextState_ == nullptr) {
        quit_ = true;
        return true;
    }

    currentState_ = nextState_;
    nextState_ = nullptr;

    currentState_->init();

    return true;
}


// placeholder functions (not implemented yet)

void Game::processArguments(int argc, char * argv[])
{

}
