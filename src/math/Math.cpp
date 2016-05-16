#include "math/Math.h"
#include <math.h>
#include "Point.h"

Point Math::convertToIsometric(Point point)
{
    //float x = point.x() - point.y();
    //float y = (point.x() + point.y()) / 2;
    float x = point.x();
    float y = point.y();// / 2;
    return Point(x, y);
}
Point Math::convertToCartesian(Point point)
{
    //float x = (2 * point.y() + point.x()) / 2;
    //float y = (2 * point.y() - point.x()) / 2;
    float x = point.x();
    float y = point.y();// * 2;

    return Point(x, y);
}

Matrix4f Math::genPersProjTransform(float fov, float width, float height, float zNear, float zFar)
{
    const float ar = width / height;
    const float zRange = zNear - zFar;
    const float tanHalfFOV = tanf(toRadian(fov / 2.0f));
    
    float m[4][4];

    m[0][0] = 1.0f / (tanHalfFOV * ar); m[0][1] = 0.0f;              m[0][2] = 0.0f;                           m[0][3] = 0.0;
    m[1][0] = 0.0f;                     m[1][1] = 1.0f / tanHalfFOV; m[1][2] = 0.0f;                           m[1][3] = 0.0;
    m[2][0] = 0.0f;                     m[2][1] = 0.0f;              m[2][2] = (-zNear - zFar) / zRange; m[2][3] = 2.0f* zFar * zNear / zRange;
    m[3][0] = 0.0f;                     m[3][1] = 0.0f;              m[3][2] = 1.0f;                           m[3][3] = 0.0;

    Matrix4f perspectiveMatrix;

    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            perspectiveMatrix.set(row, col, m[row][col]);
        }
    }

    return perspectiveMatrix;
}

Matrix4f Math::genCameraTransform(Vector3f & target, Vector3f & up)
{
    Vector3f n = target;
    n.normalize();
    Vector3f u = up;
    u.normalize();
    u = u.crossProduct(n);
    Vector3f v = n.crossProduct(u);

    float m[4][4];

    m[0][0] = u.x();   m[0][1] = u.y();   m[0][2] = u.z();   m[0][3] = 0.0f;
    m[1][0] = v.x();   m[1][1] = v.y();   m[1][2] = v.z();   m[1][3] = 0.0f;
    m[2][0] = n.x();   m[2][1] = n.y();   m[2][2] = n.z();   m[2][3] = 0.0f;
    m[3][0] = 0.0f;    m[3][1] = 0.0f;    m[3][2] = 0.0f;    m[3][3] = 1.0f;

    Matrix4f cameraMatrix;

    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            cameraMatrix.set(row, col, m[row][col]);
        }
    }

    return cameraMatrix;
}

