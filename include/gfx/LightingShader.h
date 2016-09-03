#ifndef TLB_GFX_LIGHTING_SHADER_H_
#define TLB_GFX_LIGHTING_SHADER_H_

#include "gfx/Shader.h"
#include "math/Vector3f.h"
#include "math/Matrix4f.h"

struct DirectionalLight
{
    Vector3f color;
    float ambientIntensity;
};

class LightingShader : public Shader
{
    public:
        LightingShader();
        LightingShader(const char* vertexFilename, const char* fragmentFilename);

        virtual bool init();

        void setWorld(const Matrix4f & world);
        void setTextureUnit(unsigned int textureUnit);
        void setDirectionalLight(const DirectionalLight & light);

    private:
        GLuint worldLoc_;
        GLuint samplerLoc_;
        GLuint dirLightColorLoc_;
        GLuint dirLightAmbientIntensityLoc_;

        void collectUniforms();
};

#endif

