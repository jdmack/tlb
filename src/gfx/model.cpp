#include "GL/glew.h"
#include "GL/glu.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_opengl.h"

#include "gfx/model.h"
#include "game.h"
#include "gfx/renderer.h"
#include "util/logger.h"

////////////////////////////////////////////////////////////////////////////////
//
//
//
////////////////////////////////////////////////////////////////////////////////
Model::Model()
{
    vertexPos2DLocation = -1;

    init();
}

bool Model::init()
{
    vertexPos2DLocation = glGetAttribLocation(Game::instance()->renderer()->programID(), "LVertexPos2D");
    if(vertexPos2DLocation == -1) {
        Logger::write(Logger::ss << "LVertexPos2D is not a valid glsl program variable!"); 
        return false;
    }

    // Initialize clear color
    glClearColor(0.f, 0.f, 0.f, 1.f);

    // VBO data
    GLfloat vertexData[] =
    {
        -0.5f, -0.5f,
        0.5f, -0.5f,
        0.5f,  0.5f,
        -0.5f,  0.5f
    };

    // IBO data
    GLuint indexData[] = {0, 1, 2, 3};

    // Create VBO
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, 2 * 4 * sizeof(GLfloat), vertexData, GL_STATIC_DRAW);

    // Create IBO
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 4 * sizeof(GLint), indexData, GL_STATIC_DRAW);

    return true;
}

void Model::render()
{
    // Clear color buffer
    glClear(GL_COLOR_BUFFER_BIT);

    // Bind program
    glUseProgram(Game::instance()->renderer()->programID());

    // Enable vertex position
    glEnableVertexAttribArray(vertexPos2DLocation);

    // Set vertex data
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(vertexPos2DLocation, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), NULL);

    // Set index data and render
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, NULL);

    // Disable vertex position
    glDisableVertexAttribArray(vertexPos2DLocation);

    // Unbind program
    glUseProgram(NULL);
}

void Model::update()
{

}
