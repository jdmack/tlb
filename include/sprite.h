#ifndef TLB_SPRITE_H_
#define TLB_SPRITE_H_

#include <string>
#include "SDL/SDL.h"

class GameObject;
class Screen;

class Sprite
{
    private:
        double rotation_;
        SDL_Surface * surface_;
        Screen * screen_;
        std::string art_asset_;
        std::string select_art_asset_;
        GameObject * object_;

    public:
        Sprite(GameObject * object, std::string asset, std::string select_asset);

        // accessors
        double rotation() const { return rotation_; }
        std::string art_asset() const { return art_asset_; }
        SDL_Surface * surface() const { return surface_; }
        Screen * screen() const { return screen_; }

        // mutators
        void set_rotation(double rotation);
        void set_surface(SDL_Surface * surface) { surface_ = surface; }
        void set_screen(Screen * screen) { screen_ = screen; }
        void set_object(GameObject * object) { object_ = object; }

        void draw();
        void select();
        void deselect();

};

#endif
