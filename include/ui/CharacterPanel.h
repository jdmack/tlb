#ifndef TLB_UI_CHARACTER_PANEL_H_
#define TLB_UI_CHARACTER_PANEL_H_

#include "ui/UIElement.h"
#include "Point.h"

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

        SDL_Texture * selectedTexture_;


    public:
        CharacterPanel();
        ~CharacterPanel();

        // accessors
        Frame * frame() { return frame_; }
        Entity * entity() { return entity_; }

        // mutators
        void setFrame(Frame * frame) { frame_ =  frame; }
        void setEntity(Entity * entity) { entity_ = entity; }


        void render(Frame * frame = nullptr);
        void update();
        bool click(Point point);

};

#endif
