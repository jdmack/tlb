#ifndef TLB_MATH_VERTEX_H_
#define TLB_MATH_VERTEX_H_

#include "math/Vector3f.h"
#include "math/Vector2f.h"

class Vertex
{
    public:
        Vector3f position_;
        Vector2f tex_;
        Vector3f normal_;

        Vertex();
        Vertex(Vector3f position, Vector2f tex);

        // accessors
        Vector3f & position() { return position_; }
        Vector2f tex() { return tex_; }
        Vector3f & normal() { return normal_; }

        // mutators
        void setPosition(Vector3f position) { position_ = position; }
        void setTex(Vector2f tex) { tex_ = tex; }
        void setNormal(Vector3f normal) { normal_ = normal; }

};
/*
struct Vertex
{
    float x_;
    float y_;
    float z_;
    float s_;
    float t_;

    Vertex() {}
    Vertex(float x, float y, float z, float s, float t)
    {
        x_ = x;
        y_ = x;
        z_ = z;
        s_ = s;
        t_ = t;
    }


};
*/
#endif

