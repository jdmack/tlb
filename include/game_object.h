#ifndef TLB_GAME_OBJECT_H_
#define TLB_GAME_OBJECT_H_

#include "SDL/SDL.h"
#include "assets.h"
#include "vector.h"

class Action;
class Sprite;

class GameObject
{
    protected:
        static int id_counter_;
        int object_id_;
        double x_position_;
        double y_position_;
        double x_velocity_;
        double y_velocity_;
        double x_acceleration_;
        double y_acceleration_;
        double rotation_;
        double width_;
        double height_;
        bool selectable_;
        bool selected_;

        Action * current_action_;
        Sprite * sprite_;

    public:
        // constructors/destructors
        GameObject();
        GameObject(double x, double y, double rot);
        virtual ~GameObject();

        // accessors
        int object_id() const { return object_id_; }
        double x_position() const { return x_position_; }
        double y_position() const { return y_position_; }
        double x_velocity() const { return x_velocity_; }
        double y_velocity() const { return y_velocity_; }
        double x_acceleration() const { return x_acceleration_; }
        double y_acceleration() const { return y_acceleration_; }
        double rotation() const { return rotation_; }
        double width() const { return width_; }
        double height() const { return height_; }
        bool selectable() const { return selectable_; }
        bool selected() const { return selected_; }

        Action * current_action() const { return current_action_; }
        Sprite * sprite() const { return sprite_; }

        virtual void select();
        virtual void deselect();
        virtual bool contains_point(double x, double y);
        virtual void move(double x, double y);
        virtual void stop();
        void draw();
        void set_current_action(Action * action) { current_action_ = action; }
        void set_sprite(Sprite * sprite) { sprite_ = sprite; }

};

#endif
