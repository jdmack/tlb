#ifndef TLB_MOVEMENT_ACTION_H_
#define TLB_MOVEMENT_ACTION_H_

#include <vector>
#include <string>
#include "action.h"
#include "point.h"

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

		std::vector<Movement *> * path_;
		std::vector<Movement *>::iterator current_;

    public:
        MovementAction(Point start, Point end, Level * level);

        // accessors
		Point start() const { return start_; }
		Point end() const { return end_; }
		std::vector<Movement *> * path() const { return path_; }
		Movement * current() const { return *current_; }

		void find_path();
		bool next_movement();
        bool is_movement() const { return true; }
        std::string to_string();
        bool empty_path();

        // overridden
        void update(Entity * entity, int delta_ticks);
};

#endif
