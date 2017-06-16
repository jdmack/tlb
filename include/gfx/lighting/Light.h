#ifndef TLB_GFX_LIGHTING_LIGHT_H_
#define TLB_GFX_LIGHTING_LIGHT_H_

#include "math/Vector3f.h"
#include "math/Matrix4f.h"

/*
struct Light
{
    Vector3f color;
    float ambientIntensity;
    float diffuseIntensity;
};
*/

class Light
{
    public:
        Light();
        Light(Vector3f color, float ambientIntensity, float diffuseIntensity);
        ~Light();

        // accessors
        Vector3f color() { return color_; }
        float ambientIntensity() { return ambientIntensity_; }
        float diffuseIntensity() { return diffuseIntensity_; }

        // mutators
        void setColor(Vector3f color) { color_ = color; }
        void setAmbientIntensity(float ambientIntensity) { ambientIntensity_ = ambientIntensity; } 
        void setDiffuseIntensity(float diffuseIntensity) { diffuseIntensity_ = diffuseIntensity; } 

        virtual bool init() = 0;
        virtual void update();

    protected:
        Vector3f color_;
        float ambientIntensity_;
        float diffuseIntensity_;

        GLuint colorLoc_;
        GLuint ambientIntensityLoc_;
        GLuint diffuseIntensityLoc_;
};

#endif

