#include <string>
#include "animation.h"
#include "utils/logger.h"

Animation::Animation()
{
    key_ = "";
    time_ = 0;
}
Animation::Animation(std::string key, int time)
{
    key_ = key;
    time_ = time;
}

void Animation::insert_frame(std::string frame_key, SDL_Rect frame)
{
    frames_.insert(std::pair<std::string, SDL_Rect>(frame_key, frame));
    current_ = frames_.begin();
}

SDL_Rect Animation::get_frame(std::string frame_key)
{
    return frames_[frame_key];
}
