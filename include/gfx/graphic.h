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
        std::string art_asset_;

        SDL_Texture * texture_;


    public:
        Graphic();
        virtual ~Graphic();

        // accessors
        Point position() const { return position_; }
        int width() const { return width_; }
        int height() const { return height_; }
        bool visible() const { return visible_; }
        std::string art_asset() const { return art_asset_; }

        // mutators
        void set_position(Point position) { position_ = position; }
        void set_width(int width) { width_ = width; }
        void set_height(int height) { height_ = height; }
        void set_visible(bool visible) { visible_ = visible; }
        void set_art_asset(std::string art_asset) { art_asset_ = art_asset; }

        virtual void render(Frame * frame = nullptr);
        virtual void update();
        virtual bool toggle();
        virtual bool click(Point point);
        bool contains_point(Point point);

        virtual bool load_texture(std::string art_asset);
};

#endif
