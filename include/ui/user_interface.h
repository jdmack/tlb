#ifndef TLB_UI_USER_INTERFACE_H_
#define TLB_UI_USER_INTERFACE_H_

#include <vector>
#include "SDL2/SDL.h"

class Frame;
class UIElement;
class TextPanel;
class CharacterPanel;

class UserInterface
{
    private:
        std::vector<UIElement *> elements_;
        TextPanel * paused_panel_;
        CharacterPanel * character_panel_[4];

    public:
        UserInterface();
        ~UserInterface();

        // accessors
        std::vector<UIElement *> elements() const { return elements_; }

        // mutators

        void add_element(UIElement * element);        

        void render(Frame * frame = nullptr);
        void update();
        bool click(Point point);

};

#endif
