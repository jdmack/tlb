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

    loadModelData();
}

Tile::Tile(Point position, float width, float length, int type)
{
    setPosition(Vector3f(position.x(), 0.0, position.y()));
    setWidth(width);
    setLength(length);
    setHeight(0.25);
    setType(type);

    row_ = position_.y() / width_;
    column_ = position_.x() / length_;
    tileset_ = nullptr;

    loadModelData();
}

void Tile::loadModelData()
{
    // VBO data
    Vector3f vertices[8];
    vertices[0] = Vector3f(-0.5f, 0.0f, -0.5f);
    vertices[1] = Vector3f(0.5f, 0.0f, -0.5f);
    vertices[2] = Vector3f(-0.5f, 0.0f, 0.5f);
    vertices[3] = Vector3f(0.5f, 0.0f, 0.5f);
    vertices[4] = Vector3f(-0.5f, 0.5f, -0.5f);
    vertices[5] = Vector3f(0.5f, 0.5f, -0.5f);
    vertices[6] = Vector3f(-0.5f, 0.5f, 0.5f);
    vertices[7] = Vector3f(0.5f, 0.5f, 0.5f);

    // IBO data
    int indices[] = { 4, 6, 7,   // 1a
                         4, 7, 5,   // 1b
                         0, 2, 3,   // 2a
                         0, 3, 1,   // 2b
                         0, 4, 5,   // 3a
                         0, 5, 1,   // 3b
                         0, 4, 6,   // 4a
                         0, 6, 2,   // 4b
                         1, 5, 7,   // 5a
                         1, 7, 3,   // 5b
                         2, 6, 7,   // 6a
                         2, 7, 3 }; // 6b

    model_.loadVertices(vertices, sizeof(vertices));
    model_.loadIndices(indices, sizeof(indices));
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
    model_.transform().translate(position_);
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

void Tile::setColor(Vector4f color)
{
    model_.setColor(color);
}
