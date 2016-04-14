#ifndef TLB_CAMERA_H_
#define TLB_CAMERA_H_

#include "SDL2/SDL.h"
#include "Constants.h"

const double kCameraInitialX = 0;
const double kCameraInitialY = 0;
const double kCameraWidth = kRendererWidth;
const double kCameraHeight = kRendererHeight;

class GameObject;

class Camera
{
    private:
        double xPosition_;
        double yPosition_;
        double width_;
        double height_;

    public:
        Camera();
        double xPosition() const { return xPosition_; }
        double yPosition() const { return yPosition_; }
        double width() const { return width_; }
        double height() const { return height_; }


        void move(double x, double y);
        void center(GameObject * object);
        void fixBounds();
        bool contains(SDL_Rect rect);
        SDL_Rect rect();

        double xAdjust(double x);
        double yAdjust(double y);
};

#endif
