#ifndef TLB_GFX_CAMERA_H_
#define TLB_GFX_CAMERA_H_

#include "math/Vector3f.h"
#include "math/Vector2i.h"
#include "event/Event.h"

class Camera
{
   private:


       Vector3f position_;
       Vector3f target_;
       Vector3f up_;

       int m_windowWidth;
       int m_windowHeight;

       float angleH_;
       float angleV_;

       bool onUpperEdge_;
       bool onLowerEdge_;
       bool onLeftEdge_;
       bool onRightEdge_;

       Vector2i mousePosition_;

       void init();
       void update();

   public:

       Camera(int windowWindow, int windowHeight);

       Camera(int windowWidth, int windowHeight, const Vector3f & position, const Vector3f & target, const Vector3f & up);

       bool onKeyboard(KeyType key);

       void onMouse(int x, int y);

       void onRender();

       const Vector3f & position() const { return position_; }
       const Vector3f & GetTarget() const { return target_; } 
       const Vector3f & GetUp() const { return up_; }

};

#endif

