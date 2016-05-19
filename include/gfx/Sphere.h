#ifndef TLB_GFX_SPHERE_H_
#define TLB_GFX_SPHERE_H_

#include "math/Vector3f.h"
#include "math/Vector4f.h"
#include "gfx/Model.h"

class Sphere
{
    private:
        float radius_;
        Vector3f center_;
        Vector4f color_;
        Model model_;

        int stacks_;
        int slices_;

        void loadModelData();

    public:
        Sphere();
        Sphere(float radius, Vector3f center);

        // accessors
        float radius() const { return radius_; }
        Vector3f center() const { return center_; }
        Vector4f color() const { return color_; }

        // mutators
        void setRadius(float radius);
        void setCenter(Vector3f center);
        void setColor(Vector4f color);
        
        void update();
        void render();
};


#endif
