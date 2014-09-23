#ifndef TLB_UI_USER_INTERFACE_H_
#define TLB_UI_USER_INTERFACE_H_

#include <vector>
#include "SDL2/SDL.h"

class Frame;
class UIElement;
class TextPanel;

class UserInterface
{
    private:
        std::vector<UIElement *> elements_;
        TextPanel * paused_panel_;

    public:
        UserInterface();
        ~UserInterface();

        // accessors
        std::vector<UIElement *> elements() const { return elements_; }

        // mutators

        void add_element(UIElement * element);        

        void render(Frame * frame = nullptr);
        void update();
};

#endif
