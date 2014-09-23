#ifndef TLB_UI_TEXT_H_
#define TLB_UI_TEXT_H_

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "renderer.h"
#include "color.h"
#include "point.h"

const int kDefaultTextWrap = 1000;
const int kDefaultTextSize = 28;

class Frame;

class Text
{
    private:
        Point position_;
        int width_;
        int height_;
        int size_;
        int wrap_;
        bool visible_;
        std::string text_;
        std::string font_asset_;
        Color color_;

        SDL_Texture * texture_;
        Renderer * renderer_;

        TTF_Font * font_;

    public:
        Text();
        Text(std::string text, int size = kDefaultTextSize);
        ~Text();

        // accessors

        // mutators
        void set_position(Point position) { position_ = position; }
        void set_width(int width) { width_ = width; }
        void set_height(int height) { height_ = height; }
        void set_size(int size) { size_ = size; }
        void set_wrap(int wrap) { wrap_ = wrap; }
        void set_visible(bool visible) { visible_ = visible; }
        void set_color(Color color) { color_ = color; }
        void set_font_asset(std::string font_asset) { font_asset_ = font_asset; }

        void set_text(std::string text);

        void update();
        void render(Frame * frame = nullptr);
        TTF_Font * load_font(std::string filename, int size);
        void reload_font();
};

#endif
