#include "gfx/LightingShader.h"

LightingShader::LightingShader() : Shader()
{

}

LightingShader::LightingShader(const char* vertexFilename, const char* fragmentFilename) : Shader(vertexFilename, fragmentFilename)
{

}


void LightingShader::collectUniforms()
{
    worldLoc_ = getUniformLocation("World");
    if(worldLoc_ == -1) {
        Logger::write(Logger::ss << "World is not a valid glsl program variable!");

    samplerLoc_ = getUniformLocation("Sampler");
    if(worldLoc_ == -1) {
        Logger::write(Logger::ss << "World is not a valid glsl program variable!");

    dirLightColorLoc_ = getUniformLocation("DirectionalLight.Color");
    if(worldLoc_ == -1) {
        Logger::write(Logger::ss << "World is not a valid glsl program variable!");

    worldLoc_ = getUniformLocation("World");
    if(worldLoc_ == -1) {
        Logger::write(Logger::ss << "World is not a valid glsl program variable!");
    }

GLuint samplerLoc_;
        GLuint dirLightColorLoc_;
                GLuint dirLightAmbientIntensityLoc_;
                `
}
