#ifndef TLB_SPRITE_H_
#define TLB_SPRITE_H_

#include <map>
#include <string>
#include "utils/timer.h"
#include "SDL2/SDL.h"
#include "animation.h"

class GameObject;
class Screen;

class Sprite
{
    private:
        double width_;
        double height_;
        SDL_Texture * texture_;
        Screen * screen_;
        std::string art_asset_;
        std::string select_art_asset_;
        GameObject * object_;

        Animation current_animation_;
        std::map<std::string, Animation> animations_;

        Timer animation_timer_;

    public:
        Sprite(GameObject * object, std::string asset, std::string select_asset);

        // accessors
        double width() const { return width_; }
        double height() const { return height_; }
        std::string art_asset() const { return art_asset_; }
        SDL_Texture * texture() const { return texture_; }
        Screen * screen() const { return screen_; }
        std::map<std::string, Animation> animations() const { return animations_; }

        // mutators
        void set_texture(SDL_Texture * texture) { texture_ = texture; }
        void set_screen(Screen * screen) { screen_ = screen; }
        void set_object(GameObject * object) { object_ = object; }

        void render();
        void select();
        void deselect();
        void update();
};

#endif
