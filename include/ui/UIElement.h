#ifndef TLB_UI_UI_ELEMENT_H_
#define TLB_UI_UI_ELEMENT_H_

#include "SDL2/SDL.h"
#include "Constants.h"
#include "gfx/Renderer.h"
#include "Point.h"

class Frame;

class UIElement
{
    protected:
        Point position_;
        int width_;
        int height_;
        bool visible_;
        std::string artAsset_;

        SDL_Texture * texture_;


    public:
        UIElement();
        virtual ~UIElement();

        // accessors
        Point position() const { return position_; }
        int width() const { return width_; }
        int height() const { return height_; }
        bool visible() const { return visible_; }
        std::string artAsset() const { return artAsset_; }

        // mutators
        virtual void setPosition(Point position) { position_ = position; }
        void setWidth(int width) { width_ = width; }
        void setHeight(int height) { height_ = height; }
        void setVisible(bool visible) { visible_ = visible; }
        void setArtAsset(std::string artAsset) { artAsset_ = artAsset; }

        virtual void render(Frame * frame = nullptr);
        virtual void update();
        virtual bool toggle();
        virtual bool click(Point point);
        bool containsPoint(Point point);

        virtual bool loadTexture(std::string artAsset);
};

#endif
