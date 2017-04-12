#include "GL/glew.h"
#include "gfx/Light.h"
#include "Game.h"
#include "gfx/Renderer.h"
#include "gfx/Shader.h"
#include "util/Logger.h"

Light::Light()
{

}

bool Light::init()
{
    Shader * shader = Game::instance()->renderer()->textureShader();

    dirLightColorLoc_ = shader->getUniformLocation("DirectionalLight.color");
    if(dirLightColorLoc_ == -1) {
        Logger::write(Logger::ss << "DirectionalLight.color is not a valid glsl program variable!");
    }

    dirLightAmbientIntensityLoc_ = shader->getUniformLocation("DirectionalLight.ambientIntensity");
    if(dirLightAmbientIntensityLoc_ == -1) {
        Logger::write(Logger::ss << "DirectionalLight.ambientIntensity is not a valid glsl program variable!");
    }

    return true;
}
