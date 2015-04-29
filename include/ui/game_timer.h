#ifndef TLB_UI_GAME_TIMER_H_
#define TLB_UI_GAME_TIMER_H_

#include "SDL2/SDL.h"
#include <vector>
#include "constants.h"
#include "gfx/renderer.h"
#include "point.h"
#include "ui/ui_element.h"

class Frame;
class Text;

class GameTimer : public UIElement
{
    private:
        int start_ticks_;
        Text * text_;

    public:
        GameTimer();
        ~GameTimer();

        // accessors

        // mutators


        void render(Frame * frame = nullptr);
        void update();

        std::string convert_time(int ticks);
};

#endif
