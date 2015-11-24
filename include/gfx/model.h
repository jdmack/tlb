#ifndef TLB_GFX_MODEL_H_
#define TLB_GFX_MODEL_H_

#include "SDL2/SDL.h"

class Model
{
    private:
        //GLfloat vertexData[8]; 
        GLuint vertexPos2DLocation;
        GLuint vbo;
        GLuint ibo;
        
    public:
        Model();

        // accessors

        // mutators

        bool init();
        void render();
        void update();
};

#endif
