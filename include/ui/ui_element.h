#ifndef TLB_UI_UI_ELEMENT_H_
#define TLB_UI_UI_ELEMENT_H_

#include "SDL2/SDL.h"
#include "constants.h"
#include "renderer.h"
#include "point.h"

class Frame;

class UIElement
{
    protected:
        Point position_;
        int width_;
        int height_;
        bool visible_;
        std::string art_asset_;

        SDL_Texture * texture_;


    public:
        UIElement();
        ~UIElement();

        // accessors
        Point position() const { return position_; }
        int width() const { return width_; }
        int height() const { return height_; }
        bool visible() const { return visible_; }
        std::string art_asset() const { return art_asset_; }

        // mutators
        void set_position(Point position) { position_ = position; }
        void set_width(int width) { width_ = width; }
        void set_height(int height) { height_ = height; }
        void set_visible(bool visible) { visible_ = visible; }
        void set_art_asset(std::string art_asset) { art_asset_ = art_asset; }

        void render(Frame * frame = nullptr);
        void update();
        bool toggle();
};

#endif