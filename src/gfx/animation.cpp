#include <string>
#include "gfx/animation.h"
#include "util/logger.h"

Animation::Animation()
{
    key_ = "";
    time_ = 0;
    current_ = 0;
}
Animation::Animation(std::string key, int time)
{
    key_ = key;
    time_ = time;
    current_ = 0;
}

void Animation::insertFrame(std::string frameKey, SDL_Rect frame)
{
    //frames_.insert(std::pair<std::string, SDL_Rect>(frameKey, frame));
    frames_.pushBack(frame);
    //current_ = frames_.begin();
}

SDL_Rect Animation::currentFrame()
{
    return frames_.at(current_);
}

void Animation::nextFrame()
{
    //Logger::write(Logger::ss << std::distance(frames_.begin(), current_));
    //Logger::write(Logger::ss << frames_.size());
    //if(frames_.size() == 1) {
        //return;
    //}
    //Logger::write("Next Frame");
    ++current_;
    if(current_ >= frames_.size()) {
        //Logger::write(Logger::ss << key_ << " - Starting over, frames_.size(): " << frames_.size());
        current_ = 0;

    }
}
