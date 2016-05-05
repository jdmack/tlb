#ifndef TLB_CAMERA2D_H_
#define TLB_CAMERA2D_H_

#include "SDL2/SDL.h"
#include "Constants.h"

const double kCamera2DInitialX = 0;
const double kCamera2DInitialY = 0;
const double kCamera2DWidth = kRendererWidth;
const double kCamera2DHeight = kRendererHeight;

class GameObject;

class Camera2D
{
    private:
        double xPosition_;
        double yPosition_;
        double width_;
        double height_;

    public:
        Camera2D();
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
