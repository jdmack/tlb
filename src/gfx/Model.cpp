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
    texLoc_ = -1;
    normalLoc_ = -1;
    specularIntensityLoc_ = -1;
    specularPowerLoc_ = -1;
    worldLoc_ = -1;
    cameraLoc_ = -1;
    cameraPositionLoc_ = -1;
    projectionLoc_ = -1;
    colorLoc_ = -1;
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

    vertexPositionLoc_ = shader->getAttribLocation("v_Position");
    if(vertexPositionLoc_ == -1) {
        Logger::write(Logger::ss << "v_Position is not a valid glsl program variable!"); 
    }

    texLoc_ = shader->getAttribLocation("v_TexCoord");
    if(texLoc_ == -1) {
        Logger::write(Logger::ss << "v_TexCoord is not a valid glsl program variable!"); 
    }

    normalLoc_ = shader->getAttribLocation("v_Normal");
    if(normalLoc_ == -1) {
        Logger::write(Logger::ss << "v_Normal is not a valid glsl program variable!"); 
    }

    specularIntensityLoc_ = shader->getAttribLocation("v_SpecularIntensity");
    if(specularIntensityLoc_ == -1) {
        Logger::write(Logger::ss << "v_SpecularIntensity is not a valid glsl program variable!"); 
    }

    specularPowerLoc_ = shader->getAttribLocation("v_SpecularPower");
    if(specularPowerLoc_ == -1) {
        Logger::write(Logger::ss << "v_SpecularPower is not a valid glsl program variable!"); 
    }

    worldLoc_ = shader->getUniformLocation("v_World");
    if(worldLoc_ == -1) {
        Logger::write(Logger::ss << "v_World is not a valid glsl program variable!"); 
    }

    cameraLoc_ = shader->getUniformLocation("v_Camera");
    if(cameraLoc_ == -1) {
        Logger::write(Logger::ss << "v_Camera is not a valid glsl program variable!"); 
    }

    cameraPositionLoc_ = shader->getUniformLocation("f_CameraPosition");
    if(cameraPositionLoc_ == -1) {
        Logger::write(Logger::ss << "f_CameraPosition is not a valid glsl program variable!"); 
    }

    projectionLoc_ = shader->getUniformLocation("v_Projection");
    if(projectionLoc_ == -1) {
        Logger::write(Logger::ss << "v_Projection is not a valid glsl program variable!"); 
    }

    colorLoc_ = shader->getUniformLocation("v_Color");
    if(colorLoc_ == -1) {
        Logger::write(Logger::ss << "v_Color is not a valid glsl program variable!"); 
    }

    samplerLoc_ = shader->getUniformLocation("f_Sampler");
    if(samplerLoc_ == -1) {
        Logger::write(Logger::ss << "f_Sampler is not a valid glsl program variable!"); 
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
    glEnableVertexAttribArray(normalLoc_);
    glEnableVertexAttribArray(specularIntensityLoc_);
    glEnableVertexAttribArray(specularPowerLoc_);

    glUniformMatrix4fv(worldLoc_, 1, GL_TRUE, transform_.worldTrans().pointer());
    // TODO (2017-05-30/JM): Think I can move camera, project
    glUniformMatrix4fv(cameraLoc_, 1, GL_TRUE, Game::instance()->renderer()->camera()->view().pointer());
    glUniform3fv(cameraPositionLoc_, 1, Game::instance()->renderer()->camera()->position().pointer());
    glUniformMatrix4fv(projectionLoc_, 1, GL_TRUE, Game::instance()->renderer()->camera()->projection().pointer());

    glUniform4fv(colorLoc_, 1, color_.pointer());

    // Set vertex data
    glBindBuffer(GL_ARRAY_BUFFER, vbo_);
    glVertexAttribPointer(vertexPositionLoc_, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), NULL);
    // Tex coords are behind a Vector3(Position) in memory 
    glVertexAttribPointer(texLoc_, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*) sizeof(Vector3f));
    // Normal is behind a Vector3(Position) and Vector2(Tex coords) in memory 
    glVertexAttribPointer(normalLoc_, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*) (sizeof(Vector3f) + sizeof(Vector2f)));
    // SpecularIntensity is behind a Vector3(Position), Vector2(Tex coords) and Vector3(Normal) in memory
    glVertexAttribPointer(specularIntensityLoc_, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*) (sizeof(Vector3f) + sizeof(Vector2f) 
        + sizeof(Vector3f)));
    // SpecularPower is behind a Vector3(Position), Vector2(Tex coords), Vector3(Normal) and float(SpecularIntensity) in memory
    glVertexAttribPointer(specularPowerLoc_, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*) (sizeof(Vector3f) + sizeof(Vector2f) 
        + sizeof(Vector3f) + sizeof(float)));

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
    glDisableVertexAttribArray(normalLoc_);
    glDisableVertexAttribArray(specularIntensityLoc_);
    glDisableVertexAttribArray(specularPowerLoc_);

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

void Model::calculateNormals(const int * indices, int indexCount, Vertex * vertices, int vertexCount)
{
    for(unsigned int i = 0; i < indexCount; i += 3) {

        unsigned int index0 = indices[i];
        unsigned int index1 = indices[i + 1];
        unsigned int index2 = indices[i + 2];

        Vector3f v1 = vertices[index1].position() - vertices[index0].position();
        Vector3f v2 = vertices[index2].position() - vertices[index0].position();
        Vector3f normal = v1.crossProduct(v2);
        normal.normalize();

        vertices[index0].setNormal(vertices[index0].normal() + normal);
        vertices[index1].setNormal(vertices[index0].normal() + normal);
        vertices[index2].setNormal(vertices[index0].normal() + normal);
    }

    for(unsigned int i = 0; i < vertexCount; ++i) {
        //vertices[i].setNormal(vertices[i].normal().normalize());
        vertices[i].normal().normalize();
    }
}


