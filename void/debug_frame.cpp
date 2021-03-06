/*
#include <sstream>
#include "debug_frame.h"
#include "assets.h"
#include "point.h"
#include "event_manager.h"
#include "util/logger.h"

DebugFrame::DebugFrame(Renderer * renderer)
{
    x_position_ = kDebugFrameXPosition;
    y_position_ = kDebugFrameYPosition;
    width_      = kDebugFrameWidth;
    height_     = kDebugFrameHeight;

    fg_color_ = { 255, 0, 255 };
    //font_ = TTF_OpenFont(kAssetFontConsolas.c_str(), kDebugFrameFontSize);
    texture_ = nullptr;
    renderer_ = renderer;
    shown_ = true;

    background_ = { x_position_ - 2 * kDebugFrameBorder, y_position_ - 2 * kDebugFrameBorder, width_ + 2 * kDebugFrameBorder, height_ + 2 * kDebugFrameBorder };
}

DebugFrame::~DebugFrame()
{
    TTF_CloseFont(font_);
    SDL_DestroyTexture(texture_);
}


void DebugFrame::render()
{
    // Draw background rectangle
    SDL_SetRenderDrawColor(renderer_->renderer(), 20, 20, 20, 200);
    SDL_RenderFillRect(renderer_->renderer(), &background_);

    // Create mouse message surface
    Point mouse = EventManager::mouse_position();
    std::stringstream message;
    message << "Mouse: (" << mouse.x_position() << "," << mouse.y_position() << ")";
    SDL_Surface * surface = TTF_RenderText_Solid(font_, message.str().c_str(), fg_color_);
    if(surface == nullptr) {
        Logger::write(Logger::ss << "Text Error: " << TTF_GetError());
    }

    Logger::write(Logger::ss << "Text Surface:\n"
            << "\t\t\t\t\t\t" << "w: " << surface->format << "\n"
            << "\t\t\t\t\t\t" << "h: " << surface->format << "\n"
            << "\t\t\t\t\t\t" << "pitch: " << surface->format << "\n"
            << "\t\t\t\t" << "pixelformat: \n"
            << "\t\t\t\t\t\t" << "BytesPerPixel: " << surface->format->BytesPerPixel << "\n"
            << "\t\t\t\t\t\t" << "Rmask: " << surface->format->Rmask << "\n"
            << "\t\t\t\t\t\t" << "Gmask: " << surface->format->Gmask << "\n"
            << "\t\t\t\t\t\t" << "Bmask: " << surface->format->Bmask << "\n"
            << "\t\t\t\t\t\t" << "Amask: " << surface->format->Amask << "\n"
    );


    // Render debug frame
    SDL_Rect offset = { x_position_, y_position_, surface->w, surface->h };
    texture_ = SDL_CreateTextureFromSurface(renderer_->renderer(), surface);
    if(texture_ == nullptr) {
        Logger::write(Logger::ss << "DebugFrame Texture: " << SDL_GetError());
    }
    else {
        renderer_->render_texture(texture_, &offset, nullptr);
    }

    SDL_FreeSurface(surface);
}

bool DebugFrame::toggle()
{
    shown_ = !shown_;
    return shown_;
}

*/
