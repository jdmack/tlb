#ifndef TLB_UI_TEXT_PANEL_H_
#define TLB_UI_TEXT_PANEL_H_

#include "SDL2/SDL.h"
#include <vector>
#include "Constants.h"
#include "gfx/Renderer.h"
#include "Point.h"
#include "ui/UIElement.h"

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
        void setText(Text * text) { text_ = text; }

        void render(Frame * frame = nullptr);
        void update();
};

#endif
