#include "GL/glew.h"
#include "GL/glu.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_opengl.h"

#include "gfx/Model.h"
#include "Game.h"
#include "gfx/Renderer.h"
#include "util/Logger.h"
#include "gfx/Camera.h"
#include "gfx/Shader.h"

#include "math/Vector3f.h"
#include "math/Matrix4f.h"

////////////////////////////////////////////////////////////////////////////////
//
//
//
////////////////////////////////////////////////////////////////////////////////
Model::Model()
{
    vbo_ = -1;
    ibo_ = -1;
    vertexPositionLoc_ = -1;
    worldLoc_ = -1;
    cameraLoc_ = -1;
    projectionLoc_ = -1;
    colorLoc_ = -1;
    texLoc_ = -1;
    samplerLoc_ = -1;
    mode_ = GL_TRIANGLES;
    numOfIndices_ = 0;

    color_ = Vector4f(0.0f, 0.0f, 0.0f, 0.0f);

    texture_ = nullptr;

    init();

}

bool Model::init()
{
    Shader * shader = Game::instance()->renderer()->textureShader();

    vertexPositionLoc_ = shader->getAttribLocation("Position");
    if(vertexPositionLoc_ == -1) {
        Logger::write(Logger::ss << "Position is not a valid glsl program variable!"); 
    }

    worldLoc_ = shader->getUniformLocation("World");
    if(worldLoc_ == -1) {
        Logger::write(Logger::ss << "World is not a valid glsl program variable!"); 
    }

    cameraLoc_ = shader->getUniformLocation("Camera");
    if(cameraLoc_ == -1) {
        Logger::write(Logger::ss << "Camera is not a valid glsl program variable!"); 
    }

    projectionLoc_ = shader->getUniformLocation("Projection");
    if(projectionLoc_ == -1) {
        Logger::write(Logger::ss << "Projection is not a valid glsl program variable!"); 
    }

    colorLoc_ = shader->getUniformLocation("Color");
    if(colorLoc_ == -1) {
        Logger::write(Logger::ss << "Color is not a valid glsl program variable!"); 
    }

    texLoc_ = shader->getAttribLocation("TexCoord");
    if(texLoc_ == -1) {
        Logger::write(Logger::ss << "TexCoord is not a valid glsl program variable!"); 
    }

    samplerLoc_ = shader->getUniformLocation("Sampler");
    if(samplerLoc_ == -1) {
        Logger::write(Logger::ss << "Sampler is not a valid glsl program variable!"); 
    }

    return true;
}

void Model::render()
{
    //Shader * shader = Game::instance()->renderer()->shader();
    Shader * shader = Game::instance()->renderer()->textureShader();
    shader->enable();


    // Enable vertex position
    glEnableVertexAttribArray(vertexPositionLoc_);
    glEnableVertexAttribArray(texLoc_);

    glUniformMatrix4fv(worldLoc_, 1, GL_TRUE, transform_.worldTrans().pointer());
    glUniformMatrix4fv(cameraLoc_, 1, GL_TRUE, Game::instance()->renderer()->camera()->view().pointer());
    glUniformMatrix4fv(projectionLoc_, 1, GL_TRUE, Game::instance()->renderer()->camera()->projection().pointer());

    glUniform4fv(colorLoc_, 1, color_.pointer());

    // Set vertex data
    glBindBuffer(GL_ARRAY_BUFFER, vbo_);
    glVertexAttribPointer(vertexPositionLoc_, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), NULL);
    glVertexAttribPointer(texLoc_, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*) sizeof(Vector3f));
    // Tex coords are behind a Vector3 in memory 

    // Set index data and render
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_);

    if(texture_ != nullptr) {
        texture_->bind(GL_TEXTURE0);
    }
    glUniform1i(samplerLoc_, 0);


    glDrawElements(mode_, numOfIndices_, GL_UNSIGNED_INT, 0);

    // Disable vertex position
    glDisableVertexAttribArray(vertexPositionLoc_);
    glDisableVertexAttribArray(texLoc_);

    shader->disable();

}

void Model::update()
{

}

void Model::loadVertices(Vertex * vertices, int size)
{
    // If buffer already created for this model, delete it
    if(vbo_ != -1) {
        glDeleteBuffers(1, &vbo_);
    }

    // Create VBO
    glGenBuffers(1, &vbo_);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_);
    glBufferData(GL_ARRAY_BUFFER, size, (const GLvoid *)vertices, GL_STATIC_DRAW);
}

void Model::loadIndices(int * indices, int size)
{
    // If buffer already created for this model, delete it
    if(ibo_ != -1) {
        glDeleteBuffers(1, &ibo_);
    }

    // Create IBO
    glGenBuffers(1, &ibo_);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
    //Logger::write(Logger::ss << "Model(vertex: " << vertexPositionLoc_ << ", world: " << worldLoc_ << ", vbo_: " << vbo_ << ", ibo: " << ibo_);

    numOfIndices_ = size / sizeof(int);

}

void Model::setMode(DrawMode mode)
{
    switch(mode) {
        case DRAW_LINES:
            mode_ = GL_LINES;
            break;
        case DRAW_TRIANGLES:
            mode_ = GL_TRIANGLES;
            break;
    }
}


