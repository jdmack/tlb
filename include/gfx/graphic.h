#ifndef TLB_GFX_GRAPHIC_H_
#define TLB_GFX_GRAPHIC_H_

#include "SDL2/SDL.h"
#include "constants.h"
#include "gfx/renderer.h"
#include "point.h"

class Frame;

class Graphic
{
    protected:
        Point position_;
        int width_;                 // auto-populated
        int height_;                // auto-populated
        bool visible_;
        std::string artAsset_;

        SDL_Texture * texture_;


    public:
        Graphic();
        virtual ~Graphic();

        // accessors
        Point position() const { return position_; }
        int width() const { return width_; }
        int height() const { return height_; }
        bool visible() const { return visible_; }
        std::string artAsset() const { return artAsset_; }

        // mutators
        void setPosition(Point position) { position_ = position; }
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
