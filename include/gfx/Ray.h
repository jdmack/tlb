#ifndef TLB_GFX_RAY_H_
#define TLB_GFX_RAY_H_

#include "math/Vector3f.h"
#include "math/Vector4f.h"
#include "gfx/Model.h"

class Ray
{
    private:
        Vector3f direction_;
        Vector3f origin_;
        Vector4f color_;
        Model model_;

        void loadModelData();

    public:
        Ray();
        Ray(Vector3f direction, Vector3f origin);

        // accessors
        Vector3f direction() const { return direction_; }
        Vector3f origin() const { return origin_; }
        Vector4f color() const { return color_; }

        // mutators
        void setDirection(Vector3f direction);
        void setOrigin(Vector3f origin);
        void setColor(Vector4f color);
        
        void update();
        void render();
};


#endif
