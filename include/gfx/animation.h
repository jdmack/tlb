#ifndef TLB_ANIMATION_H_
#define TLB_ANIMATION_H_

#include <string>
#include <map>
#include <vector>
#include "SDL2/SDL.h"

class Animation
{
    private:
        std::string key_;
        int time_;
        unsigned current_;
        std::vector<SDL_Rect> frames_;

    public:
        Animation();
        Animation(std::string key, int time);

        // accessors
        std::string key() const { return key_; }
        int time() const { return time_; }
        std::vector<SDL_Rect> frames() {return frames_; }
        int current() const { return current_; }

        void insert_frame(std::string frame_key, SDL_Rect frame);
        void next_frame();
        SDL_Rect current_frame();
};

#endif
