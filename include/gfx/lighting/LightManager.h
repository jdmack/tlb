#ifndef TLB_GFX_LIGHTING_LIGHT_MANAGER_H_
#define TLB_GFX_LIGHTING_LIGHT_MANAGER_H_

#include <array>
#include "math/Vector3f.h"

const int kMaxDirectionalLights = 1;
const int kMaxPointLights = 2;
const int kMaxSpotLights = 2;

class DirectionalLight;
class PointLight;
class SpotLight;

class LightManager
{
    public:
        LightManager();

        // accessors

        // mutators

        bool init();
        void update();

        bool createDirectionalLight();
        bool createDirectionalLight(Vector3f color, float ambientIntensity, float diffuseIntensity, Vector3f direction);

        bool createPointLight();
        bool createPointLight(Vector3f color, float ambientIntensity, float diffuseIntensity, Vector3f position,
            float attenConstant, float attenLinear, float attenExp);

        bool createSpotLight();
        bool createSpotLight(Vector3f color, float ambientIntensity, float diffuseIntensity, Vector3f position,
            float attenConstant, float attenLinear, float attenExp, Vector3f direction, float cutoff);


    private:
        int numDirectionalLights_;
        int numPointLights_;
        int numSpotLights_;

        GLuint numDirectionalLightsLoc_;
        GLuint numPointLightsLoc_;
        GLuint numSpotLightsLoc_;

        DirectionalLight * directionalLight_;
        std::array<PointLight *, kMaxPointLights> pointLights_;
        std::array<SpotLight *, kMaxSpotLights> spotLights_;

};

#endif

