#ifndef TLB_CAMERA_H_
#define TLB_CAMERA_H_

#include "SDL2/SDL.h"
#include "constants.h"

const double kCameraInitialX = 0;
const double kCameraInitialY = 0;
const double kCameraWidth = kRendererWidth;
const double kCameraHeight = kRendererHeight;

class GameObject;

class Camera
{
    private:
        double x_position_;
        double y_position_;
        double width_;
        double height_;

    public:
        Camera();
        double x_position() const { return x_position_; }
        double y_position() const { return y_position_; }
        double width() const { return width_; }
        double height() const { return height_; }


        void move(double x, double y);
        void center(GameObject * object);
        void fix_bounds();
        bool contains(SDL_Rect rect);
        SDL_Rect rect();

        double x_adjust(double x);
        double y_adjust(double y);
};

#endif
