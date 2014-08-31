#ifndef TLB_TEXT_H_
#define TLB_TEXT_H_

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "renderer.h"
#include "color.h"
#include "point.h"

class Text
{
    private:
        Point position_;
        int width_;
        int height_;
        int size_;
        bool visible_;
        std::string text_;
        Color color_;

        SDL_Texture * texture_;
        Renderer * renderer_;

        TTF_Font * font_;

    public:
        Text();
        Text(std::string text);
        ~Text();

        // accessors

        // mutators
        void set_position(Point position) { position_ = position; }
        void set_width(int width) { width_ = width; }
        void set_height(int height) { height_ = height; }
        void set_size(int size) { size_ = size; }
        void set_visible(bool visible) { visible_ = visible; }
        void set_color(Color color) { color_ = color; }

        void set_text(std::string text);

        void render();
        TTF_Font * load_font(std::string filename, int size);
};

#endif
