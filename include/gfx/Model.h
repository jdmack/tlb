#ifndef TLB_GFX_MODEL_H_
#define TLB_GFX_MODEL_H_

#include "GL/glew.h"
#include "SDL2/SDL.h"
#include "Transform.h"
#include "math/Vector4f.h"

enum DrawMode {
    DRAW_TRIANGLES,
    DRAW_LINES
};

class Model
{
    private:
        GLuint vertexPositionLoc_;
        GLuint worldLoc_;
        GLuint cameraLoc_;
        GLuint projectionLoc_;
        GLuint colorLoc_;
        GLuint vbo_;
        GLuint ibo_;
        GLenum mode_;
        int numOfIndices_;

        Vector4f color_;

        Transform transform_;
        
    public:
        Model();

        // accessors
        Transform & transform() { return transform_; }

        // mutators
        void setColor(Vector4f color) { color_ = color; }
        void setMode(DrawMode mode);

        bool init();
        void render();
        void update();

        void loadVertices(Vector3f * vertices, int size);
        void loadIndices(int * indices, int size);
};

#endif
