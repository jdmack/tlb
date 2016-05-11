#include "GL/glew.h"
#include "GL/glu.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_opengl.h"

#include "gfx/Model.h"
#include "Game.h"
#include "gfx/Renderer.h"
#include "util/Logger.h"

#include "math/Vector3f.h"
#include "math/Matrix4f.h"

////////////////////////////////////////////////////////////////////////////////
//
//
//
////////////////////////////////////////////////////////////////////////////////
Model::Model()
{
    vertexPositionLoc_ = -1;
    worldLoc_ = -1;
    cameraLoc_ = -1;
    projectionLoc_ = -1;
    colorLoc_ = -1;

    color_ = Vector4f(1.0f, 0.0f, 0.0f, 1.0f);

    init();

    Logger::write(Logger::ss << "Model(vertex: " << vertexPositionLoc_ << ", world: " << worldLoc_ << ", vbo_: " << vbo_ << ", ibo: " << ibo_);
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

    cameraLoc_ = glGetUniformLocation(Game::instance()->renderer()->programID(), "Camera");
    if(cameraLoc_ == -1) {
        Logger::write(Logger::ss << "Camera is not a valid glsl program variable!"); 
    }

    projectionLoc_ = glGetUniformLocation(Game::instance()->renderer()->programID(), "Projection");
    if(projectionLoc_ == -1) {
        Logger::write(Logger::ss << "Projection is not a valid glsl program variable!"); 
    }

    colorLoc_ = glGetUniformLocation(Game::instance()->renderer()->programID(), "Color");
    if(colorLoc_ == -1) {
        Logger::write(Logger::ss << "Color is not a valid glsl program variable!"); 
    }

    // TODO(2016-05-09/JM): Change the way vertex and index data is loaded in
    //                      to generalize Model class

    // VBO data
    Vector3f vertices[8];
    vertices[0] = Vector3f(-0.5f, 0.0f, -0.5f);
    vertices[1] = Vector3f(0.5f, 0.0f, -0.5f);
    vertices[2] = Vector3f(-0.5f, 0.0f, 0.5f);
    vertices[3] = Vector3f(0.5f, 0.0f, 0.5f);
    vertices[4] = Vector3f(-0.5f, 0.5f, -0.5f);
    vertices[5] = Vector3f(0.5f, 0.5f, -0.5f);
    vertices[6] = Vector3f(-0.5f, 0.5f, 0.5f);
    vertices[7] = Vector3f(0.5f, 0.5f, 0.5f);

    // IBO data
    GLuint indices[] = { 4, 6, 7,   // 1a
                         4, 7, 5,   // 1b
                         0, 2, 3,   // 2a
                         0, 3, 1,   // 2b
                         0, 4, 5,   // 3a
                         0, 5, 1,   // 3b
                         0, 4, 6,   // 4a
                         0, 6, 2,   // 4b
                         1, 5, 7,   // 5a
                         1, 7, 3,   // 5b
                         2, 6, 7,   // 6a
                         2, 7, 3 }; // 6b

    // Create VBO
    glGenBuffers(1, &vbo_);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Create IBO
    glGenBuffers(1, &ibo_);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    return true;
}

void Model::render()
{
    // Bind program
    glUseProgram(Game::instance()->renderer()->programID());

    // Enable vertex position
    glEnableVertexAttribArray(vertexPositionLoc_);

    glUniformMatrix4fv(worldLoc_, 1, GL_TRUE, transform_.getTrans().pointer());
    glUniformMatrix4fv(cameraLoc_, 1, GL_TRUE, Game::instance()->renderer()->camera()->view().pointer());
    glUniformMatrix4fv(projectionLoc_, 1, GL_TRUE, Game::instance()->renderer()->camera()->projection().pointer());

    glUniform4fv(colorLoc_, 1, color_.pointer());

    // Set vertex data
    glBindBuffer(GL_ARRAY_BUFFER, vbo_);
    glVertexAttribPointer(vertexPositionLoc_, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), NULL);

    // Set index data and render
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    // Disable vertex position
    glDisableVertexAttribArray(vertexPositionLoc_);

    // Unbind program
    glUseProgram(0);
}

void Model::update()
{

}
