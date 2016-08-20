#ifndef TLB_GFX_TEXTURE_H_
#define	TLB_GFX_TEXTURE_H_

#include <string>

#include <GL/glew.h>

class Texture
{
    public:
        Texture(GLenum textureTarget, const std::string & filename);

        bool load();

        void bind(GLenum textureUnit);

    private:
        std::string filename_;
        GLenum textureTarget_;
        GLuint textureObj_;
};

#endif

