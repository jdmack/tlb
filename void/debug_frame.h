/*
#ifndef TLB_DEBUG_FRAME_H_
#define TLB_DEBUG_FRAME_H_

#include "SDL2/SDL.h"
#include "constants.h"
#include "gfx/renderer.h"

const int kDebugFrameWidth = 200;
const int kDebugFrameHeight = 50;
const int kDebugFrameXPosition = kRendererWidth - kDebugFrameWidth;
const int kDebugFrameYPosition = kRendererHeight - kDebugFrameHeight;
const int kDebugFrameFontSize = 12;
const int kDebugFrameBorder = 5;

class DebugFrame
{
    private:
        int x_position_;
        int y_position_;
        int width_;
        int height_;
        bool shown_;
        SDL_Color fg_color_;

        //TTF_Font * font_;
        SDL_Texture * texture_;
        SDL_Rect background_;
        Renderer * renderer_;


    public:
        DebugFrame(Renderer * renderer);
        ~DebugFrame();

        // accessors
        bool shown() const { return shown_; }

        void render();
        bool toggle();
};

#endif
*/
