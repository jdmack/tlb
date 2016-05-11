#ifndef TLB_GFX_CAMERA_H_
#define TLB_GFX_CAMERA_H_

#include "math/Matrix4f.h"
#include "math/Vector3f.h"
#include "math/Vector2i.h"
#include "event/Event.h"
#include "gfx/Projection.h"

class Camera
{
    private:

        Vector3f position_;
        Vector3f target_;
        Vector3f up_;
        Matrix4f view_;
        Matrix4f projection_;

        int windowWidth_;
        int windowHeight_;

        float angleH_;
        float angleV_;

        bool onUpperEdge_;
        bool onLowerEdge_;
        bool onLeftEdge_;
        bool onRightEdge_;

        Vector2i mousePosition_;
        PersProjInfo persProjInfo_;

        void init();
        void update();

        void updateView();

    public:

        Camera(int windowWindow, int windowHeight);

        Camera(int windowWidth, int windowHeight, const Vector3f & position, const Vector3f & target, const Vector3f & up);

        bool onKeyboard(KeyType key);

        void onMouse(int x, int y);

        void onRender();

        Vector3f position() const { return position_; }
        Vector3f target() const { return target_; } 
        Vector3f up() const { return up_; }
        Matrix4f view();//const { return view_; }
        Matrix4f projection();//const { return view_; }
        PersProjInfo persProjInfo() { return persProjInfo_; }
        

};

#endif

