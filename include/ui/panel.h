#ifndef TLB_UI_PANEL_H_
#define TLB_UI_PANEL_H_

#include "SDL2/SDL.h"
#include <vector>
#include "constants.h"
#include "gfx/renderer.h"
#include "point.h"
#include "ui/uiElement.h"

class Frame;

class Panel : public UIElement
{
    private:
        std::vector<UIElement *> elements_;
        Frame * frame_;

    public:
        Panel();
        ~Panel();

        // accessors
        std::vector<UIElement *> elements() const { return elements_; }
        Frame * frame() const { return frame_; }

        // mutators
        void setPosition(Point point);
        void setFrame(Frame * frame) { frame_ = frame; }

        void addElement(UIElement * element);

        void render(Frame * frame = nullptr);
        void update();
        bool loadTexture(std::string artAsset);
};

#endif
