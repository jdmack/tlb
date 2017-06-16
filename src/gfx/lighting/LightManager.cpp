#include "GL/glew.h"
#include "gfx/lighting/LightManager.h"
#include "gfx/lighting/DirectionalLight.h"
#include "gfx/lighting/PointLight.h"
#include "gfx/lighting/SpotLight.h"
#include "Game.h"
#include "gfx/Renderer.h"
#include "gfx/Shader.h"
#include "util/Logger.h"

LightManager::LightManager()
{
    numDirectionalLights_ = 0;
    numPointLights_ = 0;
    numSpotLights_ = 0;

    numDirectionalLightsLoc_ = -1;
    numPointLightsLoc_ = -1;
    numSpotLightsLoc_ = -1;

    directionalLight_ = nullptr;

    for(std::array<PointLight *, kMaxPointLights>::iterator it = pointLights_.begin(); it != pointLights_.end(); ++it) {
        *it = nullptr;
    }

    for(std::array<SpotLight *, kMaxSpotLights>::iterator it = spotLights_.begin(); it != spotLights_.end(); ++it) {
        *it = nullptr;
    }
}

bool LightManager::init()
{
    Shader * shader = Game::instance()->renderer()->textureShader();

    numDirectionalLightsLoc_ = shader->getUniformLocation("f_NumDirectionalLights");
    if(numDirectionalLightsLoc_ == -1) {
        Logger::write(Logger::ss << "f_NumDirectionalLights is not a valid glsl program variable!");
    }

    numPointLightsLoc_ = shader->getUniformLocation("f_NumPointLights");
    if(numPointLightsLoc_ == -1) {
        Logger::write(Logger::ss << "f_NumPointLights is not a valid glsl program variable!");
    }

    numSpotLightsLoc_ = shader->getUniformLocation("f_NumSpotLights");
    if(numSpotLightsLoc_ == -1) {
        Logger::write(Logger::ss << "f_NumSpotLights is not a valid glsl program variable!");
    }

    update();
}

void LightManager::update()
{
    Shader * shader = Game::instance()->renderer()->textureShader();
    shader->enable();
    
    glUniform1i(numDirectionalLightsLoc_, numDirectionalLights_);
    glUniform1i(numPointLightsLoc_, numPointLights_);
    glUniform1i(numSpotLightsLoc_, numSpotLights_);

    shader->disable();
}

bool LightManager::createDirectionalLight()
{
    if(numDirectionalLights_ >= kMaxDirectionalLights) {
        return false;
    }

    ++numDirectionalLights_;
    directionalLight_ = new DirectionalLight();

    return true;
}

bool LightManager::createDirectionalLight(Vector3f color, float ambientIntensity, float diffuseIntensity, Vector3f direction)
{
    if(numDirectionalLights_ >= kMaxDirectionalLights) {
        return false;
    }

    ++numDirectionalLights_;
    directionalLight_ = new DirectionalLight(color, ambientIntensity, diffuseIntensity, direction);

    return true;

}

bool LightManager::createPointLight()
{
    if(numPointLights_ >= kMaxPointLights) {
        return false;
    }
    
    ++numPointLights_;
    pointLights_[numPointLights_ - 1] = new PointLight();
    update();
    
    return true;
}

bool LightManager::createPointLight(Vector3f color, float ambientIntensity, float diffuseIntensity, Vector3f position,
    float attenConstant, float attenLinear, float attenExp)
{
    if(numPointLights_ >= kMaxPointLights) {
        return false;
    }
    
    ++numPointLights_;
    pointLights_[numPointLights_ - 1] = new PointLight(color, ambientIntensity, diffuseIntensity, position,
        attenConstant, attenLinear, attenExp);
    update();
    
    return true;

}

bool LightManager::createSpotLight()
{
    if(numSpotLights_ >= kMaxSpotLights) {
        return false;
    }
    
    ++numSpotLights_;
    spotLights_[numSpotLights_ - 1] = new SpotLight();
    update();
    
    return true;

}

bool LightManager::createSpotLight(Vector3f color, float ambientIntensity, float diffuseIntensity, Vector3f position,
    float attenConstant, float attenLinear, float attenExp, Vector3f direction, float cutoff)
{
    if(numSpotLights_ >= kMaxSpotLights) {
        return false;
    }
    
    ++numSpotLights_;
    spotLights_[numSpotLights_ - 1] = new SpotLight(color, ambientIntensity, diffuseIntensity, position,
        attenConstant, attenLinear, attenExp, direction, cutoff);
    update();
    
    return true;
}



