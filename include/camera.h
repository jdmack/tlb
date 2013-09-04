#ifndef CAMERA_H_
#define CAMERA_H_

#include "SDL/SDL.h"
#include "screen.h"
double kCameraInitialX = 0;
double kCameraInitialY = 0;
double kCameraWidth = kScreenWidth;
double kCameraHeight = kScreenHeight;

class GameObject;
class Level;

class Camera
{
    private:
        double x_position_;
        double y_position_;
        double width_;
        double height_;
        Level * level_;

    public:
        Camera();
        Camera(Level * level);
        double x_position() const { return x_position_; }
        double y_position() const { return y_position_; }
        double width() const { return width_; }
        double height() const { return height_; }
        Level * level() const { return level_; }

        void set_level(Level * level) { level_ = level; }

        void move(double x, double y);
        void center(GameObject * object);
        void fix_bounds();
        SDL_Rect rect();
};

#endif
