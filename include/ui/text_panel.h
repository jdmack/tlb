#ifndef TLB_UI_TEXT_PANEL_H_
#define TLB_UI_TEXT_PANEL_H_

#include "SDL2/SDL.h"
#include <vector>
#include "constants.h"
#include "gfx/renderer.h"
#include "point.h"
#include "ui/ui_element.h"

class Frame;
class Text;

class TextPanel : public UIElement
{
    private:
        Text * text_;

    public:
        TextPanel();
        ~TextPanel();

        // accessors
        Text * text() { return text_; }

        // mutators
        void set_text(Text * text) { text_ = text; }

        void render(Frame * frame = nullptr);
        void update();
};

#endif
