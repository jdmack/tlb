#ifndef TLB_GFX_LIGHTING_DIRECTIONAL_LIGHT_H_
#define TLB_GFX_LIGHTING_DIRECTIONAL_LIGHT_H_

#include "gfx/lighting/Light.h"
#include "math/Vector3f.h"
#include "math/Matrix4f.h"

class DirectionalLight : public Light
{
    public:
        DirectionalLight();
        DirectionalLight(Vector3f color, float ambientIntensity, float diffuseIntensity, Vector3f direction);

        // accessors
        Vector3f direction() { return direction_; }

        // mutators
        void setDirection(Vector3f direction) { direction_ = direction; }

        bool init();
        void update();

    private:
        Vector3f direction_;

        GLuint directionLoc_;
};

#endif

