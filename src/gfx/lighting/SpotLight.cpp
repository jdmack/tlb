#include "GL/glew.h"
#include "gfx/lighting/SpotLight.h"
#include "Game.h"
#include "gfx/Renderer.h"
#include "gfx/Shader.h"
#include "util/Logger.h"

SpotLight::SpotLight()
{
    direction_ = Vector3f(0.0, 0.0, 0.0);
    cutoff_ = 1.0;
}

SpotLight::SpotLight(Vector3f color, float ambientIntensity, float diffuseIntensity, Vector3f position,
    float attenConstant, float attenLinear, float attenExp, Vector3f direction, float cutoff)
    : PointLight(color, ambientIntensity, diffuseIntensity, position, attenConstant, attenLinear, attenExp)
{
    direction_ = direction;
    cutoff_ = cutoff;
}

bool SpotLight::init()
{
    Shader * shader = Game::instance()->renderer()->textureShader();

    std::ostringstream ss;
    ss << "f_SpotLight[" << lightId_ << "]";
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

    name = preName + ".direction";
    directionLoc_ = shader->getUniformLocation(name.c_str());
    if(directionLoc_ == -1) {
        Logger::write(Logger::ss << name << " is not a valid glsl program variable!");
    }

    name = preName + ".cutoff";
    cutoffLoc_ = shader->getUniformLocation(name.c_str());
    if(cutoffLoc_ == -1) {
        Logger::write(Logger::ss << name << " is not a valid glsl program variable!");
    }

    return true;
}

void SpotLight::update()
{
    PointLight::update();    

    Shader * shader = Game::instance()->renderer()->textureShader();
    shader->enable();
    
    glUniform3f(directionLoc_, direction_.x(), direction_.y(), direction_.z());
    glUniform1f(cutoffLoc_, cutoff_);

    shader->disable();
}
