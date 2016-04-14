#ifndef TLB_UI_USER_INTERFACE_H_
#define TLB_UI_USER_INTERFACE_H_

#include <vector>
#include "SDL2/SDL.h"
#include "Point.h"

class Frame;
class UIElement;
class TextPanel;
class CharacterPanel;

class UserInterface
{
    private:
        std::vector<UIElement *> elements_;
        TextPanel * pausedPanel_;
        CharacterPanel * characterPanel_[4];

    public:
        UserInterface();
        ~UserInterface();

        // accessors
        std::vector<UIElement *> elements() const { return elements_; }
        CharacterPanel * characterPanel(int index) { return characterPanel_[index]; }

        // mutators

        void addElement(UIElement * element);        

        void render(Frame * frame = nullptr);
        void update();
        bool click(Point point);

        bool containsPoint(Point point);
};

#endif
