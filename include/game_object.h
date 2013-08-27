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
        static int id_counter_;
        int object_id_;

    public:
        GameObject();
        GameObject(float x, float y);
        virtual ~GameObject();
        std::string art_asset();
        void draw(Screen * screen);
        void set_surface(SDL_Surface * surface);
        void register_screen(Screen * screen);
        virtual bool contains_point(float x, float y);
        virtual void select();
        virtual void deselect();
        bool selected();
        bool selectable();
        int object_id();
};

#endif
