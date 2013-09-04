#ifndef TLB_DEBUG_FRAME_H_
#define TLB_DEBUG_FRAME_H_

#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#include "constants.h"
#include "screen.h"

const int kDebugFrameWidth = 200;
const int kDebugFrameHeight = 50;
const int kDebugFrameXPosition = kScreenWidth - kDebugFrameWidth;
const int kDebugFrameYPosition = kScreenHeight - kDebugFrameHeight;
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

        TTF_Font * font_;
        SDL_Texture * texture_;
        SDL_Rect background_;
        Screen * screen_;


    public:
        DebugFrame(Screen * screen);
        ~DebugFrame();

        // accessors
        bool shown() const { return shown_; }

        void draw();
        bool toggle();
};

#endif
