#ifndef TLB_RECTANGLE_H_
#define TLB_RECTANGLE_H_

#include "SDL2/SDL.h"

class Rectangle
{
    private:
        int x_;
        int y_;
        int width_;
        int height_;
        SDL_Rect * sdl_rect_;

    public:
        Rectangle();
        Rectangle(int x, int y, int width, int height);

        // accessors
        int x() const { return x_; }
        int y() const { return y_; }
        int width() const { return width_; }
        int height() const { return height_; }
        SDL_Rect * sdl_rect() const { return sdl_rect_; }

        // mutators
        void set_x(int x) { x_ = x; }
        void set_y(int y) { y_ = y; }
        void set_width(int width) { width_ = width; }
        void set_height(int height) { height_ = height; }

        void set_sdl_rect();
        void set_sdl_rect(int x, int y, int width, int height);
};

#endif
