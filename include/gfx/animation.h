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

        void insertFrame(std::string frameKey, SDL_Rect frame);
        void nextFrame();
        SDL_Rect currentFrame();
};

#endif
