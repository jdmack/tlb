#include <iostream>
#include "gfx/Texture.h"
#include "gfx/Renderer.h"
#include "Game.h"
#include "util/Logger.h"

Texture::Texture(GLenum textureTarget, const std::string & filename)
{
    textureTarget_ = textureTarget;
    filename_      = filename;
}

bool Texture::load()
{
    // Read in image
    SDL_Surface * surface = Game::instance()->renderer()->loadImageAlpha(filename_);

    if(surface == nullptr) {
        Logger::write(Logger::ss << "ERROR: Unable to load texture: " << filename_);
        return false;
    }

    // Generate texture object
    glGenTextures(1, &textureObj_);

    // Bind current texture
    glBindTexture(textureTarget_, textureObj_);

    // Load texture data into OpenGL
    glTexImage2D(textureTarget_, 0, GL_RGBA, surface->w, surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);

    glTexParameterf(textureTarget_, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(textureTarget_, GL_TEXTURE_MAG_FILTER, GL_LINEAR);    

    // Unbind texture
    glBindTexture(textureTarget_, 0);

    delete surface;
    
    return true;
}

void Texture::bind(GLenum textureUnit)
{
    glActiveTexture(textureUnit);
    glBindTexture(textureTarget_, textureObj_);
}
