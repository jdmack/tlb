#ifndef TLB_GAME_OBJECT_H_
#define TLB_GAME_OBJECT_H_

#include <string>
#include "SDL/SDL.h"
#include "assets.h"
#include "vector.h"

class Screen;
class Action;

class GameObject
{
    protected:
        static int id_counter_;
        int object_id_;
        double x_position_;
        double y_position_;
        double rotation_;
        double width_;
        double height_;
        double x_velocity_;
        double y_velocity_;
        bool selectable_;
        bool selected_;
        std::string art_asset_;
        SDL_Surface * surface_;
        Screen * screen_;

        Action * current_action_;

    public:
        // constructors/destructors
        GameObject();
        GameObject(double x, double y, double rot);
        virtual ~GameObject();

        // accessors
        int object_id() const { return object_id_; }
        double x_position() const { return x_position_; }
        double y_position() const { return y_position_; }
        double rotation() const { return rotation_; }
        double width() const { return width_; }
        double height() const { return height_; }
        double x_velocity() const { return x_velocity_; }
        double y_velocity() const { return y_velocity_; }
        bool selectable() const { return selectable_; }
        bool selected() const { return selected_; }
        std::string art_asset() const { return art_asset_; }
        SDL_Surface * surface() const { return surface_; }
        Screen * screen() const { return screen_; }

        Action * current_action() const { return current_action_; }

        // mutators
        void set_surface(SDL_Surface * surface) { surface_ = surface; }
        void set_screen(Screen * screen) { screen_ = screen; }

        void draw(Screen * screen);
        virtual void select();
        virtual void deselect();
        virtual bool contains_point(double x, double y);
        virtual void move(double x, double y);
        virtual void stop();
        void set_current_action(Action * action) { current_action_ = action; }

};

#endif
