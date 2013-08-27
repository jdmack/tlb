
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
    entigent_->register_game(this);
    evengent_ = new Evengent();
    evengent_->register_game(this);
}

TlbGame::~TlbGame()
{
    delete screen_;
}

int TlbGame::run()
{
    Logger::open(kLogFilename);
    Logger::write("running");
    SDL_Delay(3000);
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
    Dot * dot1 = new Dot();
    entigent_->add_object(dot1);

    Dot * dot2 = new Dot(0, kScreenHeight - kDotHeight);
    entigent_->add_object(dot2);

    // Main Loop
    while(quit_ == false) {


        // Handle Events
        evengent_->handle_events();

        // Update
        dot1->move(delta_timer_.get_ticks());
        dot2->move(delta_timer_.get_ticks());

        delta_timer_.start();

        // Draw
        screen_->clear();
        dot1->draw(screen_);
        dot2->draw(screen_);

        //screen_->blit_surface(game);

        if(!screen_->update()) {
            exit_code_ = 1;
        }
    }

    delete(dot1);
    delete(dot2);
}

// placeholder functions (not implemented yet)

void TlbGame::process_arguments(int argc, char * argv[])
{

}

void TlbGame::set_quit(bool quit)
{
    quit_ = quit;
}

Screen * TlbGame::screen()
{
    return screen_;
}

Entigent * TlbGame::entigent()
{
    return entigent_;
}