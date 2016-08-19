#ifndef TLB_GFX_Shader_H_
#define TLB_GFX_Shader_H_

#include <list>
#include <GL/glew.h>

class Shader
{
    public:

        Shader();
        Shader(const char* vertexFilename, const char* fragmentFilename);
        virtual ~Shader();
        virtual bool init();
        void enable();
        void disable();

        GLint getAttribLocation(const char* attribName);
        GLint getUniformLocation(const char* uniformName);
        GLint getProgramParam(GLint param);

    protected:

        bool attachShader(const char* filename, GLenum shaderType);
        bool finalize();

    
        GLuint programID_;
    
    private:

        bool initSuccess;
        std::list<GLuint> shaderList_;

        void printProgramLog(GLuint program);
        void printShaderLog(GLuint program);
};

#endif

