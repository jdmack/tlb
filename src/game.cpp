#include "SDL2/SDL.h"

// Project Files
#include "game.h"
#include "dot.h"
#include "assets.h"
#include "screen.h"
#include "entigent.h"
#include "evengent.h"
#include "utils/logger.h"
#include "camera.h"
#include "level.h"


Game::Game()
{
    exit_code_ = 0;
    quit_ = false;
    screen_ = new Screen();
    entigent_ = new Entigent(this);
    evengent_ = new Evengent(this);
    camera_ = new Camera(this);
    screen_->set_camera(camera_);
    level_ = nullptr;
}

Game::~Game()
{
    delete screen_;
}

int Game::run()
{
    Logger::write("Game running");

    if(screen_->init() == false) {
        return 1;
    }

    // Load level
    level_ = new Level(this);
    if(!level_->load(kMapTest24x18)) {
        Logger::write(Logger::string_stream << "Failed to load map");
        exit_code_ = 1;
        return exit_code_;
    }
    delta_timer_.start();

    game_loop();

    //Clean up
    screen_->clean_up();

    Logger::write("Game shutting down");
    return exit_code_;
}

void Game::game_loop()
{
    // Create a dot
    Dot * dot1 = new Dot(this, level_->width() / 3, level_->height() / 3, 0);
    entigent_->add_object(dot1);

    // Main Loop
    while(quit_ == false) {

        // Handle Events
        evengent_->handle_events();

        // Update
        dot1->update(delta_timer_.get_ticks());

        delta_timer_.start();

        // center camera
        camera_->center(dot1);

        // Draw
        screen_->clear();
        level_->render();
        dot1->render();

        screen_->update();
    }

    delete dot1;
}

// placeholder functions (not implemented yet)

void Game::process_arguments(int argc, char * argv[])
{

}
