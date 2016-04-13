#ifndef TLB_UI_TEXT_H_
#define TLB_UI_TEXT_H_

#include "SDL2/SDL.h"
#include "SDL2/SDLTtf.h"
#include "gfx/renderer.h"
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
        std::string fontAsset_;
        Color color_;

        SDL_Texture * texture_;
        Renderer * renderer_;

        TTF_Font * font_;

    public:
        Text();
        Text(std::string text, int size = kDefaultTextSize);
        ~Text();

        // accessors
        bool visible() const { return visible_; }

        // mutators
        void setPosition(Point position) { position_ = position; }
        void setWidth(int width) { width_ = width; }
        void setHeight(int height) { height_ = height; }
        void setSize(int size) { size_ = size; }
        void setWrap(int wrap) { wrap_ = wrap; }
        void setVisible(bool visible) { visible_ = visible; }
        void setColor(Color color) { color_ = color; }
        void setFontAsset(std::string fontAsset) { fontAsset_ = fontAsset; }

        void setText(std::string text);

        void update();
        void render(Frame * frame = nullptr);
        TTF_Font * loadFont(std::string filename, int size);
        void reloadFont();
};

#endif
