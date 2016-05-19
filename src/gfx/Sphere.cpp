#include "gfx/Sphere.h"
#include "util/Logger.h"

Sphere::Sphere()
{
    stacks_ = 3;
    slices_ = 3;
}

Sphere::Sphere(float radius, Vector3f center) : Sphere()
{
    radius_ = radius;
    center_ = center;
    loadModelData();

    //model_.setMode(DRAW_LINES);
}

void Sphere::loadModelData()
{
    Vector3f * vertices = new Vector3f[(stacks_ + 1) * (slices_ + 1)];
    int * indices = new int[(stacks_ * slices_ + slices_) * 6];

    int vertIndex = 0;
    int indIndex = 0;

    for(int i = 0; i <= stacks_; ++i) {
        float v = (float) i / (float) stacks_;
        float phi = v * M_PI;

        for(int j = 0; j <= slices_; ++j) {
            float u = (float) j / (float) slices_;
            float theta = u * M_PI * 2;

            // calculate the vertex positions
            float x = cosf(theta) * sinf(phi);
            float y = cosf(phi);
            float z = sinf(theta) * sinf(phi);

            Vector3f vertex = Vector3f(x, y, z);
            vertex = vertex * radius_;

            vertices[vertIndex++] = vertex;
            //Logger::write(Logger::ss << "Generating vertex: " << vertex);
        }
    }
    
    for(int i = 0; i < slices_ * stacks_ + slices_; ++i) {
        indices[indIndex++] = i;
        indices[indIndex++] = i + slices_ + 1;
        indices[indIndex++] = i + slices_;

        indices[indIndex++] = i + slices_ + 1;
        indices[indIndex++] = i;
        indices[indIndex++] = i + 1;
    }

    for(int i = 0; i < indIndex; i = i + 6) {
        Logger::write(Logger::ss << "(" << indices[i] 
            << "," << indices[i + 1]
            << "," << indices[i + 2]
            << "," << indices[i + 3]
            << "," << indices[i + 4]
            << "," << indices[i + 5] << ")");
    
    }

    Logger::write(Logger::ss << "vertices: " << vertIndex);
    Logger::write(Logger::ss << "indices: " << indIndex);

    model_.loadVertices(vertices, sizeof(vertices));
    model_.loadIndices(indices, sizeof(indices));
}

void Sphere::setCenter(Vector3f center)
{
    center_ = center;
    update();
}

void Sphere::setColor(Vector4f color)
{
    color_ = color;
    model_.setColor(color_);
}

void Sphere::update()
{
    loadModelData();
}

void Sphere::render()
{
    model_.render();
}
