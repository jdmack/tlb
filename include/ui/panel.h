#ifndef TLB_UI_PANEL_H_
#define TLB_UI_PANEL_H_

#include "SDL2/SDL.h"
#include "constants.h"
#include "renderer.h"
#include "point.h"

class Panel : public UIElement
{
    private:

    public:
        Panel();
        ~Panel();

        // accessors

        // mutators

        void render(Frame * frame = nullptr);
        void update();
};

#endif
