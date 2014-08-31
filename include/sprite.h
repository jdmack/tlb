#ifndef TLB_SPRITE_H_
#define TLB_SPRITE_H_

#include <map>
#include <string>
#include "util/timer.h"
#include "SDL2/SDL.h"
#include "animation.h"
#include "action/action.h"

class GameObject;
class Renderer;

class Sprite
{
    private:
        double width_;
        double height_;
        SDL_Texture * texture_;
        Renderer * renderer_;
        std::string art_asset_;
        std::string select_art_asset_;
        GameObject * object_;
        ActionType current_action_;
        double current_direction_;

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
        Renderer * renderer() const { return renderer_; }
        std::map<std::string, Animation> animations() const { return animations_; }

        // mutators
        void set_texture(SDL_Texture * texture) { texture_ = texture; }
        void set_renderer(Renderer * renderer) { renderer_ = renderer; }
        void set_object(GameObject * object) { object_ = object; }

        void render();
        void select();
        void deselect();
        void update();
};

#endif
