
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
    //Dot * dot1 = new Dot();
    //entigent_->add_object(dot1);

    Dot * dot2 = new Dot(kScreenWidth / 2, kScreenHeight / 2, 0);
    entigent_->add_object(dot2);

    // Main Loop
    while(quit_ == false) {


        // Handle Events
        evengent_->handle_events();

        // Update
        //dot1->update(delta_timer_.get_ticks());
        dot2->update(delta_timer_.get_ticks());

        delta_timer_.start();

        // Draw
        screen_->clear();
        //dot1->draw(screen_);
        dot2->draw();

        //SDL_Surface * select_surface = screen_->load_image_alpha(kAssetArtGreenCircle);
        //screen_->blit_surface(dot2->x_position() - dot2->width() / 2, dot2->y_position() - dot2->width() / 2, select_surface);


        //screen_->blit_surface(game);

        if(!screen_->update()) {
            exit_code_ = 1;
        }
    }

    //delete(dot1);
    delete(dot2);
}

// placeholder functions (not implemented yet)

void TlbGame::process_arguments(int argc, char * argv[])
{

}
