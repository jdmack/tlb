#ifndef TLB_GAME_OBJECT_H_
#define TLB_GAME_OBJECT_H_

#include "SDL2/SDL.h"
#include "assets.h"
#include "vector.h"
#include "point.h"

class Sprite;
class Game;

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
        // TODO(2013-09-06/JM): Create "to string" function for objects to use with logging

        Point position_;
        Game * game_;
        Sprite * sprite_;

    public:
        // constructors/destructors
        GameObject(Game * game);
        GameObject(Game * game, Point position, double rot);
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
        Sprite * sprite() const { return sprite_; }
        SDL_Rect rect();
        Point position();

        // mutators
        void set_x_position(double x_position) { x_position_ = x_position; }
        void set_y_position(double y_position) { y_position_ = y_position; }
        void set_x_velocity(double x_velocity) { x_velocity_ = x_velocity; }
        void set_y_velocity(double y_velocity) { y_velocity_ = y_velocity; }
        void set_x_acceleration(double x_acceleration) { x_acceleration_ = x_acceleration; }
        void set_y_acceleration(double y_acceleration) { y_acceleration_ = y_acceleration; }
        void set_rotation(double rotation) { rotation_ = rotation; }
        void set_width(double width) { width_ = width; }
        void set_height(double height) { height_ = height; }
        void set_selectable(bool selectable) { selectable_ = selectable; }
        void set_position(Point position);

        void create_sprite(std::string asset);

        virtual void select();
        virtual void deselect();
        virtual bool contains_point(double x, double y);
        virtual void move(Point point);
        void render();
        void set_sprite(Sprite * sprite) { sprite_ = sprite; }

        bool check_collision(SDL_Rect rect);
        void fix_collision(SDL_Rect rect);

        virtual bool is_entity() const { return false; }
};

#endif
