#ifndef TLB_ANIMATION_H_
#define TLB_ANIMATION_H_

#include <string>
#include <map>
#include "SDL2/SDL.h"

class Animation
{
    private:
        std::string key_;
        int time_;
        std::map<std::string, SDL_Rect> frames_;
        std::map<std::string, SDL_Rect>::iterator current_;

    public:
        Animation();
        Animation(std::string key, int time);

        // accessors
        std::string key() const { return key_; }
        int time() const { return time_; }
        std::map<std::string, SDL_Rect> frames() {return frames_; }
        std::map<std::string, SDL_Rect>::iterator current() const { return current_; }

        void insert_frame(std::string frame_key, SDL_Rect frame);
        SDL_Rect get_frame(std::string frame_key);
};

#endif
