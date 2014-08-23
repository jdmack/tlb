#ifndef TLB_PANEL_H_
#define TLB_PANEL_H_

#include "SDL2/SDL.h"
#include "constants.h"
#include "renderer.h"
#include "point.h"

class Panel
{
    private:
        Point position_;
        int width_;
        int height_;
        bool visible_;
        SDL_Color color_;

        SDL_Texture * texture_;
        Renderer * renderer_;


    public:
        Panel();
        Panel(Renderer * renderer);
        ~Panel();

        // accessors
        Point position() const { return position_; }
        int width() const { return width_; }
        int height() const { return height_; }
        bool visible() const { return visible_; }
        SDL_Color color() const { return color_; }

        // mutators
        void set_position(Point position) { position_ = position; }
        void set_width(int width) { width_ = width; }
        void set_height(int height) { height_ = height; }
        void set_visible(bool visible) { visible_ = visible; }
        void set_color(SDL_Color color) { color_ = color; }
        void set_alpha(Uint8 alpha) { color_.a= alpha; }

        void render();
        bool toggle();
};

#endif
