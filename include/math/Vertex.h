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
        float specularIntensity_;
        float specularPower_;

        Vertex();
        Vertex(Vector3f position, Vector2f tex);

        // accessors
        Vector3f & position() { return position_; }
        Vector2f tex() { return tex_; }
        Vector3f & normal() { return normal_; }
        //float specularIntensity() { return specularIntensity_; }
        //float specularPower() { return specularPower_; }

        // mutators
        void setPosition(Vector3f position) { position_ = position; }
        void setTex(Vector2f tex) { tex_ = tex; }
        void setNormal(Vector3f normal) { normal_ = normal; }
        //void setSpecularIntensity(float specularIntensity) { specularIntensity_ = specularIntensity; }
        //void setSpecularPower(float specularPower) { specularPower_ = specularPower; }

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

