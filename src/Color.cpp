/*
 * color.cpp
 *
 *  Created on: Aug 31, 2013
 *      Author: James
 */

#include "SDL2/SDL.h"
#include "Color.h"

Color::Color()
{
    red_ = 0x00;
    green_ = 0x00;
    blue_ = 0x00;
}

Color::Color(Uint8 red, Uint8 green, Uint8 blue)
{
    red_ = red;
    green_ = green;
    blue_ = blue;
}
