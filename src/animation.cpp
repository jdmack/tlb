#include <string>
#include "animation.h"
#include "utils/logger.h"

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

void Animation::insert_frame(std::string frame_key, SDL_Rect frame)
{
    //frames_.insert(std::pair<std::string, SDL_Rect>(frame_key, frame));
    frames_.push_back(frame);
    //current_ = frames_.begin();
}

SDL_Rect Animation::current_frame()
{
    return frames_.at(current_);
}

void Animation::next_frame()
{
    //Logger::write(Logger::string_stream << std::distance(frames_.begin(), current_));
    //Logger::write(Logger::string_stream << frames_.size());
    //if(frames_.size() == 1) {
        //return;
    //}
    Logger::write("Next Frame");
    ++current_;
    if(current_ >= frames_.size()) {
        Logger::write(Logger::string_stream << key_ << " - Starting over, frames_.size(): " << frames_.size());
        current_ = 0;

    }
}
