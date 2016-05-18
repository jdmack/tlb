#ifndef TLB_GFX_MOUSE_PICKER_H_
#define TLB_GFX_MOUSE_PICKER_H_

#include "math/Vector3f.h"
#include "math/Vector2i.h"

class MousePicker
{
    private:
        Vector3f ray_;
        Matrix4f view_;
        Matrix4f projection_;

        Vector3f calculateMouseRay(Vector2i mousePosition);
        Vector3f getNormalizedDeviceCoords(Vector2i mousePosition);
        Vector4f toEyeCoords(Vector4f clipCoords); 
        Vector4f toWorldCoords(Vector4f eyeCoords);

    public:
        MousePicker();
        MousePicker(Matrix4f view, Matrix4f projection);

        // accessors
        Vector3f ray() const { return ray_; }

        void update(Vector2i mousePosition);

        float rayPlaneIntersect(Vector3f ray, Vector3f rayOrigin, Vector3f planeNormal, Vector3f planePoint);

};


#endif

