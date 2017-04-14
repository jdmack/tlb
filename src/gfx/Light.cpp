#include "GL/glew.h"
#include "gfx/Light.h"
#include "Game.h"
#include "gfx/Renderer.h"
#include "gfx/Shader.h"
#include "util/Logger.h"

Light::Light()
{
    color_ = Vector3f(1.0, 1.0, 1.0);
    ambientIntensity_ = 1.0;

    update();
}

Light::Light(Vector3f color, float ambientIntensity)
{
    color_ = color;
    ambientIntensity_ = ambientIntensity;

    update();
}

bool Light::init()
{
    Shader * shader = Game::instance()->renderer()->textureShader();

    dirLightColorLoc_ = shader->getUniformLocation("directionalLight.color");
    if(dirLightColorLoc_ == -1) {
        Logger::write(Logger::ss << "directionalLight.color is not a valid glsl program variable!");
    }

    dirLightAmbientIntensityLoc_ = shader->getUniformLocation("directionalLight.ambientIntensity");
    if(dirLightAmbientIntensityLoc_ == -1) {
        Logger::write(Logger::ss << "directionalLight.ambientIntensity is not a valid glsl program variable!");
    }

    return true;
}

void Light::update()
{
    directionalLight_.color = color_;
    directionalLight_.ambientIntensity = ambientIntensity_;
    
    Shader * shader = Game::instance()->renderer()->textureShader();
    shader->enable();
    
    //glUniform3fv(dirLightColorLoc_, 1, directionalLight_.color.pointer());
    glUniform3f(dirLightColorLoc_, directionalLight_.color.x(), directionalLight_.color.y(), directionalLight_.color.z());
    glUniform1f(dirLightAmbientIntensityLoc_, directionalLight_.ambientIntensity);
    //glUniform1f(dirLightAmbientIntensityLoc_, ambientIntensity_);
    shader->disable();
}
