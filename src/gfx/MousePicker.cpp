#include "gfx/MousePicker.h"
#include "Game.h"
#include "gfx/Renderer.h"
#include "gfx/Camera.h"

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
    Vector4f clipCoords = Vector4f(normalizedCoords.x(), normalizedCoords.y(), normalizedCoords.z(), 1);
    Vector4f eyeCoords = toEyeCoords(clipCoords);
    Vector3f worldRay = toWorldCoords(eyeCoords);
    return worldRay;
}


Vector3f MousePicker::getNormalizedDeviceCoords(Vector2i mousePosition)
{
    int width = Game::instance()->renderer()->screenWidth();
    int height = Game::instance()->renderer()->screenHeight();

    float x = (2 * mousePosition.x()) / width - 1;
    float y = 1 - (2 * mousePosition.y()) / height;
    float z = 1;

    return Vector3f(x, y, z);
}

Vector4f MousePicker::toEyeCoords(Vector4f clipCoords)
{
    Matrix4f invertedProjection = projection_;
    invertedProjection.invert();
    Vector4f eyeCoords = invertedProjection * clipCoords;
    return Vector4f(eyeCoords.x(), eyeCoords.y(), -1, 0);
}

Vector3f MousePicker::toWorldCoords(Vector4f eyeCoords)
{
    Matrix4f invertedView = view_;
    invertedView.invert();
    Vector4f rayWorld = invertedView * eyeCoords);
    Vector3f mouseRay = Vector3f(rayWorld.x(), rayWorld.y(), rayWorld.z());
    mouseRay.normalize();
    return mouseRay;
}



