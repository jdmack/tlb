#include "GL/glew.h"
#include "gfx/Light.h"
#include "Game.h"
#include "gfx/Renderer.h"
#include "gfx/Shader.h"
#include "util/Logger.h"

Light::Light()
{
    color_ = Vector3f(1.0, 1.0, 1.0);
    ambientIntensity_ = 0.3;
    direction_ = Vector3f(1.0, 1.0, 0.0);
    diffuseIntensity_ = 0.8;

    update();
}

Light::Light(Vector3f color, float ambientIntensity, Vector3f direction, float diffuseIntensity)
{
    color_ = color;
    ambientIntensity_ = ambientIntensity;
    direction_ = direction;
    diffuseIntensity_ = diffuseIntensity;

    update();
}

bool Light::init()
{
    Shader * shader = Game::instance()->renderer()->textureShader();

    dirLightColorLoc_ = shader->getUniformLocation("f_DirectionalLight.color");
    if(dirLightColorLoc_ == -1) {
        Logger::write(Logger::ss << "f_DirectionalLight.color is not a valid glsl program variable!");
    }

    dirLightAmbientIntensityLoc_ = shader->getUniformLocation("f_DirectionalLight.ambientIntensity");
    if(dirLightAmbientIntensityLoc_ == -1) {
        Logger::write(Logger::ss << "f_DirectionalLight.ambientIntensity is not a valid glsl program variable!");
    }

    dirLightDirectionLoc_ = shader->getUniformLocation("f_DirectionalLight.direction");
    if(dirLightDirectionLoc_ == -1) {
        Logger::write(Logger::ss << "f_DirectionalLight.direction is not a valid glsl program variable!");
    }

    dirLightDiffuseIntensityLoc_ = shader->getUniformLocation("f_DirectionalLight.diffuseIntensity");
    if(dirLightDiffuseIntensityLoc_ == -1) {
        Logger::write(Logger::ss << "f_DirectionalLight.diffuseIntensity is not a valid glsl program variable!");
    }

    return true;
}

void Light::update()
{
    directionalLight_.color = color_;
    directionalLight_.ambientIntensity = ambientIntensity_;
    directionalLight_.direction = direction_;
    directionalLight_.diffuseIntensity = diffuseIntensity_;
    
    Shader * shader = Game::instance()->renderer()->textureShader();
    shader->enable();
    
    //glUniform3fv(dirLightColorLoc_, 1, directionalLight_.color.pointer());
    glUniform3f(dirLightColorLoc_, directionalLight_.color.x(), directionalLight_.color.y(), directionalLight_.color.z());
    glUniform1f(dirLightAmbientIntensityLoc_, directionalLight_.ambientIntensity);
    glUniform3f(dirLightDirectionLoc_, directionalLight_.direction.x(), directionalLight_.direction.y(), directionalLight_.direction.z());
    glUniform1f(dirLightDiffuseIntensityLoc_, directionalLight_.diffuseIntensity);
    //glUniform1f(dirLightAmbientIntensityLoc_, ambientIntensity_);
    shader->disable();
}
