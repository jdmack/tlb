#ifndef TLB_COLOR_H_
#define TLB_COLOR_H_

#include "SDL2/SDL.h"

class Color
{
    private:
        Uint8 red_;
        Uint8 green_;
        Uint8 blue_;

    public:
        Color();
        Color(Uint8 red, Uint8 green, Uint8 blue);
        Uint8 red() const { return red_; }
        Uint8 green() const { return green_; }
        Uint8 blue() const { return blue_; }
};

const Color kColorBlack = Color(0x00, 0x00, 0x00);
const Color kColorWhite = Color(0xFF, 0xFF, 0xFF);

#endif
