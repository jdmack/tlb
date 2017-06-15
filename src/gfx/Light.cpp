#include "GL/glew.h"
#include "gfx/Light.h"
#include "Game.h"
#include "gfx/Renderer.h"
#include "gfx/Shader.h"
#include "util/Logger.h"

Light::Light()
{
    std::cout << "HIIIIIIIIIIIIIIIIIIIIIIIIIIIII" << std::endl;
    color_ = Vector3f(1.0, 1.0, 1.0);
    ambientIntensity_ = 0.3;
    diffuseIntensity_ = 0.8;
}

Light::Light(Vector3f color, float ambientIntensity, float diffuseIntensity)
{
    color_ = color;
    ambientIntensity_ = ambientIntensity;
    diffuseIntensity_ = diffuseIntensity;
}

Light::~Light()
{

}

void Light::update()
{
    Shader * shader = Game::instance()->renderer()->textureShader();
    shader->enable();
    
    glUniform3f(colorLoc_, color_.x(), color_.y(), color_.z());
    glUniform1f(ambientIntensityLoc_, ambientIntensity_);
    glUniform1f(diffuseIntensityLoc_, diffuseIntensity_);

    shader->disable();
}
