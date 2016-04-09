#include "GL/glew.h"
#include "GL/glu.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_opengl.h"

#include "gfx/model.h"
#include "game.h"
#include "gfx/renderer.h"
#include "util/logger.h"

#include "util/math/vector3.h"
#include "util/math/matrix4.h"

////////////////////////////////////////////////////////////////////////////////
//
//
//
////////////////////////////////////////////////////////////////////////////////
Model::Model()
{
    vertexPositionLoc_ = -1;
    worldLoc_ = -1;

    init();
}

bool Model::init()
{
    vertexPositionLoc_ = glGetAttribLocation(Game::instance()->renderer()->programID(), "Position");
    if(vertexPositionLoc_ == -1) {
        Logger::write(Logger::ss << "Position is not a valid glsl program variable!"); 
    }

    worldLoc_ = glGetUniformLocation(Game::instance()->renderer()->programID(), "World");
    if(worldLoc_ == -1) {
        Logger::write(Logger::ss << "World is not a valid glsl program variable!"); 
    }

    // Initialize clear color
    glClearColor(0.f, 0.f, 0.f, 1.f);

    // VBO data
    Vector3 vertices[3];
    vertices[0] = Vector3(-1.0f, -1.0f, 0.0f);
    vertices[1] = Vector3(0.0f, -1.0f, 1.0f);
    vertices[2] = Vector3(1.0f, -1.0f, 0.0f);
    vertices[3] = Vector3(0.0f, 1.0f, 0.0f);

    // IBO data
    GLuint indices[] = { 0, 3, 1,
                           1, 3, 2,
                           2, 3, 0,
                           0, 1, 2 };

    // Create VBO
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Create IBO
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    return true;
}

void Model::render()
{

    // Clear color buffer
    glClear(GL_COLOR_BUFFER_BIT);

    // Bind program
    glUseProgram(Game::instance()->renderer()->programID());

    // Enable vertex position
    glEnableVertexAttribArray(vertexPositionLoc_);

    static float scale = 0.0f;
    scale += 0.01f;

    // World matrix
    Matrix4 world = Matrix4(cosf(scale), 0.0f, -sinf(scale), 0.0f,
                            0.0f,        1.0f,         0.0f, 0.0f,
                            sinf(scale), 0.0f,  cosf(scale), 0.0f,
                            0.0f,        0.0f,         0.0f, 1.0f);
    glUniformMatrix4fv(worldLoc_, 1, GL_TRUE, world.pointer());

    // Set vertex data
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(vertexPositionLoc_, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), NULL);

    // Set index data and render
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);

    // Disable vertex position
    glDisableVertexAttribArray(vertexPositionLoc_);

    // Unbind program
    glUseProgram(0);
}

void Model::update()
{

}
