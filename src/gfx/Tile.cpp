#include "gfx/Tile.h"
#include "Level.h"
#include "gfx/Camera.h"
#include "gfx/Renderer.h"
#include "Game.h"
#include "Point.h"
#include "gfx/Tileset.h"
#include "Frame.h"
#include "math/Vector4f.h"

Tile::Tile()
{
    position_ = Vector3f(0.0, 0.0, 0.0);
    width_ = 1;
    length_ = 1;
    height_ = 1;
    type_ = 0;

    row_ = -1;
    column_ = -1;
    tileset_ = nullptr;
}

Tile::Tile(Point position, float width, float length, int type)
{
    setPosition(Vector3f(position.x(), 0.0, position.y()));
    setWidth(width);
    setLength(length);
    setHeight(0.25);
    setType(type_);

    row_ = position_.y() / width_;
    column_ = position_.x() / length_;
    tileset_ = nullptr;
}

void Tile::render()
{
    model_.render();
}

////////////////////////////////////////////////////////////////////////////////
// Setters
////////////////////////////////////////////////////////////////////////////////
void Tile::setPosition(Vector3f position)
{
    position_ = position;
    model_.transform().worldPos(position_);
}

void Tile::setWidth(float width)
{
    width_ = width;
    model_.transform().scale(0, width_);
}

void Tile::setLength(float length)
{
    length_ = length;
    model_.transform().scale(2, length_);
}

void Tile::setHeight(float height)
{
    height_ = height;
    model_.transform().scale(1, height_);
}

void Tile::setType(int type)
{
    type_ = type;
    Vector4f color;

    switch(type_) {
        case 0:
            color = Vector4f(1.0, 0.0, 0.0, 1.0);
            break;
        case 1:
            color = Vector4f(0.0, 1.0, 0.0, 1.0);
            break;
        case 2:
            color = Vector4f(0.0, 0.0, 1.0, 1.0);
            break;
        default: 
            color = Vector4f(0.5, 0.5, 0.5, 1.0);
    }
    model_.setColor(color);

}
