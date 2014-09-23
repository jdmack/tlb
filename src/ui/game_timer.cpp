#include "ui/game_timer.h"
#include "point.h"
#include "util/logger.h"
#include "frame.h"
#include "util/global_timer.h"
#include "ui/text.h"

GameTimer::GameTimer()
{
    position_ = Point(0, 0);
    width_ = 0;
    height_ = 0;

    texture_ = nullptr;
    visible_ = true;
    start_ticks_ = GlobalTimer::instance()->get_ticks();
    text_ = new Text("00:00");
    text_->set_position(Point(25, 25));
    text_->set_size(55);
    text_->reload_font();
    text_->update();

}

GameTimer::~GameTimer()
{
    SDL_DestroyTexture(texture_);
}


void GameTimer::render(Frame * frame)
{
    UIElement::render(frame);
    text_->render(frame);
}

void GameTimer::update()
{
    int ticks = GlobalTimer::instance()->get_ticks();
    std::string str = "";
    if((ticks - start_ticks_) >= 1000) {
        str = convert_time(ticks - start_ticks_);
        text_->set_text(str);
    }
}

std::string GameTimer::convert_time(int ticks)
{

    int minutes = (ticks % (1000*60*60)) / (1000*60);
    int seconds = ((ticks % (1000*60*60)) % (1000*60)) / 1000;

    std::ostringstream string_stream;

    if(minutes < 10) string_stream << "0";
    string_stream << minutes << ":";
    if(seconds < 10) string_stream << "0";
    string_stream << seconds;
    std::string str = string_stream.str();

    return str;

}
