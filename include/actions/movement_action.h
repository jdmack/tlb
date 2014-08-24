#ifndef TLB_MOVEMENT_ACTION_H_
#define TLB_MOVEMENT_ACTION_H_

#include <vector>
#include <string>
#include "action.h"
#include "point.h"
#include "vector.h"

class Entity;
class GameObject;
class Level;
class Movement;

class MovementAction : public Action
{
    private:
		Point start_;
		Point end_;
		Level * level_;
		Vector current_max_velocity_;
		bool started_;

		std::vector<Movement *> * path_;
		std::vector<Movement *>::iterator current_;

    public:
        MovementAction(Point start, Point end, Level * level);

        // accessors
		Point start() const { return start_; }
		Point end() const { return end_; }
		std::vector<Movement *> * path() const { return path_; }
		Movement * current() const { return *current_; }
		Level * level() const { return level_; }

		void find_path();
		bool next_movement();
        std::string to_string();
        bool empty_path();

        // overridden
        bool update(Entity * entity, int delta_ticks);
        void stop();

		Vector current_max_velocity() const { return current_max_velocity_; }
		void set_current_max_velocity(Vector vector) { current_max_velocity_ = vector; }
		void remove_movements_back(int number = 1);

};

#endif
