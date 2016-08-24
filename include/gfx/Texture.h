#ifndef TLB_GFX_TEXTURE_H_
#define	TLB_GFX_TEXTURE_H_

#include <string>
//#include <ImageMagick/Magick++.h>

#include <GL/glew.h>

class Texture
{
    public:
        Texture(const std::string & filename);
        Texture(GLenum textureTarget, const std::string & filename);

        bool load();

        void bind(GLenum textureUnit);

    private:
        std::string filename_;
        GLenum textureTarget_;
        GLuint textureObj_;

        //Magick::Image image_;
        //Magick::Blob blob_;
};

#endif

