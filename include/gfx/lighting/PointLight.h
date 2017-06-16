#ifndef TLB_GFX_LIGHTING_POINT_LIGHT_H_
#define TLB_GFX_LIGHTING_POINT_LIGHT_H_

#include "gfx/lighting/Light.h"
#include "math/Vector3f.h"
#include "math/Matrix4f.h"

class PointLight : public Light
{
    public:
        PointLight();
        PointLight(Vector3f color, float ambientIntensity, float diffuseIntensity, Vector3f position,
            float attenConstant, float attenLinear, float attenExp);

        // accessors
        Vector3f position() { return position_; }
        float attenConstant() { return attenConstant_; }
        float attenLinear() { return attenLinear_; }
        float attenExp() { return attenExp_; }
        int lightId() { return lightId_; }

        // mutators
        void setPosition(Vector3f position) { position_ = position; }
        void setAttenConstant(float attenConstant) { attenConstant_ = attenConstant; }
        void setAttenLinear(float attenLinear) { attenLinear_ = attenLinear; }
        void setAttenExp(float attenExp) { attenExp_ = attenExp; }
        void setLightId(int lightId) { lightId_ = lightId; }

        bool init();
        void update();

    protected:
        Vector3f position_;
        float attenConstant_;
        float attenLinear_;
        float attenExp_;

        GLuint positionLoc_;
        GLuint attenConstantLoc_;
        GLuint attenLinearLoc_;
        GLuint attenExpLoc_;

        int lightId_;
};

#endif

