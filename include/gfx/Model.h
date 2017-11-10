#ifndef TLB_GFX_MODEL_H_
#define TLB_GFX_MODEL_H_

#include "GL/glew.h"
#include "SDL2/SDL.h"
#include "Transform.h"
#include "math/Vector4f.h"
#include "gfx/Texture.h"
#include "math/Vertex.h"

enum DrawMode {
    DRAW_TRIANGLES,
    DRAW_LINES
};

class Model
{
    private:
        GLuint vertexPositionLoc_;
        GLuint texLoc_;
        GLuint normalLoc_;
        GLuint specularIntensityLoc_;
        GLuint specularPowerLoc_;
        GLuint worldLoc_;
        GLuint cameraLoc_;
        GLuint cameraPositionLoc_;
        GLuint projectionLoc_;
        GLuint colorLoc_;
        GLuint samplerLoc_;
        GLuint vbo_;
        GLuint ibo_;
        GLuint vao_;
        GLenum mode_;
        int numOfIndices_;

        Vector4f color_;

        Transform transform_;
        Texture * texture_;
        
    public:
        Model();

        // accessors
        Transform & transform() { return transform_; }
        Texture * texture() { return texture_; }

        // mutators
        void setColor(Vector4f color) { color_ = color; }
        void setMode(DrawMode mode);
        void setTexture(Texture * texture) { texture_ = texture; }

        bool init();
        void render();
        void update();

        void loadVertices(Vertex * vertices, int size);
        void loadIndices(int * indices, int size);
        void calculateNormals(const int * indices, int indexCount, Vertex * vertices, int vertexCount);
};

#endif
