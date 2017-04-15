#ifndef TLB_GFX_LIGHT_H_
#define TLB_GFX_LIGHT_H_

#include "math/Vector3f.h"
#include "math/Matrix4f.h"

struct DirectionalLight
{
    Vector3f color;
    float ambientIntensity;
    Vector3f direction;
    float diffuseIntensity;
};

class Light
{
    public:
        Light();
        Light(Vector3f color, float ambientIntensity, Vector3f direction, float diffuseIntensity);

        bool init();

        // accessors
        struct DirectionalLight directionalLight() { return directionalLight_; }
        Vector3f color() { return color_; }
        float ambientIntensity() { return ambientIntensity_; }
        Vector3f direction() { return direction_; }
        float diffuseIntensity() { return diffuseIntensity_; }

        // mutators
        //void setDirectionalLight(DirectionalLight directionalLight) { directionalLight_ = directionalLight; }
        void setColor(Vector3f color) { color_ = color; }
        void setAmbientIntensity(float ambientIntensity) { ambientIntensity_ = ambientIntensity; } 
        void setDirection(Vector3f direction) { direction_ = direction; }
        void setDiffuseIntensity(float diffuseIntensity) { diffuseIntensity_ = diffuseIntensity; } 

        void update();

    private:
        struct DirectionalLight directionalLight_;
        Vector3f color_;
        float ambientIntensity_;
        Vector3f direction_;
        float diffuseIntensity_;

        GLuint dirLightColorLoc_;
        GLuint dirLightAmbientIntensityLoc_;
        GLuint dirLightDirectionLoc_;
        GLuint dirLightDiffuseIntensityLoc_;
};

#endif

