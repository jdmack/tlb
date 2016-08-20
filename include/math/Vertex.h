#ifndef TLB_MATH_VERTEX_H_
#define TLB_MATH_VERTEX_H_

#include "math/Vector3f.h"
#include "math/Vector2f.h"

class Vertex
{
    public:
        Vector3f position_;
        Vector2f tex_;

        Vertex(Vector3f position, Vector2f tex);
}

#endif

