#include "ui/panel.h"
#include "point.h"
#include "util/logger.h"

Panel::Panel()
{
    position_ = Point(0, 0);
    width_ = 0;
    height_ = 0;

    texture_ = nullptr;
    visible_ = true;
}

Panel::~Panel()
{
    SDL_DestroyTexture(texture_);
}


