#ifndef TLB_GFX_MODEL_H_
#define TLB_GFX_MODEL_H_

#include "SDL2/SDL.h"
#include "Transform.h"

class Model
{
    private:
        //GLfloat vertexData[8]; 
        GLuint vertexPositionLoc_;
        GLuint worldLoc_;
        GLuint vbo;
        GLuint ibo;

        Transform transform_;
        
    public:
        Model();

        // accessors

        // mutators

        bool init();
        void render();
        void update();
};

#endif
