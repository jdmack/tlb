#ifndef TLB_GAME_OBJECT_H_
#define TLB_GAME_OBJECT_H_

#include <string>
#include "SDL/SDL.h"
#include "assets.h"

class Screen;

class GameObject
{
    protected:
        static int id_counter_;
        int object_id_;
        float x_position_;
        float y_position_;
        float rotation_;
        bool selectable_;
        bool selected_;
        std::string art_asset_;
        SDL_Surface * surface_;
        Screen * screen_;

    public:
        // constructors/destructors
        GameObject();
        GameObject(float x, float y, float rot);
        virtual ~GameObject();

        // accessors
        int object_id();
        float x_position();
        float y_position();
        float rotation();
        bool selectable();
        bool selected();
        std::string art_asset();
        SDL_Surface * surface();
        Screen * screen();

        // mutators
        void set_surface(SDL_Surface * surface);
        void set_screen(Screen * screen);


        void draw(Screen * screen);
        virtual bool contains_point(float x, float y);
        virtual void select();
        virtual void deselect();
};

#endif
