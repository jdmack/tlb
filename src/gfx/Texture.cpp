#include <iostream>
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
    SDL_DisplayFormatAlpha(surface);

    if(surface == nullptr) {
        Logger::write(Logger::ss << "ERROR: Unable to load texture: " << filename_);
        return false;
    }
    int mode = GL_RGB;

    if(surface->format->BytesPerPixel == 4) {
        if(surface->format->Rshift == 24 && surface->format->Aloss == 0) {
            mode = GL_ABGR_EXT;
            std::cout << "GL_ABGR_EXT" << std::endl;
        }
        else if(surface->format->Rshift == 16 && surface->format->Aloss == 8) {
            mode = GL_BGRA;
            std::cout << "GL_BGRA" << std::endl;
        }
        else if(surface->format->Rshift == 16 && surface->format->Ashift == 24) {
            mode = GL_BGRA;
            std::cout << "GL_BGRA" << std::endl;
        }
        else if(surface->format->Rshift == 0 && surface->format->Ashift == 24) {
            mode = GL_RGBA;
            std::cout << "GL_RGBA" << std::endl;
        }
        else {
            std::cout << "Pixel Format not recognized for GL display" << std::endl;
        }
    }
    else if(surface->format->BytesPerPixel == 3) {
        if(surface->format->Rshift == 16) {
            mode = GL_BGR;
            std::cout << "GL_BGR" << std::endl;
        }
        else if( surface->format->Rshift == 0) {
            mode = GL_RGB;
            std::cout << "RGB" << std::endl;
        }
        else {
            std::cout << "Pixel Format not recognized for GL display" << std::endl;
        }
    }
    //else std::cout >> "Pixel Format not recognized for GL display";



    //std::cout << "width: " << surface->w << " height: " << surface->h << std::endl;

    //int mode = GL_RGB;
    //if(surface->format->BytesPerPixel == 4) {
        //mode = GL_RGBA;
    //}

    // Generate texture object
    glGenTextures(1, &textureObj_);

    // Bind current texture
    glBindTexture(textureTarget_, textureObj_);

    // Load texture data into OpenGL
    glTexImage2D(textureTarget_, 0, mode, surface->w, surface->h, 0, mode, GL_UNSIGNED_BYTE, surface->pixels);

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
