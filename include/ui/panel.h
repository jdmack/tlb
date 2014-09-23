#ifndef TLB_UI_PANEL_H_
#define TLB_UI_PANEL_H_

#include "SDL2/SDL.h"
#include <vector>
#include "constants.h"
#include "renderer.h"
#include "point.h"
#include "ui/ui_element.h"

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
        void set_position(Point point);
        void set_frame(Frame * frame) { frame_ = frame; }

        void add_element(UIElement * element);

        void render(Frame * frame = nullptr);
        void update();
        bool load_texture(std::string art_asset);
};

#endif
