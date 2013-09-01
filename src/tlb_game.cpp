
#include "SDL/SDL.h"

// Project Files
#include "tlb_game.h"
#include "dot.h"
#include "assets.h"
#include "screen.h"
#include "entigent.h"
#include "evengent.h"
#include "util/logger.h"


TlbGame::TlbGame()
{
    exit_code_ = 0;
    quit_ = false;
    screen_ = new Screen();
    entigent_ = new Entigent();
    entigent_->set_game(this);
    evengent_ = new Evengent();
    evengent_->set_game(this);
}

TlbGame::~TlbGame()
{
    delete screen_;
}

int TlbGame::run()
{
    Logger::open(kLogFilename);
    Logger::write("running");

    if(screen_->init() == false) {
        return 1;
    }

    delta_timer_.start();

    game_loop();

    //Clean up
    screen_->clean_up();

    Logger::write("shutting down");
    return exit_code_;
}

void TlbGame::game_loop()
{
    // Create a dot

    Dot * dot1 = new Dot(kScreenWidth / 2, kScreenHeight / 2, 0);
    entigent_->add_object(dot1);

    // Main Loop
    while(quit_ == false) {

        // Handle Events
        evengent_->handle_events();

        // Update
        dot1->update(delta_timer_.get_ticks());

        delta_timer_.start();

        // Draw
        screen_->clear();
        dot1->draw();

        screen_->update();
    }

    delete(dot1);
}

// placeholder functions (not implemented yet)

void TlbGame::process_arguments(int argc, char * argv[])
{

}
