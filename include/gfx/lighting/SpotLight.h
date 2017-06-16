#ifndef TLB_GFX_LIGHTING_SPOT_LIGHT_H_
#define TLB_GFX_LIGHTING_SPOT_LIGHT_H_

#include "gfx/lighting/PointLight.h"
#include "math/Vector3f.h"
#include "math/Matrix4f.h"

class SpotLight : public PointLight
{
    public:
        SpotLight();
        SpotLight(Vector3f color, float ambientIntensity, float diffuseIntensity, Vector3f position,
            float attenConstant, float attenLinear, float attenExp, Vector3f direction, float cutoff);

        // accessors
        Vector3f direction() { return direction_; }
        float cutoff() { return cutoff_; }

        // mutators
        void setDirection(Vector3f direction) { direction_ = direction; }
        void setCutoff(float cutoff) { cutoff_ = cutoff; }

        bool init();
        void update();

    protected:
        Vector3f direction_;
        float cutoff_;

        GLuint directionLoc_;
        GLuint cutoffLoc_;
};

#endif

