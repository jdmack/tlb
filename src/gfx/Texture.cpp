#include <iostream>
//#include <ImageMagick/Magick++.h>
#include "gfx/Texture.h"
#include "gfx/Renderer.h"
#include "Game.h"
#include "util/Logger.h"

Texture::Texture(const std::string & filename)
{
    textureObj_ = 0;
    textureTarget_ = GL_TEXTURE_2D;
    filename_      = filename;
    load();
}

Texture::Texture(GLenum textureTarget, const std::string & filename)
{
    textureObj_ = 0;
    textureTarget_ = textureTarget;
    filename_      = filename;
    load();
}

bool Texture::load()
{
    // Read in image
    SDL_Surface * surface = Game::instance()->renderer()->loadImageAlpha(filename_);

    if(surface == nullptr) {
        Logger::write(Logger::ss << "ERROR: Unable to load texture: " << filename_);
        return false;
    }

    int mode = GL_RGB;
    if(surface->format->BytesPerPixel == 4) {
        mode = GL_RGBA;
    }

    // ImageMagick code
    //try {
    //    image_.read(filename_);
    //    image_.write(&blob_, "RGBA");
    //}
    //catch(Magick::Error & error) {
    //    std::cout << "ERROR loading texture '" << filename_ << "': " << error.what() << std::endl;
    //    return false;
    //}
    //glTexImage2D(textureTarget_, 0, GL_RGBA, image_.columns(), image_.rows(), 0, GL_RGBA, GL_UNSIGNED_BYTE, blob_.data());

    // Generate texture object
    glGenTextures(1, &textureObj_);

    // Bind current texture
    glBindTexture(textureTarget_, textureObj_);

    // Load texture data into OpenGL
    glTexImage2D(textureTarget_, 0, mode, surface->w, surface->h, 0, mode, GL_UNSIGNED_BYTE, surface->pixels);

    glTexParameteri(textureTarget_, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(textureTarget_, GL_TEXTURE_MAG_FILTER, GL_LINEAR);    
    glTexParameteri(textureTarget_, GL_TEXTURE_WRAP_S, GL_REPEAT);    
    glTexParameteri(textureTarget_, GL_TEXTURE_WRAP_T, GL_REPEAT);    

    // Unbind texture
    glBindTexture(textureTarget_, 0);

    SDL_FreeSurface(surface);
    
    return true;
}

void Texture::bind(GLenum textureUnit)
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureObj_);
}
