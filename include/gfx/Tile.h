#ifndef TLB_TILE_H_
#define TLB_TILE_H_

#include "SDL2/SDL.h"
#include "Point.h"
#include "math/Vector3f.h"
#include "gfx/Model.h"

class Level;
class Tileset;
class Frame;

class Tile
{
    private:
        Vector3f position_;
        float width_;
        float length_;
        float height_;
        int row_;
        int column_;
        int type_;
        Tileset * tileset_;

        Model model_;

        void loadModelData();

    public:
        Tile();
        Tile(Point point, float width, float height, int type);
        Vector3f position() const { return position_; }
        float width() const { return width_; }
        float length() const { return length_; }
        float height() const { return height_; }
        int row() const { return row_; }
        int column() const { return column_; }
        int type() const { return type_; }
        Tileset * tileset() const { return tileset_; }

        void render();

        void setPosition(Vector3f position);
        void setColor(Vector4f color);
        void setWidth(float width);
        void setLength(float length);
        void setHeight(float height);
        void setType(int type_);

        void setTileset(Tileset * tileset) { tileset_ = tileset; }

};

#endif
