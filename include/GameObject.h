#ifndef TLB_GAME_OBJECT_H_
#define TLB_GAME_OBJECT_H_

#include "SDL2/SDL.h"
#include "Assets.h"
#include "Vector.h"
#include "Point.h"
#include "gfx/Model.h"

class Sprite;
class Frame;

class GameObject
{
    protected:
        static int idCounter_;
        int objectId_;
        double xPosition_;
        double yPosition_;
        double xVelocity_;
        double yVelocity_;
        double xAcceleration_;
        double yAcceleration_;
        double rotation_;
        double width_;
        double height_;
        bool selectable_;
        bool selected_;
        // TODO(2013-09-06/JM): Create "to string" function for objects to use with logging

        double xAbs_;
        double yAbs_;

        Point position_;
        Model model_;

    public:
        // constructors/destructors
        GameObject();
        GameObject(Point position, double rot);
        virtual ~GameObject();

        // accessors
        int objectId() const { return objectId_; }
        double xPosition() const { return xPosition_; }
        double yPosition() const { return yPosition_; }
        double xVelocity() const { return xVelocity_; }
        double yVelocity() const { return yVelocity_; }
        double xAcceleration() const { return xAcceleration_; }
        double yAcceleration() const { return yAcceleration_; }
        double rotation() const { return rotation_; }
        double width() const { return width_; }
        double height() const { return height_; }
        bool selectable() const { return selectable_; }
        bool selected() const { return selected_; }

        double xAbs() const { return xAbs_; }
        double yAbs() const { return yAbs_; }

        Point position();

        Model & model() { return model_; }

        // mutators
        void setXPosition(double xPosition) { xPosition_ = xPosition; }
        void setYPosition(double yPosition) { yPosition_ = yPosition; }
        void setXVelocity(double xVelocity) { xVelocity_ = xVelocity; }
        void setYVelocity(double yVelocity) { yVelocity_ = yVelocity; }
        void setXAcceleration(double xAcceleration) { xAcceleration_ = xAcceleration; }
        void setYAcceleration(double yAcceleration) { yAcceleration_ = yAcceleration; }
        void setRotation(double rotation) { rotation_ = rotation; }
        void setWidth(double width) { width_ = width; }
        void setHeight(double height) { height_ = height; }
        void setSelectable(bool selectable) { selectable_ = selectable; }
        void setPosition(Point position);

        void setXAbs(double xAbs) { xAbs_ = xAbs; }
        void setYAbs(double yAbs) { yAbs_ = yAbs; }

        virtual void select();
        virtual void deselect();
        virtual bool containsPoint(double x, double y);
        virtual void move(Point point);
        void render();

        bool checkCollision(SDL_Rect rect);
        void fixCollision(SDL_Rect rect);

        virtual bool isEntity() const { return false; }
};

#endif
