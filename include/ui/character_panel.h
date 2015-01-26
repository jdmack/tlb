#ifndef TLB_UI_CHARACTER_PANEL_H_
#define TLB_UI_CHARACTER_PANEL_H_

#include "ui/ui_element.h"
#include "point.h"

class Frame;
class Entity;
class TextPanel;

class CharacterPanel : public UIElement
{
    private:
        Frame * frame_;
        Entity * entity_;
        UIElement * portrait_;
        TextPanel * name_;
        TextPanel * role_;

        SDL_Texture * selected_texture_;


    public:
        CharacterPanel();
        ~CharacterPanel();

        // accessors
        Frame * frame() { return frame_; }
        Entity * entity() { return entity_; }

        // mutators
        void set_frame(Frame * frame) { frame_ =  frame; }
        void set_entity(Entity * entity) { entity_ = entity; }


        void render(Frame * frame = nullptr);
        void update();
        bool click(Point point);

};

#endif
