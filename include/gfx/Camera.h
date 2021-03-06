#ifndef TLB_GFX_CAMERA_H_
#define TLB_GFX_CAMERA_H_

#include "math/Matrix4f.h"
#include "math/Vector3f.h"
#include "math/Vector2i.h"
#include "event/Event.h"
#include "gfx/Projection.h"

enum CameraDirection {
    CAMERA_DIRECTION_FORWARD,
    CAMERA_DIRECTION_BACKWARD,
    CAMERA_DIRECTION_RIGHT,
    CAMERA_DIRECTION_LEFT,
    CAMERA_DIRECTION_UP,
    CAMERA_DIRECTION_DOWN
};

enum CameraAxis {
    CAMERA_AXIS_X,
    CAMERA_AXIS_Y,
    CAMERA_AXIS_Z
};

class Camera
{
    private:

        Vector3f position_;
        Vector3f target_;
        Vector3f up_;

        Matrix4f view_;
        Matrix4f projection_;

        float angleH_;
        float angleV_;

        float width_;
        float height_;
        float fov_;
        float zNear_;
        float zFar_;

        bool viewDirty_;
        bool projectionDirty_;

        void init();
        void update();
        void updateView();
        void updateProjection();

    public:

        Camera(int windowWindow, int windowHeight);
        Camera(int windowWidth, int windowHeight, const Vector3f & position, const Vector3f & target, const Vector3f & up);

        void onRender();

        // accessors
        Vector3f position() const { return position_; }
        Vector3f target() const { return target_; } 
        Vector3f up() const { return up_; }
        Matrix4f view();
        Matrix4f projection();

        // mutators
        void move(CameraDirection dir, float distance);
        void rotate(CameraAxis axis, float angle);
        void setWidth(float width);
        void setHeight(float height);
        void setFovRel(float fov);
        void setZNear(float zNear);
        void setZFar(float zFar);
        void setZNearRel(float zNear);
        void setZFarRel(float zFar);
        
};

#endif

