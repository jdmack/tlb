#ifndef TLB_GFX_CAMERA_H_
#define TLB_GFX_CAMERA_H_

#include "util/math/Vector3.h"
#include "util/math/Vector2i.h"
#include "event/Event.h"

class Camera
{
   private:


       Vector3 position_;
       Vector3 target_;
       Vector3 up_;

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

       Camera(int windowWidth, int windowHeight, const Vector3 & position, const Vector3 & target, const Vector3 & up);

       bool onKeyboard(KeyType key);

       void onMouse(int x, int y);

       void onRender();

       const Vector3 & position() const { return position_; }
       const Vector3 & GetTarget() const { return target_; } 
       const Vector3 & GetUp() const { return up_; }

};

#endif

