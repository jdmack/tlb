#include "GL/glew.h"
#include "gfx/lighting/DirectionalLight.h"
#include "Game.h"
#include "gfx/Renderer.h"
#include "gfx/Shader.h"
#include "util/Logger.h"

DirectionalLight::DirectionalLight()
{
    //direction_ = Vector3f(1.0, 1.0, 0.0);
    direction_ = Vector3f(0.0, 0.0, -1.0);
}

DirectionalLight::DirectionalLight(Vector3f color, float ambientIntensity, float diffuseIntensity, Vector3f direction)
    : Light(color, ambientIntensity, diffuseIntensity)
{
    direction_ = direction;
}

bool DirectionalLight::init()
{
    Shader * shader = Game::instance()->renderer()->textureShader();

    colorLoc_ = shader->getUniformLocation("f_DirectionalLight.color");
    if(colorLoc_ == -1) {
        Logger::write(Logger::ss << "f_DirectionalLight.color is not a valid glsl program variable!");
    }

    ambientIntensityLoc_ = shader->getUniformLocation("f_DirectionalLight.ambientIntensity");
    if(ambientIntensityLoc_ == -1) {
        Logger::write(Logger::ss << "f_DirectionalLight.ambientIntensity is not a valid glsl program variable!");
    }

    diffuseIntensityLoc_ = shader->getUniformLocation("f_DirectionalLight.diffuseIntensity");
    if(diffuseIntensityLoc_ == -1) {
        Logger::write(Logger::ss << "f_DirectionalLight.diffuseIntensity is not a valid glsl program variable!");
    }

    directionLoc_ = shader->getUniformLocation("f_DirectionalLight.direction");
    if(directionLoc_ == -1) {
        Logger::write(Logger::ss << "f_DirectionalLight.direction is not a valid glsl program variable!");
    }
    
    update();

    return true;
}

void DirectionalLight::update()
{
    Light::update();    

    Shader * shader = Game::instance()->renderer()->textureShader();
    shader->enable();
    
    glUniform3f(directionLoc_, direction_.x(), direction_.y(), direction_.z());

    shader->disable();
}
