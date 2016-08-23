#include "gfx/Ray.h"

Ray::Ray()
{
}

Ray::Ray(Vector3f direction, Vector3f origin)
{
    direction_ = direction;
    origin_ = origin;
    loadModelData();
    model_.setMode(DRAW_LINES);
}

void Ray::loadModelData()
{
    /*
    Vector3f vertices[2];
    vertices[0] = origin_;
    vertices[1] = (direction_ * 100) + origin_;

    int indices[] = { 0, 1 };

    model_.loadVertices(vertices, sizeof(vertices));
    model_.loadIndices(indices, sizeof(indices));
    */
}

void Ray::setDirection(Vector3f direction)
{
    direction_ = direction;
    update();
}

void Ray::setOrigin(Vector3f origin)
{
    origin_ = origin;
    update();
}

void Ray::setColor(Vector4f color)
{
    color_ = color;
    model_.setColor(color_);
}

void Ray::update()
{
    loadModelData();
}

void Ray::render()
{
    model_.render();
}
