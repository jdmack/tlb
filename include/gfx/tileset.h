#ifndef TLB_TILESET_H_
#define TLB_TILESET_H_

#include "SDL2/SDL.h"
#include "point.h"
#include <vector>
#include <map>

class Level;

class Tileset
{
    private:
        double width_;
        double height_;
        //SDL_Rect clips_[kTileSprites];
        SDL_Texture * texture_;
        std::map<int, SDL_Rect> clips_;

    public:
        Tileset();
        Tileset(std::string filename);

        double width() const { return width_; }
        double height() const { return height_; }
        SDL_Texture * texture() const { return texture_; }

        SDL_Rect clips(int type) { return clips_[type]; }

        void setWidth(double width) { width_ = width; }
        void setHeight(double height) { height_ = height; }

        bool load(std::string filename);

};

#endif
