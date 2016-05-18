#include <cstdlib>
#include "gfx/MousePicker.h"
#include "Game.h"
#include "gfx/Renderer.h"
#include "gfx/Camera.h"
#include "util/Logger.h"

MousePicker::MousePicker()
{
}

MousePicker::MousePicker(Matrix4f view, Matrix4f projection)
{
    view_ = view;
    projection_ = projection;
}

void MousePicker::update(Vector2i mousePosition)
{
    ray_ = calculateMouseRay(mousePosition);
    view_ = Game::instance()->renderer()->camera()->view();
    projection_ = Game::instance()->renderer()->camera()->projection();
}

Vector3f MousePicker::calculateMouseRay(Vector2i mousePosition)
{ 

    Vector3f normalizedCoords = getNormalizedDeviceCoords(mousePosition);
    //Vector4f clipCoords = Vector4f(normalizedCoords.x(), normalizedCoords.y(), 1.0, 0.0);
    Vector4f clipCoords = Vector4f(normalizedCoords.x(), normalizedCoords.y(), normalizedCoords.z(), 1.0);
    Vector4f eyeCoords = toEyeCoords(clipCoords);
    Vector4f worldCoords = toWorldCoords(eyeCoords);
    Vector3f ray = Vector3f(worldCoords.x(), worldCoords.y(), worldCoords.z());
    Logger::write(Logger::ss << "Mouse Ray: " << ray);
    return ray;
}


Vector3f MousePicker::getNormalizedDeviceCoords(Vector2i mousePosition)
{
    float width = Game::instance()->renderer()->screenWidth();
    float height = Game::instance()->renderer()->screenHeight();
    float mouseX = mousePosition.x();
    float mouseY = mousePosition.y();

    float x = ((2.0 * mouseX) / width) - 1.0;
    float y = 1.0 - ((2.0 * mouseY) / height);
    float z = -1.0;

    Vector3f ndc = Vector3f(x, y, z);

    return ndc;
}

Vector4f MousePicker::toEyeCoords(Vector4f clipCoords)
{
    Matrix4f invertedProjection = projection_;
    invertedProjection.invert();
    
    Vector4f eyeCoords = invertedProjection * clipCoords;

    return Vector4f(eyeCoords.x(), eyeCoords.y(), -1, 0.0);
}

Vector4f MousePicker::toWorldCoords(Vector4f eyeCoords)
{
    Matrix4f invertedView = view_;
    invertedView.invert();

    Vector4f worldCoords = invertedView * eyeCoords;

    return worldCoords;
}

float MousePicker::rayPlaneIntersect(Vector3f ray, Vector3f rayOrigin, Vector3f planeNormal, Vector3f planePoint)
{
    float denom = planeNormal.dotProduct(ray);

    if(std::fabs(denom) > 0.0001f) {
        float t = (planePoint - rayOrigin).dotProduct(planeNormal) / denom;
        
        if(t >= 0) return t;

    }
    return 0;
}

