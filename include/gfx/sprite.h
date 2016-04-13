#ifndef TLB_SPRITE_H_
#define TLB_SPRITE_H_

#include <map>
#include <string>
#include "util/timer.h"
#include "SDL2/SDL.h"
#include "gfx/animation.h"
#include "action/action.h"

class GameObject;
class Renderer;
class Frame;

class Sprite
{
    private:
        int width_;
        int height_;
        SDL_Texture * texture_;
        Renderer * renderer_;
        std::string artAsset_;
        std::string selectArtAsset_;
        GameObject * object_;
        ActionType currentAction_;
        double currentDirection_;

        Animation currentAnimation_;
        std::map<std::string, Animation> animations_;

        Timer animationTimer_;

    public:
        Sprite(GameObject * object, std::string asset, std::string selectAsset);

        // accessors
        double width() const { return width_; }
        double height() const { return height_; }
        std::string artAsset() const { return artAsset_; }
        SDL_Texture * texture() const { return texture_; }
        Renderer * renderer() const { return renderer_; }
        std::map<std::string, Animation> animations() const { return animations_; }

        // mutators
        void setTexture(SDL_Texture * texture) { texture_ = texture; }
        void setRenderer(Renderer * renderer) { renderer_ = renderer; }
        void setObject(GameObject * object) { object_ = object; }

        void render(Frame * frame = nullptr);
        void select();
        void deselect();
        void update();
};

#endif
