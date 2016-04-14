#include "ui/GameTimer.h"
#include "Point.h"
#include "util/Logger.h"
#include "Frame.h"
#include "util/GlobalTimer.h"
#include "ui/Text.h"

GameTimer::GameTimer()
{
    position_ = Point(0, 0);
    width_ = 0;
    height_ = 0;

    texture_ = nullptr;
    visible_ = true;
    startTicks_ = GlobalTimer::instance()->getTicks();
    text_ = new Text("00:00");
    text_->setPosition(Point(25, 25));
    text_->setSize(55);
    text_->reloadFont();
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
    int ticks = GlobalTimer::instance()->getTicks();
    std::string str = "";
    if((ticks - startTicks_) >= 1000) {
        str = convertTime(ticks - startTicks_);
        text_->setText(str);
    }
}

std::string GameTimer::convertTime(int ticks)
{

    int minutes = (ticks % (1000*60*60)) / (1000*60);
    int seconds = ((ticks % (1000*60*60)) % (1000*60)) / 1000;

    std::ostringstream stringStream;

    if(minutes < 10) stringStream << "0";
    stringStream << minutes << ":";
    if(seconds < 10) stringStream << "0";
    stringStream << seconds;
    std::string str = stringStream.str();

    return str;

}
