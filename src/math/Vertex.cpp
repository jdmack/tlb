#include "math/Vertex.h"


Vertex::Vertex()
{
    position_ = Vector3f(0.0, 0.0, 0.0);
    tex_ = Vector2f(0.0, 0.0);
    normal_ = Vector3f(0.0, 0.0, 0.0);
    specularIntensity_ = 1.0f;
    specularPower_ = 32;
}

Vertex::Vertex(Vector3f position, Vector2f tex)
{
    position_ = position;
    tex_ = tex;
    normal_ = Vector3f(0.0, 0.0, 0.0);
    specularIntensity_ = 1.0f;
    specularPower_ = 32;
}
