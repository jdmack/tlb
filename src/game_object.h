#ifndef TLB_GAME_OBJECT_H_
#define TLB_GAME_OBJECT_H_

#include <string>
#include "SDL/SDL.h"
#include "assets.h"

class Screen;

class GameObject
{
    protected:
        float x_position_;
        float y_position_;
        SDL_Surface * surface_;
        std::string art_asset_;
        Screen * screen_;
        bool selectable_;
        bool selected_;

    public:
        GameObject();
        GameObject(float x, float y);
        std::string art_asset();
        void draw(Screen * screen);
        void set_surface(SDL_Surface * surface);
        void register_screen(Screen * screen);
        bool contains_point(float x, float y);
        void select();
        void deselect();
        bool is_selected();
        bool selectable();
};

#endif
