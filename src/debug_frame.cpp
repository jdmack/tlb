#include <sstream>
#include "SDL/SDL_ttf.h"
#include "debug_frame.h"
#include "assets.h"
#include "coordinate.h"
#include "evengent.h"
#include "util/logger.h"

DebugFrame::DebugFrame(Screen * screen)
{
    x_position_ = kDebugFrameXPosition;
    y_position_ = kDebugFrameYPosition;
    width_      = kDebugFrameWidth;
    height_     = kDebugFrameHeight;

    fg_color_ = { 255, 0, 255 };
    font_ = TTF_OpenFont(kAssetFontConsolas.c_str(), kDebugFrameFontSize);
    texture_ = nullptr;
    screen_ = screen;
    shown_ = true;

    background_ = { x_position_ - 2 * kDebugFrameBorder, y_position_ - 2 * kDebugFrameBorder, width_ + 2 * kDebugFrameBorder, height_ + 2 * kDebugFrameBorder };
}

DebugFrame::~DebugFrame()
{
    TTF_CloseFont(font_);
    SDL_DestroyTexture(texture_);
}


void DebugFrame::draw()
{
    // Draw background rectangle
    SDL_SetRenderDrawColor(screen_->renderer(), 20, 20, 20, 200);
    SDL_RenderFillRect(screen_->renderer(), &background_);

    // Create mouse message surface
    Coordinate mouse = Evengent::mouse_position();
    std::stringstream message;
    message << "Mouse: (" << mouse.x_position() << "," << mouse.y_position() << ")";
    SDL_Surface * surface = TTF_RenderText_Solid(font_, message.str().c_str(), fg_color_);
    if(surface == nullptr) {
        Logger::write(Logger::string_stream << "Text Error: " << TTF_GetError());
    }

    // Render debug frame
    SDL_Rect offset = { x_position_, y_position_, surface->w, surface->h };
    texture_ = SDL_CreateTextureFromSurface(screen_->renderer(), surface);
    if(texture_ == nullptr) {
        Logger::write(Logger::string_stream << "DebugFrame Texture: " << SDL_GetError());
        return;
    }
    screen_->render_texture(texture_, &offset, nullptr);

    SDL_FreeSurface(surface);
}

bool DebugFrame::toggle()
{
    shown_ = !shown_;
    return shown_;
}
