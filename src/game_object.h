#ifndef TLB_GAME_OBJECT_H_
#define TLB_GAME_OBJECT_H_

#include <string>
#include "SDL/SDL.h"

class Screen;

class GameObject
{
    protected:
        float x_position_;
        float y_position_;
        SDL_Surface * surface_;
        std::string art_asset_;

    public:
        GameObject(std::string art_asset);
        std::string art_asset();
        void draw(Screen * screen);
        void set_surface(SDL_Surface * surface);
};

#endif
