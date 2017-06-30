#include "GL/glew.h"
#include "gfx/lighting/PointLight.h"
#include "Game.h"
#include "gfx/Renderer.h"
#include "gfx/Shader.h"
#include "util/Logger.h"

PointLight::PointLight()
{
    position_ = Vector3f(0.0, 0.0, 0.0);
    attenConstant_ = 0.0;
    attenLinear_ = 0.0;
    attenExp_ = 0.0;

}

PointLight::PointLight(Vector3f color, float ambientIntensity, float diffuseIntensity, Vector3f position,
    float attenConstant, float attenLinear, float attenExp)
    : Light(color, ambientIntensity, diffuseIntensity)
{
    position_ = position;
    attenConstant_ = attenConstant;
    attenLinear_ = attenLinear;
    attenExp_ = attenExp;
}

bool PointLight::init()
{
    Shader * shader = Game::instance()->renderer()->textureShader();

    std::ostringstream ss;
    ss << "f_PointLights[" << lightId_ << "]";
    std::string preName = ss.str();
    std::string name;

    name = preName + ".color";
    colorLoc_ = shader->getUniformLocation(name.c_str());
    if(colorLoc_ == -1) {
        Logger::write(Logger::ss << name << " is not a valid glsl program variable!");
    }

    name = preName + ".ambientIntensity";
    ambientIntensityLoc_ = shader->getUniformLocation(name.c_str());
    if(ambientIntensityLoc_ == -1) {
        Logger::write(Logger::ss << name << " is not a valid glsl program variable!");
    }

    name = preName + ".diffuseIntensity";
    diffuseIntensityLoc_ = shader->getUniformLocation(name.c_str());
    if(diffuseIntensityLoc_ == -1) {
        Logger::write(Logger::ss << name << " is not a valid glsl program variable!");
    }

    name = preName + ".position";
    positionLoc_ = shader->getUniformLocation(name.c_str());
    if(positionLoc_ == -1) {
        Logger::write(Logger::ss << name << " is not a valid glsl program variable!");
    }

    name = preName + ".attenConstant";
    attenConstantLoc_ = shader->getUniformLocation(name.c_str());
    if(attenConstantLoc_ == -1) {
        Logger::write(Logger::ss << name << " is not a valid glsl program variable!");
    }

    name = preName + ".attenLinear";
    attenLinearLoc_ = shader->getUniformLocation(name.c_str());
    if(attenLinearLoc_ == -1) {
        Logger::write(Logger::ss << name << " is not a valid glsl program variable!");
    }

    name = preName + ".attenExp";
    attenExpLoc_ = shader->getUniformLocation(name.c_str());
    if(attenExpLoc_ == -1) {
        Logger::write(Logger::ss << name << " is not a valid glsl program variable!");
    }

    update();

    return true;
}

void PointLight::update()
{
    Light::update();    

    Shader * shader = Game::instance()->renderer()->textureShader();
    shader->enable();
    
    glUniform3f(positionLoc_, position_.x(), position_.y(), position_.z());
    glUniform1f(attenConstantLoc_, attenConstant_);
    glUniform1f(attenLinearLoc_, attenLinear_);
    glUniform1f(attenExpLoc_, attenExp_);

    shader->disable();
}
